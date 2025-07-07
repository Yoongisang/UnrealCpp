// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "AI/EnemyAIController.h"
#include "AI/EnemyAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "MyUserWidget.h"
#include "MyActorComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	if (SM.Succeeded())
	{

		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));

	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AI(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/ABP_Enemy.ABP_Enemy_C'"));
	if (AI.Succeeded())
	{
		GetMesh()->SetAnimClass(AI.Class);

	}

	AIControllerClass = AEnemyAIController::StaticClass();

	MyActorCompoent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActorCompoent"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarTest"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 130.f));

	static ConstructorHelpers::FClassFinder<UMyUserWidget> UW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(200.f, 20.f));
	}
	
}




// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	EnemyAnimInstance->OnMontageEnded.AddDynamic(this, &AEnemy::OnAttackMontageEnded);
	
	auto HpWidget = Cast<UMyUserWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(MyActorCompoent);

	}
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

	MyActorCompoent->OnDamaged(DamageAmount);
	if (MyActorCompoent->Hp <= 0)
	{
		SetLifeSpan(2.f);
	}
	return DamageAmount;
}

void AEnemy::EnemyAttack()
{
	UE_LOG(LogTemp, Log, TEXT("Attack"));

	if (IsValid(EnemyAnimInstance))
	{
		if (!isAttacking)
		{

			EnemyAnimInstance->PlayAttackMontage();
			isAttacking = true;
		}

	}
	

}

void AEnemy::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking = false;
	UE_LOG(LogTemp, Log, TEXT("OnAttackMontage Ended"));

}


