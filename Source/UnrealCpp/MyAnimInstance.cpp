// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "kismet/kismetMathLibrary.h"
#include "Enemy.h"

UMyAnimInstance::UMyAnimInstance()
{
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'"));
	//
	//if (AM.Succeeded())
	//{
	//	AttackMontage = AM.Object;
	//}
	//if (IsValid(AttackMontage))
	//{
	//	Montage_Play(AttackMontage);
	//}

}

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	APawn* Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		MyCharacter = Cast<AMyCharacter>(Pawn);
		if (IsValid(MyCharacter))
		{
			CharacterMovement = MyCharacter->GetCharacterMovement();
		}
		EnemyOwner = Cast<AEnemy>(Pawn);
		MyCharacterOwner = Cast<AMyCharacter>(Pawn);
	}

}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(CharacterMovement))
	{
		Velocity = CharacterMovement->Velocity;
		FRotator Rotation = MyCharacter->GetActorRotation();
		FVector UnrotateVector = Rotation.UnrotateVector(Velocity);
		
		UnrotateVector.Normalize();

		Horizontal = UnrotateVector.Y;
		Vertical = UnrotateVector.X;

		GroundSpeed = Velocity.Size2D();

		FVector Acceleration = CharacterMovement->GetCurrentAcceleration();
		if (GroundSpeed >= 3.0 && Acceleration != FVector::Zero())
		{
			ShouldMove = true;
		}
		else
		{
			ShouldMove = false;
		}
		
		IsFalling = CharacterMovement->IsFalling();
		
		AimRotation = MyCharacter->GetBaseAimRotation();
		FRotator RotFromX = UKismetMathLibrary::MakeRotFromX(Velocity);

		FRotator DeltaRotation = AimRotation - RotFromX;
		DeltaRotation.Normalize();

		YawOffset = DeltaRotation.Yaw;
	

	}
	if (IsValid(EnemyOwner))
	{
		EnemyHP = EnemyOwner->HP;
	}
	if (IsValid(MyCharacterOwner))
	{
		MyCharacterHP = MyCharacterOwner->HP;
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	if (IsValid(AttackMontage))
	{
		if (!Montage_IsPlaying(AttackMontage))
		{
			Montage_Play(AttackMontage);
		}

	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Error"));
	}
}


void UMyAnimInstance::AnimNotify_SaveAttack()
{
	MyCharacter->PlayerReload();

}

void UMyAnimInstance::AnimNotify_Shoot()
{
	MyCharacter->PlayerAttack();

}
