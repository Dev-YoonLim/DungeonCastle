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

public:
	UAnimMontage* ZombieIdle1;
	UAnimMontage* ZombieIdle2;
	UAnimMontage* ZombieDie1;
	UAnimMontage* ZombieDie2;
	UAnimMontage* ZombieWalk1;
	UAnimMontage* ZombieWalk2;
	UAnimMontage* ZombieHit1;
	UAnimMontage* ZombieHit2;
	UAnimMontage* ZombieAttack1;
	UAnimMontage* ZombieAttack2;
	UAnimMontage* ZombieAttack3;
	UAnimMontage* ZombieAttack4;

	
};
