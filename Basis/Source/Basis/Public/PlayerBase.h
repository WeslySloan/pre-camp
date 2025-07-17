// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerBase.generated.h"
 
class UInputAction;
struct FInputActionValue;
class AWeapon;

UCLASS()
class BASIS_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerBase();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Hit(int32 Damage, AActor* ByWho) override;
	virtual void IncreaseKillCount() override;
	virtual void Attack() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> Weapon;
	// TSubclassOf : 클래스 정보를 가르킴 // 

	UPROPERTY()
	TObjectPtr<AWeapon> WeaponActor;

	UPROPERTY(EditAnyWhere)
	TObjectPtr<UInputAction> MoveAction; 
	UPROPERTY(EditAnyWhere)
	TObjectPtr<UInputAction> ZoomAction;
	UPROPERTY(EditAnyWhere)
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnyWhere)
	TObjectPtr<UInputAction> FireAction;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Fire(const FInputActionValue& value);
	void Zoom(const FInputActionValue& value);



};
