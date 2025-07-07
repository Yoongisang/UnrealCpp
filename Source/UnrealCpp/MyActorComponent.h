// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPP_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	int32 Hp;

public:
	FOnHpChanged OnHpChanged;

public:	
	// Sets default values for this component's properties
	UMyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	int32 GetHp() const { return Hp; }
public:
	void OnDamaged(float DamagedAmount);
	void SetHp(int32 NewHp);
	float GetHpRatio();

		
};
