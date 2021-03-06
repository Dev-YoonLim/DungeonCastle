// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyRogue.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_StayWait_Fix.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API UBTTask_StayWait_Fix : public UBTTask_Wait
{
	GENERATED_BODY()


public:
	UBTTask_StayWait_Fix();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
public:
	AEnemyRogue* EnemyRogue;
	AEnemyAIController* EnemyController;
	FVector NextPosition;
	
};
