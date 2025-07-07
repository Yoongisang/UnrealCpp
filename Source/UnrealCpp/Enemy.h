// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class UNREALCPP_API AEnemy : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UEnemyAnimInstance* EnemyAnimInstance;
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;
	UPROPERTY(VisibleAnywhere)
	class UMyActorComponent* MyActorCompoent;

private:
	bool isAttacking = false;

public:
	// Sets default values for this character's properties
	AEnemy();
public:
	bool GetIsAttacking() const { return isAttacking; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	void EnemyAttack();
public:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

};
