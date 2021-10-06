// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyRogue.h"
#include "EnemyAIController.h"
#include "BTDecorator_CheckSense.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API UBTDecorator_CheckSense : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_CheckSense();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
