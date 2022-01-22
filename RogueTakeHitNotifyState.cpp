// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueTakeHitNotifyState.h"
#include "EnemyRogue.h"

FString URogueTakeHitNotifyState::GetNotifyName_Implementation() const {
	return TEXT("Down");
}

void URogueTakeHitNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DurationTime) {
	Super::NotifyBegin(MeshComp, Animation, DurationTime);
	AEnemyRogue* EnemyRogue = Cast<AEnemyRogue>(MeshComp->GetOwner());
	if (EnemyRogue) {
		EnemyRogue->SetEnemyDownFinish(false);
	}
}

void URogueTakeHitNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);
	AEnemyRogue* EnemyRogue = Cast<AEnemyRogue>(MeshComp->GetOwner());
	if (EnemyRogue) {
		EnemyRogue->SetEnemyDownFinish(true);
	}
}

void URogueTakeHitNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DurationTime) {
	Super::NotifyTick(MeshComp, Animation, DurationTime);
}