// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Die.h"

EBTNodeResult::Type UBTTask_Die::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue =
		Cast<AEnemyRogue>(EnemyController->GetPawn());

	auto Blackboard = OwnerComp.GetBlackboardComponent();

	EnemyRogue->EnemyRogueDie();
	//EnemyRogue->GetActorLocation() + FVector(EnemyRogue->GetActorRightVector().GetSafeNormal() * 100);
	//EnemyController->MoveToActor(Target, 50.0f);
	//EnemyRogue = Cast<AEnemyRogue>();

	return EBTNodeResult::Succeeded;

	//return EBTNodeResult::Failed;

}