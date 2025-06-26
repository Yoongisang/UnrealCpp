// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
	}


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/ParagonSparrow/FX/Meshes/Heroes/Sparrow/Abilities/SM_Sparrow_Arrow.SM_Sparrow_Arrow'"));
	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);

	}

	static ConstructorHelpers::FObjectFinder<UMaterial> AM(TEXT("/ Script / Engine.Material'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Materials/M_Sparrow_Arrow.M_Sparrow_Arrow'"));
	if (AM.Succeeded())
	{
		Mesh->SetMaterial(0, AM.Object);
	}

	Mesh->SetRelativeLocationAndRotation(FVector(100.f, 0.f, 0.f), FRotator(90.f, 0.f, 0.f));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("Collision Box"));
	CollisionBox->SetupAttachment(Mesh);
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, -55.f));
	CollisionBox->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));


	// ✅ Collision 설정
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetNotifyRigidBodyCollision(true);
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // 캐릭터
	CollisionBox->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block); // 상자
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); // 벽

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnOverlapBegin);
	CollisionBox->OnComponentHit.AddDynamic(this, &AArrow::OnHit);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->SetUpdatedComponent(RootComponent);
	ProjectileMovement->InitialSpeed = 5000.f;S
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Primary/FX/P_Sparrow_HitHero.P_Sparrow_HitHero'"));
	if (PS.Succeeded())
	{
		HitParticle = PS.Object;

	}

}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArrow::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	ProjectileMovement->StopMovementImmediately();
	ProjectileMovement->ProjectileGravityScale = 0.f;
	
	if (OtherActor && OtherActor != this)
	{
		AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);
		SetActorRotation(GetActorForwardVector().Rotation());
	}
	
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, CollisionBox->GetComponentLocation(), FRotator::ZeroRotator, true);

}

void AArrow::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileMovement->StopMovementImmediately();
	ProjectileMovement->ProjectileGravityScale = 0.f;

	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		//FVector Impulse = GetActorForwardVector() * 1000.f;
		//OtherComp->AddImpulseAtLocation(Impulse, Hit.ImpactPoint);
		//SetActorRotation(Impulse.Rotation());
		AttachToComponent(OtherComp, FAttachmentTransformRules::KeepWorldTransform);
		SetActorRotation(GetActorForwardVector().Rotation());
	}

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle,Hit.ImpactPoint, FRotator::ZeroRotator, true);
}



