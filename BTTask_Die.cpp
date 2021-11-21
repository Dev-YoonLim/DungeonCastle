// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Die.h"

EBTNodeResult::Type UBTTask_Die::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue =
		Cast<AEnemyRogue>(EnemyController->GetPawn());

	auto Blackboard = OwnerComp.GetBlackboardComponent();

	EnemyRogue->EnemyRogueDie();


	return EBTNodeResult::Succeeded;


}