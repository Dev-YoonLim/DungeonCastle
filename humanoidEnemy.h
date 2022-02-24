// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

public:
	virtual void BodyInit();
	virtual void Working();
	virtual void Attack();
	virtual void Dodge();
	virtual void Idle();
	virtual void StatInit();

public:
	UPROPERTY(EditAnywhere)
		float EnemyHp;
	UPROPERTY(EditAnywhere)
		float EnemyHpCoe; // hp °è¼ö

public:
	int32 EnemyActionState; // 0Idle, 1Move, 2Attack, 3TakeHit, 4Death

};
