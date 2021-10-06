// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckInAttackRange.h"

UBTDecorator_CheckInAttackRange::UBTDecorator_CheckInAttackRange() {
	NodeName = TEXT("CheckInAttackRange");
}

bool UBTDecorator_CheckInAttackRange::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	auto EnemyAIController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	ARogue* Rogue = Cast<ARogue>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AEnemyRogue* EnemyRogue = Cast<AEnemyRogue>(OwnerComp.GetAIOwner()->GetPawn());
	if (Rogue->GetDistanceTo(EnemyRogue) <= 200.f)
		return true;
	else
		return false;
}