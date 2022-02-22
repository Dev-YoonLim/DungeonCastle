// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyRogue.h"
#include "EnemyRogueZombie.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API AEnemyRogueZombie : public AEnemyRogue
{
	GENERATED_BODY()

public:
	AEnemyRogueZombie();
	virtual void EnemyWeaponInit();
	virtual void EnemyRogueBodyInit();
	virtual void EnemyRogueCollisionInit();
	virtual void EnemyRogueStateInit();
	void EnemyRogueTakeDamegeDelegateInit();
	virtual void TakeStackInit();
	virtual void AllStateInit();
	virtual void AllDotTickInit();
	virtual void StateEffectInit();

	virtual void EnemyRogueBodySetting();
	virtual void EnemyRogueStateSetting();
};
