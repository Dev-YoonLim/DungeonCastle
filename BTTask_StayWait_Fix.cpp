// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StayWait_Fix.h"

UBTTask_StayWait_Fix::UBTTask_StayWait_Fix() {
	WaitTime = 3.f;
	RandomDeviation = 0.5;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_StayWait_Fix::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue = Cast<AEnemyRogue>(EnemyController->GetPawn());
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	EnemyRogue->GetCharacterMovement()->MaxWalkSpeed = EnemyRogue->GetSpeedValue();
	return EBTNodeResult::InProgress;
}

void UBTTask_StayWait_Fix::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	NextPosition = Blackboard->GetValueAsVector(AEnemyAIController::NextPosKeyName);
	EnemyRogue = Cast<AEnemyRogue>(EnemyController->GetPawn());

	if (EnemyRogue != nullptr) {
		if (EnemyController->CheckDie() == true)
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		else{
			if (EnemyController->GetMoveStatus() == EPathFollowingStatus::Idle) {
				EnemyController->DoAllAnimStop();
				if (EnemyController->SenseRogue == true)
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}
}