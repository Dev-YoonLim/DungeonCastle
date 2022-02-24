// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "humanoidEnemy.h"
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
	virtual void BodyInit() override;
	virtual void Working() override;
	virtual void Attack() override;
	virtual void Dodge() override;
	virtual void Idle() override;
	virtual void StatInit() override;
};
