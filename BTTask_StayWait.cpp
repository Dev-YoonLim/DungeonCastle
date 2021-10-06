// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StayWait.h"

EBTNodeResult::Type UBTTask_StayWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	auto Blackboard = OwnerComp.GetBlackboardComponent();
	int32 StayValue = FMath::FRandRange(0, 1);
	if (EnemyController) {
		EnemyController->StopMovement();
		if(StayValue == 0)
			EnemyController->DoSideWalk();
		else if(StayValue == 1)
			EnemyController->DoSideWalk();
		return EBTNodeResult::Succeeded;
	}
	else
		return EBTNodeResult::Failed;
}