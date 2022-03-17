// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TakeHit.h"

EBTNodeResult::Type UBTTask_TakeHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyRogue =
		Cast<AEnemyRogue>(EnemyController->GetPawn());

	auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (EnemyRogue->HitKinds == 0) {
		if (EnemyRogue->EnemyDead == false) {
			UGameplayStatics::PlaySoundAtLocation(this, EnemyRogue->TakeHitSoundCue, EnemyRogue->GetActorLocation());
			EnemyRogue->WeaponHitAnimationPlay();
		}
	}
	else if (EnemyRogue->HitKinds == 1) {
		if (EnemyRogue->EnemyDead == false) {
			UGameplayStatics::PlaySoundAtLocation(this, EnemyRogue->TakeHitSoundCue, EnemyRogue->GetActorLocation());
			EnemyRogue->TorchHitAnimationPlay();
		}
	}


	return EBTNodeResult::Succeeded;


}