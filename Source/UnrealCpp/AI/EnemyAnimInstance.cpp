// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "UnrealCpp/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnrealCpp/MyActorComponent.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Attack_PrimaryA_Montage.Attack_PrimaryA_Montage"));

	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}


}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		EnemyOwner = Cast<AEnemy>(Pawn);
		
		if (IsValid(EnemyOwner))
		{
			CharacterMovement = EnemyOwner->GetCharacterMovement();
		}
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(CharacterMovement))
	{
		FVector Velocity = CharacterMovement->Velocity;
		float GroundSpeed = Velocity.Size2D();
		ShouldMove = GroundSpeed >= 3.0;
		
	}

	if (IsValid(EnemyOwner))
	{	
		AActor* Owner = TryGetPawnOwner();
		UMyActorComponent* Comp = Cast<UMyActorComponent>(Owner->GetComponentByClass(UMyActorComponent::StaticClass()));
		if (Comp)
		{
			EnemyHP = Comp->Hp;
		}
		//EnemyHP = EnemyOwner->HP;
	}

}

void UEnemyAnimInstance::PlayAttackMontage()
{
	if (IsValid(AttackMontage))
	{
		if (!Montage_IsPlaying(AttackMontage))
		{
			Montage_Play(AttackMontage);
		}

	}
}
