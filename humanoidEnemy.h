// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HumanoidEnemyAniminstance.h"
#include "RogueWeapon.h"
#include "RogueTorch.h"
#include "Rogue.h"
#include "humanoidEnemy.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API AhumanoidEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AhumanoidEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	virtual void BodyInit();
	virtual void Walking();
	virtual void Attack();
	virtual void Dodge();
	virtual void Die();
	virtual void Hit();
	virtual void Idle();
	virtual void StatInit();

public:
	UPROPERTY(EditAnywhere)
		float EnemyHp;
	UPROPERTY(EditAnywhere)
		float EnemyHpCoe; // hp 계수
	UPROPERTY(EditAnywhere)
		int32 FormNumber;

public:
	int32 EnemyActionState; // 0Idle, 1Move, 2Attack, 3TakeHit, 4Death
	int32 TakeHitState; //슈퍼아머나 자세 등등
	UAnimInstance* SetHumanoidAnim;
	UHumanoidEnemyAniminstance* HumanoidAnim;
	ARogueWeapon* RogueWeapon;
	ARogueTorch* RogueTorch;
	ARogue* WeaponOwner;
	ARogue* TorchOwner;
};
