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
	//EnemyController->MoveToActor(Target, 50.0f);
	//EnemyRogue = Cast<AEnemyRogue>();
	FVector PrePosition = Blackboard->GetValueAsVector(AEnemyAIController::PrePosKeyName);
	FNavLocation NextPosition;
	if (NavSystem->GetRandomPointInNavigableRadius(EnemyRogue->GetActorLocation(), 300.f, NextPosition)) {
		
		/*GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, FString::Printf(TEXT("x%f y%f z%f"),
			EnemyRogue->GetActorLocation().X, EnemyRogue->GetActorLocation().Y, EnemyRogue->GetActorLocation().Z));

		GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Yellow, FString::Printf(TEXT("x%f y%f z%f"),
			NextPosition.Location.X, NextPosition.Location.Y, NextPosition.Location.Z));*/
		
		Blackboard->SetValueAsVector(AEnemyAIController::NextPosKeyName, NextPosition.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;

}