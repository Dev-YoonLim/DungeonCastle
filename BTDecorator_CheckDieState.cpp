// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckDieState.h"

UBTDecorator_CheckDieState::UBTDecorator_CheckDieState() {
	NodeName = TEXT("CheckDieState");
}

bool UBTDecorator_CheckDieState::CalculateRawConditionValue (
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	auto EnemyAIController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (EnemyAIController->CheckDie() == true)
		return false;
	else
		return true;
}