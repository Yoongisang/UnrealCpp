// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "MyAnimInstance.h"
#include "AI/EnemyAIController.h"



// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HP = 50;

	AIControllerClass = AEnemyAIController::StaticClass();


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HP -= DamageAmount;
	UE_LOG(LogTemp, Log, TEXT("Damaged : %f"), HP);
	if (HP <= 0)
	{
		SetLifeSpan(2.f);
	}
	return 0.f;
}

