// Fill out your copyright notice in the Description page of Project Settings.

    #include "PlayerBase.h"
    #include "GameFrameWork/SpringArmComponent.h"
    #include "Camera/CameraComponent.h"
    #include "EnhancedInputComponent.h"
    #include "Weapon.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

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

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (IsValid(PC))
    {
        ULocalPlayer* Player = PC->GetLocalPlayer();
        if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player))
        {
            InputSubsystem->AddMappingContext(InputMappingContext, 0);
        }
    }

    WeaponActor = GetWorld()->SpawnActor<AWeapon>(Weapon);
    // staticclass() : 객체의 클래스정보를 반환. ( 런타임에 클래스를 나타내는 UClass 객체를 반환 )

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
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerBase::Look);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerBase::Fire);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerBase::Zoom);
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
        AddControllerPitchInput(-LookAxisVector.Y);
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

