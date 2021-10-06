// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PreShakingMove.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_PreShakingMove::UBTTask_PreShakingMove() {
	NodeName = TEXT("ShakingMoving");
	WaitTime =  0.5;
	RandomDeviation = 0.3;
}

EBTNodeResult::Type UBTTask_PreShakingMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue = Cast<AEnemyRogue>(OwnerComp.GetAIOwner()->GetPawn());
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	myRogue = Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));
	
	ShakingForm = FMath::FRandRange(0, 2);
	int32 NextFormIndex = FMath::FRandRange(0, 9);
	int32 NextFormDirIndex = FMath::FRandRange(0, 4);
	Blackboard->SetValueAsInt(AEnemyAIController::NextForm, NextFormIndex);
	if (EnemyController->CheckDie() == true || EnemyController->CheckHit() == true)
		return EBTNodeResult::Failed;
	if(NextFormIndex <= 2)
		Blackboard->SetValueAsInt(AEnemyAIController::RollDirection, NextFormDirIndex);
	return EBTNodeResult::InProgress;

	//return EBTNodeResult::Failed;

}

void UBTTask_PreShakingMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue = Cast<AEnemyRogue>(OwnerComp.GetAIOwner()->GetPawn());
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	myRogue =
		Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));
	//FVector RightNormal = EnemyRogue->GetActorRightVector();
	//RightNormal.No
	if (ShakingForm == 0) {
		EnemyRogue->SetActorLocation(EnemyRogue->GetActorLocation() +
			(EnemyRogue->GetActorRightVector().GetSafeNormal()) / 2);
		EnemyRogue->DoWalk(1);
	}
	
	else if (ShakingForm == 1) {
		EnemyRogue->SetActorLocation(EnemyRogue->GetActorLocation() -
			(EnemyRogue->GetActorRightVector().GetSafeNormal()) / 2);
		EnemyRogue->DoWalk(2);
	}
	
	else if (ShakingForm == 2){
		EnemyRogue->SetActorLocation(EnemyRogue->GetActorLocation() - 
			(EnemyRogue->GetActorForwardVector().GetSafeNormal())); 
		EnemyRogue->DoWalk(0);
	}
	if (EnemyController->CheckDie() == true)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
}