// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


UBTTask_Patrol::UBTTask_Patrol() {
	NodeName = TEXT("EnemyRoguePatrol");
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue = Cast<AEnemyRogue>(OwnerComp.GetAIOwner()->GetPawn());
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	myRogue =
		Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));
	
	//FVector PrePosition = Blackboard->GetValueAsVector(AEnemyAIController::PrePosKeyName);
	FVector PrePosition = Blackboard->GetValueAsVector(AEnemyAIController::PrePosKeyName);
	FNavLocation NextPosition;
	if (NavSystem->GetRandomPointInNavigableRadius(EnemyRogue->GetActorLocation(), 300.f, NextPosition)) {
				
		Blackboard->SetValueAsVector(AEnemyAIController::NextPosKeyName, NextPosition.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;

}