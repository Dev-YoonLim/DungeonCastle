// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAttackNotifyState.h"
#include "Rogue.h"
#include "RogueWeapon.h"
#include "RogueTorch.h"
#include "EnemyRogue.h"

FString URogueAttackNotifyState::GetNotifyName_Implementation() const {
	return TEXT("CanHit");
}

void URogueAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DurationTime){
	Super::NotifyBegin(MeshComp, Animation, DurationTime);
	ARogue* Rogue = Cast<ARogue>(MeshComp->GetOwner());
	ARogueWeapon* RogueWeapon = Cast<ARogueWeapon>(Rogue->RogueWeapons->GetChildActor());
	ARogueTorch* RogueTorch = Cast<ARogueTorch>(Rogue->RogueTorchs->GetChildActor());
	//ARogueWeapon* Weapon = Cast<ARogueWeapon>(Rogue->RogueWeapons);
	if (Rogue) {
		if (Rogue->getAttackQue() != 4) {
			Rogue->setCanHit(true);
			RogueWeapon->SetAttackState(1);
		}
		else if (Rogue->getAttackQue() == 4) {
			Rogue->SetTorchCanHit(true);
			RogueTorch->SetAttackState(1);
		}
	}
}

void URogueAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);
	ARogue* Rogue = Cast<ARogue>(MeshComp->GetOwner());
	ARogueWeapon* RogueWeapon = Cast<ARogueWeapon>(Rogue->RogueWeapons->GetChildActor());
	ARogueTorch* RogueTorch = Cast<ARogueTorch>(Rogue->RogueTorchs->GetChildActor());
	//ARogueWeapon* Weapon = Cast<ARogueWeapon>(Rogue->RogueWeapons);
	if (Rogue) {
		if (Rogue->getAttackQue() != 4) {
			Rogue->setCanHit(false);
			RogueWeapon->SetAttackState(0);
		}
		else if (Rogue->getAttackQue() == 4) {
			Rogue->SetTorchCanHit(false);
			RogueTorch->SetAttackState(0);
		}
	}
}

void URogueAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DurationTime) {
	Super::NotifyTick(MeshComp, Animation, DurationTime);
}