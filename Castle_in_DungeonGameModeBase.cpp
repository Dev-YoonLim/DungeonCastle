// Copyright Epic Games, Inc. All Rights Reserved.


#include "Castle_in_DungeonGameModeBase.h"
#include "Rogue.h"
#include "RogueState.h"
#include "MyRogueController.h"
#include "MyRogueWidget.h"

ACastle_in_DungeonGameModeBase::ACastle_in_DungeonGameModeBase(){
	DefaultPawnClass = ARogue::StaticClass();
	PlayerControllerClass = AMyRogueController::StaticClass();
	PlayerStateClass = ARogueState::StaticClass();
	WidgetPageNumber = 0;
	WidgetPrePageNumber = 0;
	WidgetCount = 0;
	GameStartCheck = 0;
	NewGameStart = true;
	//FOVValue = 1.f;
	SaveSlotName = TEXT("SaveSlot");
	//StartSetting();

	auto FXSoundClassAsset = ConstructorHelpers::FObjectFinder<USoundClass>
		(TEXT("SoundClass'/Game/Sound/FX_SoundClass.FX_SoundClass'"));
	if (FXSoundClassAsset.Succeeded()) {
		FXSoundClass = FXSoundClassAsset.Object;
	}
	
	auto TitleWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/TitleMenu.TitleMenu_C'"));
	if (TitleWidget.Succeeded()) {
		TitleMenuWidgetClass = TitleWidget.Class;
	}

	auto MainUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/Main.Main_C'"));
	if (MainUIWidget.Succeeded()) {
		MainWidgetClass = MainUIWidget.Class;
	}
	
	auto ReSumeUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/ReSumeMenu.ReSumeMenu_C'"));
	if (ReSumeUIWidget.Succeeded()) {
		ReSumeWidgetClass = ReSumeUIWidget.Class;
	}

	auto TabUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/TabMenu.TabMenu_C'"));
	if (TabUIWidget.Succeeded()) {
		TabWidgetClass = TabUIWidget.Class;
	}

	auto StatUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/RogueStat.RogueStat_C'"));
	if (StatUIWidget.Succeeded()) {
		StatWidgetClass = StatUIWidget.Class;
	}

	auto EquipmentUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/RogueEquipment.RogueEquipment_C'"));
	if (EquipmentUIWidget.Succeeded()) {
		EquipmentWidgetClass = EquipmentUIWidget.Class;
	}

	auto BurningTotemUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/BurningTotemMenu.BurningTotemMenu_C'"));
	if (BurningTotemUIWidget.Succeeded()) {
		BurningTotemWidgetClass = BurningTotemUIWidget.Class;
	}

	auto ChangedWeaponUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/ChangedWeaponMenu.ChangedWeaponMenu_C'"));
	if (ChangedWeaponUIWidget.Succeeded()) {
		ChangedWeaponWidgetClass = ChangedWeaponUIWidget.Class;
	}

	auto ChangedAttackFormUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/ChangedAttackForm.ChangedAttackForm_C'"));
	if (ChangedAttackFormUIWidget.Succeeded()) {
		ChangedAttackFormWidgetClass = ChangedAttackFormUIWidget.Class;
	}

	auto ChangedElementalFormUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/ChangedElemental.ChangedElemental_C'"));
	if (ChangedElementalFormUIWidget.Succeeded()) {
		ChangedElementalFormWidgetClass = ChangedElementalFormUIWidget.Class;
	}

	auto AddAbilityUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/AddAbilityMenu.AddAbilityMenu_C'"));
	if (AddAbilityUIWidget.Succeeded()) {
		AddAbilityWidgetClass = AddAbilityUIWidget.Class;
	}

	auto DialogueUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/RogueDialogue.RogueDialogue_C'"));
	if (EquipmentUIWidget.Succeeded()) {
		DialogueWidgetClass = DialogueUIWidget.Class;
	}

	auto RevivalUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/ReVival.ReVival_C'"));
	if (RevivalUIWidget.Succeeded()) {
		RevivalWidgetClass = RevivalUIWidget.Class;
	}

	auto TitleInRevivalUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/TitleInRevival.TitleInRevival_C'"));
	if (TitleInRevivalUIWidget.Succeeded()) {
		TitleInRevivalWidgetClass = TitleInRevivalUIWidget.Class;
	}

	auto KeyUIWidget = ConstructorHelpers::FClassFinder<UMyRogueWidget>
		(TEXT("WidgetBlueprint'/Game/UI/RogueTuto.RogueTuto_C'"));
	if (KeyUIWidget.Succeeded()) {
		KeyWidgetClass = KeyUIWidget.Class;
	}

	Widget_ChangedWidgetDelegate.BindUObject(this, &ACastle_in_DungeonGameModeBase::GetWidgetNumber);
}

void ACastle_in_DungeonGameModeBase::BeginPlay() {
	//ChangedWidget(TitleMenuWidgetClass);
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("GameModeOn")));
	URogueSaveGame* LoadGame = Cast<URogueSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (LoadGame == nullptr) {
		LoadGame = GetMutableDefault<URogueSaveGame>();
	}
	else {
		LoadGameData(LoadGame);
	}
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == TEXT("StartMap")) {
		StageIndex = 0;
	}
	if(GameStartCheck == 0)
		GetWidgetNumber(-1);
	else
		GetWidgetNumber(0);
	
	if(UGameplayStatics::GetCurrentLevelName(GetWorld()) != TEXT("Stage0") && UGameplayStatics::GetCurrentLevelName(GetWorld()) != TEXT("StartMap"))
		LevelLoading();
}

void ACastle_in_DungeonGameModeBase::LoadGameData(URogueSaveGame* LoadData) {
	URogueSaveGame* LoadGame = Cast<URogueSaveGame>(LoadData);
	StageIndex = LoadGame->StageIndex;
	StageSubIndex = LoadGame->StageSubIndex;
	FXSoundClass->Properties.Volume = LoadGame->FXSoundVolume;
	FOVValue = LoadGame->FOVValue;
	for(int i = 0; i < 3; i ++)
		StoryProgress[i] = LoadGame->StoryProgress[i];
	//myRogue->SetActorLocation(LoadGame->LastLocation);
}

void ACastle_in_DungeonGameModeBase::MainUIUpdate() {
	ChangedWidget(MainWidgetClass);
}

void ACastle_in_DungeonGameModeBase::RevivalUIUpdate() {
	if (RevivalTextAlphaMax == false)
		GetWorldTimerManager().SetTimer(RevivalAlphaPlusTimeHandle, this, &ACastle_in_DungeonGameModeBase::RevivalTextAlphaPlus, 0.02, true);
	else
		GetWorldTimerManager().SetTimer(RevivalAlphaMinusTimeHandle, this, &ACastle_in_DungeonGameModeBase::RevivalTextAlphaMinus, 0.02, true);
}

void ACastle_in_DungeonGameModeBase::TitleUIUpdate() {
	if (TitleBorderAlphaMax == false) {
		GetWorldTimerManager().SetTimer(TitleBorderBlackTimeHandle, this, &ACastle_in_DungeonGameModeBase::TitleBorderAlphaPlus, 0.02, true);
	}
}

void ACastle_in_DungeonGameModeBase::RevivalTextAlphaPlus() {
	if (RevivalTextAlphaValue >= 1.00f) {
		RevivalTextAlphaMax = true;
		GetWorldTimerManager().ClearTimer(RevivalAlphaPlusTimeHandle);
		RevivalUIUpdate();
	}
	else {
		RevivalTextAlphaValue += 0.01f;
		ChangedWidget(RevivalWidgetClass);
	}
}
void ACastle_in_DungeonGameModeBase::RevivalTextAlphaMinus() {
	if (RevivalTextAlphaMax == true && RevivalTextAlphaValue <= 0.00f) {
		GetWorldTimerManager().ClearTimer(RevivalAlphaMinusTimeHandle);
		GetWidgetNumber(1);
	}
	else {
		RevivalTextAlphaValue -= 0.01f;
		ChangedWidget(RevivalWidgetClass);
	}
}

void ACastle_in_DungeonGameModeBase::TitleBorderAlphaPlus() {
	if (TitleBorderAlphaValue >= 1.5f) {
		TitleBorderAlphaMax = true;
		GetWorldTimerManager().ClearTimer(TitleBorderBlackTimeHandle);
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Green, FString::Printf(TEXT("StageIndex : %d"), StageIndex));
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Green, FString::Printf(TEXT("StageSubIndex : %d"), StageIndex));
		switch (StageIndex) {
		case 0:
			UGameplayStatics::OpenLevel(this, TEXT("Stage0"), false);
			break;
		case 1:
			if (StageSubIndex == 0)
				UGameplayStatics::OpenLevel(this, TEXT("Stage1_0_0"), false);
			else if (StageSubIndex == 1)
				UGameplayStatics::OpenLevel(this, TEXT("Stage1_0_1"), false);
			else if (StageSubIndex == 2)
				UGameplayStatics::OpenLevel(this, TEXT("Stage1_0_2"), false);
			break;
		case 2:
			if (StageSubIndex == 0)
				UGameplayStatics::OpenLevel(this, TEXT("Stage2_0_0"), false);
			else if (StageSubIndex == 1)
				UGameplayStatics::OpenLevel(this, TEXT("Stage2_0_1"), false);
			else if (StageSubIndex == 2)
				UGameplayStatics::OpenLevel(this, TEXT("Stage2_0_2"), false);
			break;
		case 3:
			if (StageSubIndex == 0)
				UGameplayStatics::OpenLevel(this, TEXT("Stage3_0_0"), false);
			else if (StageSubIndex == 1)
				UGameplayStatics::OpenLevel(this, TEXT("Stage3_0_1"), false);
			else if (StageSubIndex == 2)
				UGameplayStatics::OpenLevel(this, TEXT("Stage3_0_2"), false);
			break;
		}
		//if()S
	}
	else {
		TitleBorderAlphaValue += 0.01f;
		ChangedWidget(TitleInRevivalWidgetClass);
	}
}

void ACastle_in_DungeonGameModeBase::GetStageIndex(int32 Index, int32 SubIndex) {
	StageIndex = Index;
	StageSubIndex = SubIndex;
}

void ACastle_in_DungeonGameModeBase::ChangedWidget(TSubclassOf<UUserWidget> NewWidgetclass) {
	ARogue* myRogue = Cast<ARogue>(DefaultPawnClass.GetDefaultObject());
	if (WidgetPageNumber == 0) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		TitleWidgetState = true;
		if (TitleMenuWidget != nullptr) {
			TitleMenuWidget->RemoveFromViewport();
			TitleMenuWidget = nullptr;
		}
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(10);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (TitleMenuWidgetClass != nullptr) {
			TabWidgetIn = false;
			TitleMenuWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (TitleMenuWidget != nullptr) {
				TitleMenuWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 1) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(0);
		MainWidgetState = true;
		if (MainWidget != nullptr) {
			MainWidget->RemoveFromViewport();
			MainWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(10);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (MainWidgetClass != nullptr) {
			TabWidgetIn = false;
			MainWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (MainWidget != nullptr) {
				MainWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 2){
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (ReSumeWidget != nullptr) {
			ReSumeWidget->RemoveFromViewport();
			ReSumeWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(10);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (ReSumeWidgetClass != nullptr) {
			ReSumeWidgetState = true;
			TabWidgetIn = false;
			ReSumeWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (ReSumeWidget != nullptr) {
				ReSumeWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 3) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (TabWidget != nullptr) {
			TabWidget->RemoveFromViewport();
			TabWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(10);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (TabWidgetClass != nullptr) {
			TabWidgetIn = true;
			TabWidgetState = true;
			TabWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (TabWidget != nullptr) {
				TabWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 4) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (StatWidget != nullptr) {
			StatWidget->RemoveFromViewport();
			StatWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(10);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (StatWidgetClass != nullptr) {
			StatWidgetState = true;
			StatWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (StatWidget != nullptr) {
				StatWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 5) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (EquipmentWidget != nullptr) {
			EquipmentWidget->RemoveFromViewport();
			EquipmentWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(10);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (EquipmentWidgetClass != nullptr) {
			EquipmentWidgetState = true;
			EquipmentWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (EquipmentWidget != nullptr) {
				EquipmentWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 7) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (BurningTotemWidget != nullptr) {
			BurningTotemWidget->RemoveFromViewport();
			BurningTotemWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(8);
		RemoveView(9);
		RemoveView(10);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (BurningTotemWidgetClass != nullptr) {
			BurningTotemWidgetState = true;
			BurningTotemWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (BurningTotemWidget != nullptr) {
				BurningTotemWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 8) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (ChangedWeaponWidget != nullptr) {
			ChangedWeaponWidget->RemoveFromViewport();
			ChangedWeaponWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(9);
		RemoveView(10);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (ChangedWeaponWidgetClass != nullptr) {
			ChangedWeaponWidgetState = true;
			ChangedWeaponWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (ChangedWeaponWidget != nullptr) {
				ChangedWeaponWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 9) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (ChangedAttackFormWidget != nullptr) {
			ChangedAttackFormWidget->RemoveFromViewport();
			ChangedAttackFormWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(10);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (ChangedAttackFormWidgetClass != nullptr) {
			ChangedAttackFormWidgetState = true;
			ChangedAttackFormWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (ChangedAttackFormWidget != nullptr) {
				ChangedAttackFormWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 10) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (AddAbilityWidget != nullptr) {
			AddAbilityWidget->RemoveFromViewport();
			AddAbilityWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (AddAbilityWidgetClass != nullptr) {
			AddAbilityWidgetState = true;
			AddAbilityWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (AddAbilityWidget != nullptr) {
				AddAbilityWidget->AddToViewport();
			}
		}
	}
	else if (WidgetPageNumber == 11) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (ChangedElementalFormWidget != nullptr) {
			ChangedElementalFormWidget->RemoveFromViewport();
			ChangedElementalFormWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		//RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (ChangedElementalFormWidgetClass != nullptr) {
			ChangedElementalFormWidgetState = true;
			ChangedElementalFormWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (ChangedElementalFormWidget != nullptr) {
				ChangedElementalFormWidget->AddToViewport();
				
			}
		}
	}
	else if (WidgetPageNumber == 99) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(0);
		if (DialogueWidget != nullptr) {
			DialogueWidget->RemoveFromViewport();
			DialogueWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(11);
		RemoveView(-1);
		RemoveView(-2);
		RemoveView(-3);
		if (DialogueWidgetClass != nullptr) {
			DialogueWidgetState = true;
			DialogueWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (DialogueWidget != nullptr) {
				DialogueWidget->AddToViewport();
				
			}
		}
	}
	if (WidgetPageNumber == -1) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(0);
		if (RevivalWidget != nullptr) {
			RevivalWidget->RemoveFromViewport();
			RevivalWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-2);
		RemoveView(-3);
		if (RevivalWidgetClass != nullptr) {
			RevivalWidgetState = true;
			RevivalWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (RevivalWidget != nullptr && WidgetPageNumber == -1) {
				
				RevivalWidget->AddToViewport();
				
			}
		}
	}
	if (WidgetPageNumber == -2) {
			//Widget_MouseCursorChangedDelegate.ExecuteIfBound(0);
			Widget_MouseCursorChangedDelegate.ExecuteIfBound(2);
		if (TitleInRevivalWidget != nullptr) {
			TitleInRevivalWidget->RemoveFromViewport();
			TitleInRevivalWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-3);
		if (TitleInRevivalWidgetClass != nullptr) {
			TitleInRevivalWidgetState = true;
			TitleInRevivalWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (TitleInRevivalWidget != nullptr) {
				
				TitleInRevivalWidget->AddToViewport();
				
			}
		}
	}
	if (WidgetPageNumber == -3) {
		Widget_MouseCursorChangedDelegate.ExecuteIfBound(1);
		if (KeyWidget != nullptr) {
			KeyWidget->RemoveFromViewport();
			KeyWidget = nullptr;
		}
		RemoveView(0);
		RemoveView(1);
		RemoveView(2);
		RemoveView(3);
		RemoveView(4);
		RemoveView(5);
		RemoveView(7);
		RemoveView(8);
		RemoveView(9);
		RemoveView(11);
		RemoveView(99);
		RemoveView(-1);
		RemoveView(-2);
		if (KeyWidgetClass != nullptr) {
			KeyWidgetState = true;
			KeyWidget = Cast<UMyRogueWidget>(CreateWidget(GetWorld(), NewWidgetclass));
			if (KeyWidget != nullptr) {
				
				KeyWidget->AddToViewport();
				
			}
		}
	}
}

void ACastle_in_DungeonGameModeBase::GetWidgetNumber(int32 PageNumber) {
	WidgetPageNumber = PageNumber;
	
	if (WidgetPageNumber == 0) {
		WidgetPush(TitleMenuWidgetClass);
	}
	else if (WidgetPageNumber == 1) {
		WidgetPush(MainWidgetClass);
	}
	else if (WidgetPageNumber == 2) {
		WidgetPush(ReSumeWidgetClass);
	}
	else if (WidgetPageNumber == 3) {
		WidgetPush(TabWidgetClass);
	}
	else if (WidgetPageNumber == 4) {
		WidgetPush(StatWidgetClass);
	}
	else if (WidgetPageNumber == 5) {
		WidgetPush(EquipmentWidgetClass);
	}
	else if (WidgetPageNumber == 7) {
		WidgetPush(BurningTotemWidgetClass);
	}
	else if (WidgetPageNumber == 8) {
		WidgetPush(ChangedWeaponWidgetClass);
	}
	else if (WidgetPageNumber == 9) {
		WidgetPush(ChangedAttackFormWidgetClass);
	}
	else if (WidgetPageNumber == 10) {
		WidgetPush(AddAbilityWidgetClass);
	}
	else if (WidgetPageNumber == 11) {
		WidgetPush(ChangedElementalFormWidgetClass);
	}
	else if (WidgetPageNumber == 99) {
		WidgetPush(DialogueWidgetClass);
	}
	else if (WidgetPageNumber == -1) {
		WidgetPush(RevivalWidgetClass);
	}
	else if (WidgetPageNumber == -2) {
		WidgetPush(TitleInRevivalWidgetClass);
	}
	else if (WidgetPageNumber == -3) {
		WidgetPush(KeyWidgetClass);
	}
}

void ACastle_in_DungeonGameModeBase::WidgetPop() {
	WidgetCount--;
	WidgetPageNumber = WidgetStackNumber[WidgetCount];
	ChangedWidget(WidgetStack[WidgetCount]);
}

void ACastle_in_DungeonGameModeBase::WidgetPush(TSubclassOf<UUserWidget> PushPage) {
	if(AddAbilityWidgetState != true)
		WidgetCount++;
	WidgetStack[WidgetCount] = PushPage;
	WidgetStackNumber[WidgetCount] = WidgetPageNumber;
	ChangedWidget(WidgetStack[WidgetCount]);
}

/*void ACastle_in_DungeonGameModeBase::StartSetting() {
	//Call_WeaponChangeDelegate.ExecuteIfBound(FMath::FRandRange(0, 9));
	WeaponElementChangeDelegate.ExecuteIfBound(0, true);
	TorchElementChangeDelegate.ExecuteIfBound(0, true);
}*/

void ACastle_in_DungeonGameModeBase::RemoveView(int32 StateNumber) {
	switch (StateNumber){
	case 0:
		if (TitleWidgetState == true) {
			TitleMenuWidget->RemoveFromViewport();
			TitleMenuWidget = nullptr;
			TitleWidgetState = false;
		}
		break;
	case 1:
		if (MainWidgetState == true) {
			MainWidget->RemoveFromViewport();
			MainWidget = nullptr;
			MainWidgetState = false;
		}
		break;
	case 2:
		if (ReSumeWidgetState == true) {
			ReSumeWidget->RemoveFromViewport();
			ReSumeWidget = nullptr;
			ReSumeWidgetState = false;
		}
		break;
	case 3:
		if (TabWidgetState == true) {
			TabWidget->RemoveFromViewport();
			TabWidget = nullptr;
			TabWidgetState = false;
		}
		break;
	case 4:
		if (StatWidgetState == true) {
			StatWidget->RemoveFromViewport();
			StatWidget = nullptr;
			StatWidgetState = false;
		}
		break;
	case 5:
		if (EquipmentWidgetState == true) {
			EquipmentWidget->RemoveFromViewport();
			EquipmentWidget = nullptr;
			EquipmentWidgetState = false;
		}
		break;
	case 7:
		if (BurningTotemWidgetState == true) {
			BurningTotemWidget->RemoveFromViewport();
			BurningTotemWidget = nullptr;
			BurningTotemWidgetState = false;
		}
		break;
	case 8:
		if (ChangedWeaponWidgetState == true) {
			ChangedWeaponWidget->RemoveFromViewport();
			ChangedWeaponWidget = nullptr;
			ChangedWeaponWidgetState = false;
		}
		break;
	case 9:
		if (ChangedAttackFormWidgetState == true) {
			ChangedAttackFormWidget->RemoveFromViewport();
			ChangedAttackFormWidget = nullptr;
			ChangedAttackFormWidgetState = false;
		}
		break;
	case 10:
		if (AddAbilityWidgetState == true) {
			AddAbilityWidget->RemoveFromViewport();
			AddAbilityWidget = nullptr;
			AddAbilityWidgetState = false;
		}
		break;
	case 11:
		if (ChangedElementalFormWidgetState == true) {
			ChangedElementalFormWidget->RemoveFromViewport();
			ChangedElementalFormWidget = nullptr;
			ChangedElementalFormWidgetState = false;
		}
		break;
	case 99:
		if (DialogueWidgetState == true) {
			DialogueWidget->RemoveFromViewport();
			DialogueWidget = nullptr;
			DialogueWidgetState = false;
		}
		break;
	case -1:
		if (RevivalWidgetState == true) {
			RevivalWidget->RemoveFromViewport();
			RevivalWidget = nullptr;
			RevivalWidgetState = false;
			
		}
		break;
	case -2:
		if (TitleInRevivalWidgetState == true) {
			TitleInRevivalWidget->RemoveFromViewport();
			TitleInRevivalWidget = nullptr;
			TitleInRevivalWidgetState = false;
		}
		break;
	case -3:
		if (KeyWidgetState == true) {
			KeyWidget->RemoveFromViewport();
			KeyWidget = nullptr;
			KeyWidgetState = false;
		}
		break;
	}
}

void ACastle_in_DungeonGameModeBase::LevelLoading() {

	//RogueLevel->NextDoorGuard();
	//RogueLevel->PreDoorGuard();
	for (int32 i = 0; i < 5; i++) {
		NextStageDirection[i] = false;
		for (int32 j = 0; j < 5; j++) {
			LevelFloorPoint1[i][j] = FTransform(FRotator(0, 0, 0), FVector(i * 8000, j * 8000, 5), FVector(1, 1, 1));
			LevelFloorCheck1[i][j] = true;
		}
	}
	//for (StageCount = 0; StageCount < 15; StageCount++) {
		LevelFloorCheck1[StageX][StageY] = false;
		RogueLevel = GetWorld()->SpawnActor<ARogueLevel>
			(ARogueLevel::StaticClass(), LevelFloorPoint1[StageX][StageY]);		
		LevelFloorCheck();
		RogueLevel->DoorGuard(NextDirection, NextDirectionIndex, PreDirection, PreDirectionIndex, true);
	
}

void ACastle_in_DungeonGameModeBase::LevelFloorCheck() {
	if (StageX < 4) {
		if (LevelFloorCheck1[StageX + 1][StageY] == true) {
			NextStageDirection[0] = true;
		}
		else
			NextStageDirection[0] = false;
	}
	if(StageY < 4){
		if (LevelFloorCheck1[StageX][StageY + 1] == true) {
			NextStageDirection[1] = true;
		}
		else
			NextStageDirection[1] = false;
	}
	if (StageX > 0) {
		if (LevelFloorCheck1[StageX - 1][StageY] == true) {
			NextStageDirection[2] = true;
		}
		else
			NextStageDirection[2] = false;
	}
	if (StageY > 0) {
		if (LevelFloorCheck1[StageX][StageY - 1] == true) {
			NextStageDirection[3] = true;
		}
		else
			NextStageDirection[3] = false;
	}
	int32 SelectDirection = FMath::FRandRange(0, 3);
	/*while (NextStageDirection[SelectDirection] == false) {
		SelectDirection = FMath::FRandRange(0, 3);
		if (NextStageDirection[0] == false && NextStageDirection[1] == false
			&& NextStageDirection[2] == false && NextStageDirection[3] == false)
			break;
	}*/
	if (StageCount != 0) {
		if (NextDirection == 0)
			PreDirection = 2;
		else if (NextDirection == 1)
			PreDirection = 3;
		else if (NextDirection == 2)
			PreDirection = 0;
		else if (NextDirection == 3)
			PreDirection = 1;
		PreDirectionIndex = NextDirectionIndex;
	}
	else {
		switch (StageSubIndex){
		case 0:
			PreDirection = 3;
			PreDirectionIndex = StageSubIndex;
			break;
		case 1:
			PreDirection = 3;
			PreDirectionIndex = StageSubIndex;
			break;
		case 2:
			PreDirection = 3;
			PreDirectionIndex = StageSubIndex;
			break;
		}
	}
	if (SelectDirection == 0) {
		StageX += 1;
		NextDirection = 1;
	}
	if (SelectDirection == 1) {
		StageY += 1;
		NextDirection = 2;
	}
	if (SelectDirection == 2) {
		StageX -= 1;
		NextDirection = 3;
	}
	if (SelectDirection == 3) {
		StageY -= 1;
		NextDirection = 0;
	}
	NextDirectionIndex = FMath::FRandRange(0, 3);
	for (int32 i = 0; i < 4; i++)
		NextStageDirection[i] = false;
}