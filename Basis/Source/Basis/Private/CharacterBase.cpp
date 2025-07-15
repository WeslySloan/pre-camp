// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FullHP = 100;
	Strength = 10;
	KillCount = 0;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultController();
	CurrentHP = FullHP;
	KillCount = 0;
}

void ACharacterBase::Attack()
{
	AttackCount++;
}

void ACharacterBase::Hit(int32 Damage, AActor* ByWho)
{
	CurrentHP -= Damage;
	if (CurrentHP < 0) 
		CurrentHP = 0;
}

void ACharacterBase::IncreaseKillCount()
{
	KillCount++;
}


