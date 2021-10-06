// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckHitState.h"

UBTDecorator_CheckHitState::UBTDecorator_CheckHitState() {
	NodeName = TEXT("CheckHitState");
}

bool UBTDecorator_CheckHitState::CalculateRawConditionValue (
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	auto EnemyAIController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	if (EnemyAIController->CheckHit() == true) {
		return false;
	}
	else
		return true;
}