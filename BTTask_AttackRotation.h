// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyRogue.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_AttackRotation.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API UBTTask_AttackRotation : public UBTTask_Wait
{
	GENERATED_BODY()
public:
	UBTTask_AttackRotation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
public:
	ARogue* myRogue;
	AEnemyRogue* EnemyRogue;
	AEnemyAIController* EnemyController;
	FVector Direction;
};
