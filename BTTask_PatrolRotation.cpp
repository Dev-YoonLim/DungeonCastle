// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PatrolRotation.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_PatrolRotation::UBTTask_PatrolRotation() {
	WaitTime = 10.f;
	RandomDeviation = 0.;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_PatrolRotation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	myRogue =
		Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));
	EnemyRogue = Cast<AEnemyRogue>(EnemyController->GetPawn());
	return EBTNodeResult::InProgress;
}

void UBTTask_PatrolRotation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	myRogue =
		Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));
	FVector Goal =
		Blackboard->GetValueAsVector(AEnemyAIController::NextPosKeyName);
	EnemyRogue = Cast<AEnemyRogue>(EnemyController->GetPawn());
	
	
	EnemyRogue->SetActorRotation(FMath::RInterpTo(
		EnemyRogue->GetActorRotation(), Goal.Rotation(), DeltaSeconds, 3.f));
	

	if (EnemyRogue->GetActorRotation() == Goal.Rotation())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);


	
}