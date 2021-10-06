// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckRoll.h"

UBTDecorator_CheckRoll::UBTDecorator_CheckRoll() {
	NodeName = TEXT("CheckRoll");
}

bool UBTDecorator_CheckRoll::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	auto EnemyAIController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard->GetValueAsInt(AEnemyAIController::NextForm) <= 2)
		return true;
	else
		return false;
}