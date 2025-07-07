// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool ShouldMove;
public:
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 EnemyHP;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UCharacterMovementComponent* CharacterMovement;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr <class AEnemy> EnemyOwner;
	UPROPERTY(Category = "Ani", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DeathMontage; // UAnimMontage ∆˜¿Œ≈Õ

public:
	UEnemyAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	void PlayAttackMontage();

};
