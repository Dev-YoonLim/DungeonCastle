// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "humanoidEnemy.h"
#include "HumanoidEnemyAniminstance.h"
#include "Components/CapsuleComponent.h"
#include "ZombieEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API AZombieEnemy : public AhumanoidEnemy
{
	GENERATED_BODY()
public:
	AZombieEnemy();

public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION()
		void EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void BodyInit() override;
	virtual void Walking() override;
	virtual void Attack() override;
	virtual void Dodge() override;
	virtual void Idle() override;
	virtual void Die() override;
	//virtual void Hit() override;
	virtual void StatInit() override;

public:
	UAnimInstance* SetHumanoidAnim;
	UHumanoidEnemyAniminstance* HumanoidAnim;
};
