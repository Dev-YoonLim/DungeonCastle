// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyRogue.h"
#include "EnemyRogue_Zombie.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API AEnemyRogue_Zombie : public AEnemyRogue
{
	GENERATED_BODY()

public:
	AEnemyRogue_Zombie();
	
public:
	//virtual void BeginPlay() override;
	virtual void EnemyRogueBodyInit() override;
	virtual void AnimBlendInit() override;
	virtual void EnemyRogueStateSetting() override;
	virtual void EnemyRogueWeaponInfo() override;
	virtual void WeaponHitAnimationPlay() override;
};
