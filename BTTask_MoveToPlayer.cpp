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

	Goal = Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));


	if (Goal) {
		if (EnemyController->SenseRogue == true) {
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("CheckSense"));
			if (EnemyController->CheckDie() == true) {
				//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("MoveToDie"));
				return EBTNodeResult::Failed;
			}
			EnemyController->MoveToActor(Goal, EnemyRogue->EnemyRogueWeaponRange);
			EnemyController->DoWalk();
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("GoalSuccess"));
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("MoveTo"));
			return EBTNodeResult::Succeeded;
		}
		//else
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("NotSense"));
	}
	return EBTNodeResult::Failed;

}
