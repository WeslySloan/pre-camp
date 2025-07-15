// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Bullet.h"
#include "Playerbase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	MuzzleOffset = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleOffset"));
	MuzzleOffset->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Fire()
{
    UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
    if (IsValid(AnimInstance) && IsValid(FireMontage))
    {
        AnimInstance->Montage_Play(FireMontage);
    }

    if (IsValid(Bullet))
    {
        FRotator SpawnRotation = MuzzleOffset->GetComponentRotation();
        FVector SpawnLocation = MuzzleOffset->GetComponentLocation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        APlayerBase* PB = Cast<APlayerBase>(GetOwner());

        if (!IsValid(PB))
        {
            GetWorld()->SpawnActor<ABullet>(Bullet, SpawnLocation, SpawnRotation, SpawnParams);
            return;
        }

        APlayerController* PC = Cast<APlayerController>(PB->GetController());
        int32 x, y;


        if (!IsValid(PC))
        {
            GetWorld()->SpawnActor<ABullet>(Bullet, SpawnLocation, SpawnRotation, SpawnParams);
            return;
        }

        PC->GetViewportSize(x, y);
        FVector WorldCenter;
        FVector WorldFront;
        PC->DeprojectScreenPositionToWorld(x / 2.0f, y / 2.0f, WorldCenter, WorldFront);
        WorldCenter += WorldFront * 10000;
        SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, WorldCenter);
        GetWorld()->SpawnActor<ABullet>(Bullet, SpawnLocation, SpawnRotation, SpawnParams);
    }
}
