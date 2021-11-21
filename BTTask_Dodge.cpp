// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Dodge.h"

EBTNodeResult::Type UBTTask_Dodge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue =
		Cast<AEnemyRogue>(EnemyController->GetPawn());

	auto Blackboard = OwnerComp.GetBlackboardComponent();

	FVector DodgePoint;
	int32 RollDirectionIndex = Blackboard->GetValueAsInt(AEnemyAIController::RollDirection);
	if(RollDirectionIndex == 0)
		DodgePoint = EnemyRogue->GetActorLocation() + FVector(EnemyRogue->GetActorRightVector().GetSafeNormal() * 250);
	else if (RollDirectionIndex == 4)
		DodgePoint = EnemyRogue->GetActorLocation() - FVector(EnemyRogue->GetActorRightVector().GetSafeNormal() * 250);
	else if (RollDirectionIndex == 1)
		DodgePoint = EnemyRogue->GetActorLocation() - FVector(EnemyRogue->GetActorForwardVector().GetSafeNormal() * 250);
	else if (RollDirectionIndex == 2)
		DodgePoint = EnemyRogue->GetActorLocation() + 
		FVector((EnemyRogue->GetActorRightVector() - EnemyRogue->GetActorForwardVector()).GetSafeNormal() * 250);
	else if (RollDirectionIndex == 3)
		DodgePoint = EnemyRogue->GetActorLocation() - 
		FVector((-EnemyRogue->GetActorRightVector() - EnemyRogue->GetActorForwardVector()).GetSafeNormal() * 250);
	
	

	if (EnemyController) {
		if (EnemyController->SenseRogue == true) {
			EnemyRogue->GetCharacterMovement()->MaxWalkSpeed = 250.f;
			EnemyController->MoveToLocation(DodgePoint);
			EnemyController->DoRoll(0);
			
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;

}