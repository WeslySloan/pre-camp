// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CharacterBase.h"

// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 20000.0f;
	ProjectileMovementComponent->MaxSpeed = 20000.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector Normallmpulse, const FHitResult& Hit)
{
	ACharacterBase* CB = Cast<ACharacterBase>(OtherActor);
	AActor* Actor = GetOwner();
	if (!IsValid(Actor))
	{
		return;
	}

	ACharacterBase* Owner = Cast<ACharacterBase>(Actor->GetOwner());
	if (!IsValid(Owner))
	{
		return;
	}

	if (IsValid(CB))
	{
		CB->Hit(Owner->Strength, Owner);
	}

}

