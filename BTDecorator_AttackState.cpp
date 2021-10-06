// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_AttackState.h"

UBTDecorator_AttackState::UBTDecorator_AttackState() {
	NodeName = TEXT("CheckAttackState");
}

bool UBTDecorator_AttackState::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	auto EnemyAIController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (EnemyAIController->CheckAttackState() == true)
		return false;
	else
		return true;
}