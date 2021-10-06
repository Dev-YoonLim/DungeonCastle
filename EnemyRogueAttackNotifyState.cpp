// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRogueAttackNotifyState.h"
#include "Rogue.h"
#include "EnemyRogue.h"

FString UEnemyRogueAttackNotifyState::GetNotifyName_Implementation() const {
	return TEXT("RogueAttackTakeHit");
}

void UEnemyRogueAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DurationTime) {
	Super::NotifyBegin(MeshComp, Animation, DurationTime);
	AEnemyRogue* EnemyRogue = Cast<AEnemyRogue>(MeshComp->GetOwner());
	//AEnemyRogueWeapon* EnemyRogueWeapon = Cast<AEnemyRogueWeapon>(EnemyRogue->EnemyWeapon->GetChildActor());
	if (EnemyRogue) {
		EnemyRogue->SetTakeHit(true);
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("CanhitBegin"));
	}
}

void UEnemyRogueAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);
	AEnemyRogue* EnemyRogue = Cast<AEnemyRogue>(MeshComp->GetOwner());
	//AEnemyRogueWeapon* EnemyRogueWeapon = Cast<AEnemyRogueWeapon>(EnemyRogue->EnemyWeapon->GetChildActor());
	if (EnemyRogue) {
		EnemyRogue->SetTakeHit(false);
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("CanhitEnd"));
	}
}

void UEnemyRogueAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DurationTime) {
	Super::NotifyTick(MeshComp, Animation, DurationTime);
}
