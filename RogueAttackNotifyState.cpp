// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAttackNotifyState.h"
#include "Rogue.h"
#include "RogueWeapon.h"
#include "EnemyRogue.h"

FString URogueAttackNotifyState::GetNotifyName_Implementation() const {
	return TEXT("CanHit");
}

void URogueAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DurationTime){
	Super::NotifyBegin(MeshComp, Animation, DurationTime);
	ARogue* Rogue = Cast<ARogue>(MeshComp->GetOwner());
	//ARogueWeapon* Weapon = Cast<ARogueWeapon>(Rogue->RogueWeapons);
	if (Rogue) {
		if (Rogue->getAttackQue() != 4) {
			Rogue->setCanHit(true);
		}
		else if (Rogue->getAttackQue() == 4) {
			Rogue->SetTorchCanHit(true);
		}
	}
}

void URogueAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);
	ARogue* Rogue = Cast<ARogue>(MeshComp->GetOwner());
	//ARogueWeapon* Weapon = Cast<ARogueWeapon>(Rogue->RogueWeapons);
	if (Rogue) {
		if (Rogue->getAttackQue() != 4) {
			Rogue->setCanHit(false);
		}
		else if (Rogue->getAttackQue() == 4) {
			Rogue->SetTorchCanHit(false);
		}
	}
}

void URogueAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DurationTime) {
	Super::NotifyTick(MeshComp, Animation, DurationTime);
}