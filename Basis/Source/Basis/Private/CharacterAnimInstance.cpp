// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnimInstance.h"
#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Character = Cast<ACharacterBase>(TryGetPawnOwner());
    if (IsValid(Character))
    {
        MovementComponent = Character->GetCharacterMovement();
    }
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (IsValid(MovementComponent))
    {
        Speed = MovementComponent->Velocity.Size();
        AttackCount = Character->AttackCount;
    }

    if (IsValid(Character))
    {
        ActorRot = Character->GetActorRotation();
        ControlRot = Character->GetControlRotation();
    }
    FRotator DeltaRotator = (ActorRot - ControlRot).GetNormalized();
    UE_LOG(LogTemp, Display, TEXT("DeltaRotation : %f"), DeltaRotator.Pitch);
    
}

void UCharacterAnimInstance::AnimNotify_Attack()
{
    Character->AttackCount = 0;
    AttackCount = 0;
}
