// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToPlayer.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	
	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue =
		Cast<AEnemyRogue>(EnemyController->GetPawn());

	auto Blackboard = OwnerComp.GetBlackboardComponent();

	ARogue* Goal =
		Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));

	if (Goal) {
		if (EnemyController->SenseRogue == true) {
			if (EnemyController->CheckDie() == true)
				return EBTNodeResult::Failed;
			EnemyController->MoveToActor(Goal, EnemyRogue->EnemyRogueWeaponRange);
			EnemyController->DoWalk();
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("MoveTo"));
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;

}
