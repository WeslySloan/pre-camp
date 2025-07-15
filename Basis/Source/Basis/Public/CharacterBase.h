// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class BASIS_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Attack();
	virtual void Hit(int32 Damage, AActor* ByWho);
	virtual void IncreaseKillCount();

public:
	UPROPERTY(EditAnywhere)
	int32 FullHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 AttackCount;

	UPROPERTY(EditAnywhere)
	int32 Strength;

protected:
	int32 CurrentHP;

private:
	int32 KillCount;

};
