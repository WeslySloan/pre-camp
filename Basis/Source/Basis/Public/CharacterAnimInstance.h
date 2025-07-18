// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API UCharacterAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UFUNCTION()
    void AnimNotify_Attack();

    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<class ACharacterBase> Character;

    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<class UCharacterMovementComponent> MovementComponent;

    UPROPERTY(BlueprintReadOnly)
    FRotator ControlRot;

    UPROPERTY(BlueprintReadOnly)
    FRotator ActorRot;

    UPROPERTY(BlueprintReadOnly)
    float Speed;

    UPROPERTY(BlueprintReadOnly)
    int32 AttackCount;
};
