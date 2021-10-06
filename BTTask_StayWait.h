// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyRogue.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StayWait.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API UBTTask_StayWait : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	AEnemyRogue* EnemyRogue;
	AEnemyAIController* EnemyController;
};
