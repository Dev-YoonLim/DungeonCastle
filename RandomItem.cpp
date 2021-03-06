// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomItem.h"


ARandomItem::ARandomItem() {

}

void ARandomItem::NotifyActorBeginOverlap(AActor* OtherActor){
	Super::NotifyActorBeginOverlap(OtherActor);
	myRogue = Cast<ARogue>(OtherActor);
	ItemIndex = FMath::FRandRange(0, 99);
	if (myRogue) {
		myRogue->MyRogueState->ItemCount++;
		if (myRogue->MyRogueState->ItemCount == 3) {
			myRogue->SetStartDialogueIndex(1);
			//myRogue->MyRogueState->StartDialogueState[1] = 1;
			//myRogue->DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL, myRogue->MyRogueState->StartDialogueSourceRef[1]));
			myRogue->BeepCall();
		}
		/*MyRogueState->ItemCount++;
		if (MyRogueState->ItemCount == 3) {
			MyRogueState->DialogueState[1] = 1;
			myRogue->BeepCall();
		}*/
		UGameplayStatics::PlaySoundAtLocation(this, GetItemSound, GetActorLocation());
		if (ItemIndex <= 70) {
			MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(-50.f * FMath::FRandRange(0.5f, 1.f));
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("DataUp"));
		}
		else if (ItemIndex <= 90) {
			MyGameMode->RogueTakeAbilityDelegate.ExecuteIfBound(23);
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Ability"));
		}
		else if (ItemIndex <= 92) {
			int32 WeaponNumber = FMath::FRandRange(0, 9);
			MyGameMode->Call_RogueHavingWeaponCheckDelegate.ExecuteIfBound(WeaponNumber);
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Weapon"));
		}
		else if (ItemIndex <= 95) {
			int32 AttackFormNumber[5] = { FMath::FRandRange(0, 3),  FMath::FRandRange(0, 6),
			 FMath::FRandRange(0, 8),  FMath::FRandRange(0, 9),  FMath::FRandRange(0, 3) };
			if (AttackFormNumber[0] == 0)
				MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(AttackFormNumber[0], AttackFormNumber[1]);
			else if (AttackFormNumber[0] == 1)
				MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(AttackFormNumber[0], AttackFormNumber[2]);
			else if (AttackFormNumber[0] == 2)
				MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(AttackFormNumber[0], AttackFormNumber[4]);
			else if (AttackFormNumber[0] == 3)
				MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(AttackFormNumber[0], AttackFormNumber[5]);
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Form %d"),
				AttackFormNumber[0]));
		}
		else if (ItemIndex <= 97) {
			int32 ElementalNumber = FMath::FRandRange(0, 4);
			MyGameMode->Call_RogueHavingElementalCheckDelegate.ExecuteIfBound(ElementalNumber);
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Elemental %d"),
				ElementalNumber));
		}
		else {
			int32 ElementalNumber = FMath::FRandRange(5, 9);
			MyGameMode->Call_RogueHavingElementalCheckDelegate.ExecuteIfBound(ElementalNumber);
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Elemental %d"),
				ElementalNumber));
		}
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TakeItem, GetActorTransform());
		Destroy();
	}
}