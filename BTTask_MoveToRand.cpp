// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToRand.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type UBTTask_MoveToRand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue =
		Cast<AEnemyRogue>(OwnerComp.GetAIOwner()->GetPawn());
	ARogue* myRogue =
		Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));

	FVector Goal = 
		Blackboard->GetValueAsVector(AEnemyAIController::NextPosKeyName);
		EnemyController->MoveTo(Goal);
		EnemyController->DoWalk();
		return EBTNodeResult::Succeeded;
}