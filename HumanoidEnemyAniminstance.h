// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HumanoidEnemyAniminstance.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API UHumanoidEnemyAniminstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UHumanoidEnemyAniminstance();


protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void ZombieAnimationInit();
	
};
