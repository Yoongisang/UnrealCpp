// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxHp = 100;

}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	Hp = MaxHp;
	GetHpRatio();
	
}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyActorComponent::OnDamaged(float DamagedAmount)
{
	int32 NewHp = Hp - DamagedAmount;
	SetHp(NewHp);
}

void UMyActorComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;
	if (Hp < 0)
	{
		Hp = 0;
	}
	OnHpChanged.Broadcast();

}

float UMyActorComponent::GetHpRatio()
{
	if (MaxHp == 0 || Hp == 0)
	{
		return 0.0f;
	}

	return (float)Hp / (float)MaxHp;

}

