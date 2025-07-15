// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBase.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Weapon.h"

// Sets default values
APlayerBase::APlayerBase()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera-> SetupAttachment(CameraBoom);
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

    WeaponActor = GetWorld()->SpawnActor<AWeapon>(Weapon);
    if (IsValid(WeaponActor))
    {
        FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
        WeaponActor->AttachToComponent(GetMesh(), TransformRules, TEXT("WeaponSocket"));
        WeaponActor->SetOwner(this);
    }
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerBase::Move);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerBase::Move);
	}
}
void APlayerBase::Hit(int32 Damage, AActor* ByWho)
{
	Super::Hit(Damage, ByWho);

	if (CurrentHP > 0)
	{
		return;
	}

    Destroy();

}

void APlayerBase::IncreaseKillCount()
{
	Super::IncreaseKillCount();
}

void APlayerBase::Attack()
{
	Super::Attack();
    if (IsValid(WeaponActor))
    {
        WeaponActor->Fire();
    }

}

void APlayerBase::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}

void APlayerBase::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void APlayerBase::Fire(const FInputActionValue& Value)
{
    Attack();
}

void APlayerBase::Zoom(const FInputActionValue& Value)
{
    if (!IsValid(CameraBoom))
    {
        return;
    }

    if (Value.Get<bool>())
    {
        CameraBoom->TargetArmLength = 40;
        CameraBoom->SocketOffset = FVector(0, 40, 60);
    }
    else
    {
        CameraBoom->TargetArmLength = 400;
        CameraBoom->SocketOffset = FVector(0, 0, 0);
    }
}

