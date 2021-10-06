// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckSense.h"

UBTDecorator_CheckSense::UBTDecorator_CheckSense() {
	NodeName = TEXT("CheckSense");
}

bool UBTDecorator_CheckSense::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	auto EnemyAIController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (EnemyAIController->CheckSense() == true)
		return true;
	else
		return false;
}