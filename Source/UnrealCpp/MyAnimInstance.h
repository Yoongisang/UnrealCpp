// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"
/**
 * 
 */
UCLASS()
class UNREALCPP_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool ShouldMove;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool IsFalling;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector Velocity;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float Horizontal;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float Vertical;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float GroundSpeed;


	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float YawOffset;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FRotator AimRotation;

public:
	UPROPERTY(VisibleAnywhere)
	class AMyCharacter* MyCharacter;
	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementComponent* CharacterMovement;
	//UPROPERTY(VisibleAnywhere)
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage; // UAnimMontage 포인터
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UAnimMontage* DeathMontage; // UAnimMontage 포인터
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class AEnemy* EnemyOwner;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float HP;
public:
	UMyAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	void PlayAttackMontage(); 
public:

	UFUNCTION()
	void AnimNotify_SaveAttack();
	UFUNCTION()
	void AnimNotify_Shoot();

};
