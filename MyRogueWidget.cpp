// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRogueWidget.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateBrush.h"
//#include "RogueWeapon.h"
#include "Components/Button.h"
#include "GameFramework/Actor.h"

void UMyRogueWidget::WorldGameModeInit() {
	BonFireMenuIn = false;
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
	APawn* myPawn = Cast<APawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MyRogue = Cast<ARogue>(myPawn);
	//if (UGameplayStatics::GetCurrentLevelName(GetWorld()) != TEXT("StartMap"))
		//MyRogueState = Cast<ARogueState>(myPawn->GetPlayerState());
	//AActor* WeaponActor = UGameplayStatics::GetActorOfClass(TheWorld, TSubclassOf<AActor>(ARogueWeapon::StaticClass()));
	//RogueWeapon = Cast<ARogueWeapon>(WeaponActor);
}

void UMyRogueWidget::NativeConstruct() {
	Super::NativeConstruct();
	//UStaticMesh* NewWeapon = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, WeaponReference));
	USoundCue* NewSound = Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, TEXT("SoundCue'/Game/Sound/SoundQue/Select/Select01_Cue.Select01_Cue'")));
	if (NewSound) {
		SelectSound = NewSound;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("WidgetOn")));

	ElementIconInit();
	AbilityListString();
	WeaponListString();
	AttackFormString();
	ElementString();
	CinzelDir = TEXT("Font'/Game/Fonts/Cinzel-Regular_Font.Cinzel-Regular_Font'");
	UseCinzelFont = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), NULL, CinzelDir));
	UseNanumMyeonjo = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), NULL,
		TEXT("Font'/Game/Fonts/NanumMyeongjo-Regular_Font.NanumMyeongjo-Regular_Font'")));
	UseCardo = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), NULL,
		TEXT("Font'/Game/Fonts/Cardo-Regular_Font.Cardo-Regular_Font'")));
	WorldGameModeInit();
	DelegateInit();
	TitleMenuInit();
	MainMenuInit();
	ReSumeMenuInit();
	TabMenuInit();
	StatMenuInit();
	EquipMenuInit();
	GameStateInit();
	BurningTotemMenuInit();
	ChangedWeaponMenuInit();
	ChangedAttackMotionInit();
	ChangedElementalInit();
	AddAbilityMenuInit();
	DialogueMenuInit();
	RevivalMenuInit();
	TitleInRevivalMenuInit();
	WeaponImagesRefInit();
	ToolTipInit();
	PageInit();
	ControllUIInit();
	//MyGameMode->Widget_StatDataDelegate.BindUObject(this, &UMyRogueWidget::GetRogueStatValue);
	//MyGameMode->Widget_GetRogueEquipmentDelegate.BindUObject(this, &UMyRogueWidget::GetRogueEquipmentValue);
	//MyGameMode->Widget_AbilityListDelegate.BindUObject(this, &UMyRogueWidget::GetRogueAbilityIndexAndString);
	//MyGameMode->Widget_ViewRogueHpDelegate.BindUObject(this, &UMyRogueWidget::ViewRogueHp);
}

void UMyRogueWidget::DelegateInit() {
	MyGameMode->Widget_GetRogueHpDelegate.BindUObject(this, &UMyRogueWidget::GetRogueHpValue);
	MyGameMode->Widget_GetRogueDataDelegate.BindUObject(this, &UMyRogueWidget::GetRogueDataValue);
	MyGameMode->Widget_GetRogueKarmaDelegate.BindUObject(this, &UMyRogueWidget::GetRogueKarmaValue);
	MyGameMode->Widget_StatDataDelegate.BindUObject(this, &UMyRogueWidget::GetRogueStatValue);
	MyGameMode->Widget_GetRogueEquipmentDelegate.BindUObject(this, &UMyRogueWidget::GetRogueEquipmentValue);
	MyGameMode->Widget_AbilityListDelegate.BindUObject(this, &UMyRogueWidget::GetRogueAbilityIndexAndString);
	MyGameMode->Return_RogueTakeAbilityDelegate.BindUObject(this, &UMyRogueWidget::Return_HaveAbilityList);
	MyGameMode->Return_RogueTakeHaveWeaponDelegate.BindUObject(this, &UMyRogueWidget::Return_HaveWeaponList);
	MyGameMode->Return_RogueUseWeaponReferenceDelegate.BindUObject(this, &UMyRogueWidget::Receive_ReturnRogueUseWeaponRef);
	MyGameMode->Return_RogueTakeAttackFormDelegate.BindUObject(this, &UMyRogueWidget::Return_HaveAttackFormList);
	MyGameMode->Return_RogueTakeElementalDelegate.BindUObject(this, &UMyRogueWidget::Return_HaveElementalList);
	MyGameMode->Widget_ReturnGameStateWidgetDelegate.BindUObject(this, &UMyRogueWidget::Return_GameStateData);
}

void UMyRogueWidget::PageInit() {
	 PageTitle = false;
	 PageMain = false;
	 PageStat = false;
	 PageEquip = false;
	 TabMenuIn = false;
}

void UMyRogueWidget::TitleMenuInit() {
	NewGameButton = Cast<UButton>(GetWidgetFromName(TEXT("NewGameButtons")));
	ExitGameButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitGameButtons")));
	Option_Buttons = Cast<UButton>(GetWidgetFromName(TEXT("Option_Button")));
	if (NewGameButton != nullptr) {
		NewGameButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetRogueMain);
		PageTitle = true;
		PageMain = true;
	}
	if (ExitGameButton != nullptr)
		ExitGameButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetExitGame);
	if (Option_Buttons != nullptr)
		Option_Buttons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetControllOptionMenu);
}

void UMyRogueWidget::TitleInRevivalMenuInit() {
	TitleBorder = Cast<UBorder>(GetWidgetFromName(TEXT("TitleBlackBorder")));
	if (TitleBorder != nullptr) {
		TitleBorder->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, MyGameMode->TitleBorderAlphaValue));
		
		if (MyGameMode->TitleBorderAlphaMax == false && MyGameMode->TitleBorderAlphaValue == 0.00f) {
			
			MyGameMode->TitleUIUpdate();
		}
	}
}

void UMyRogueWidget::MainMenuInit() {
	FString TaskValueText;
	RogueHPValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("RogueHpBlock")));
	RogueDataValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("RogueDataBlock")));
	RogueKarmaValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("RogueKarmaBlock")));
	PressKeyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("PressKeyTextBlock")));
	TaskBoxs = Cast<UTextBlock>(GetWidgetFromName(TEXT("TaskBox")));
	TaskValues = Cast<UTextBlock>(GetWidgetFromName(TEXT("TaskValue")));
	if (RogueHPValue != nullptr && RogueDataValue != nullptr && RogueKarmaValue != nullptr) {
		PageMain = true;
		MyGameMode->Widget_RogueUIValueInitDelegate.ExecuteIfBound();
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("Equip %d"), MyRogue->MyRogueState->TotalEquipCount));
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("DialogueTu %d"), MyRogue->MyRogueState->DialogueTutorialCount));
		switch (MyRogue->MyRogueState->TaskLevel) {
		case 0:
			TaskValueText = FString::Printf(TEXT("Explore the Castle."));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 1:
			TaskValueText = FString::Printf(TEXT("Add Abilities From the Crucible"));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 2:
			TaskValueText = FString::Printf(TEXT("Carefully Explore the Castle"));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 3:
			TaskValueText = FString::Printf(TEXT("Find the Dungeon Maze."));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 4:
			TaskValueText = FString::Printf(TEXT("Find the Dungeon Hall."));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 5:
			TaskValueText = FString::Printf(TEXT("Find the Dungeon Underpass."));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 6:
			TaskValueText = FString::Printf(TEXT("Clear the Maze."));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 7:
			TaskValueText = FString::Printf(TEXT("Clear the Hall."));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 8:
			TaskValueText = FString::Printf(TEXT("Clear the Underpass."));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 9:
			TaskValueText = FString::Printf(TEXT("Find Another Dungeon."));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		case 10:
			TaskValueText = FString::Printf(TEXT("Keep Exploring.."));
			TaskValues->SetText(FText::FromString(TaskValueText));
			break;
		}

		/*
		RogueHpString = FString::Printf(TEXT("%d"), RogueHp);
		if(PageMain == true)
			RogueHPValue->SetText(FText::FromString(RogueHpString));
		if (MyRogue->MyRogueState->DialogueState[0] == 1) {
			FText PressTextValue = FText::FromString(FString::Printf(TEXT("Press 'F' Key")));
			PressKeyText->SetText(PressTextValue);
		}
		else {
			FText PressTextValue = FText::FromString(FString::Printf(TEXT("")));
			PressKeyText->SetText(PressTextValue);
		}
		if (MyRogue->BeepOn == true) {
			GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("DialogueState  %d"), MyRogue->MyRogueState->DialogueState[0]));
			if (MyRogue->MyRogueState->DialogueState[0] == 1) {
				MyRogue->MyRogueState->DialogueState[0] = 2;
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("F___________Off")));
			FText PressTextValue = FText::FromString(FString::Printf(TEXT("")));
			PressKeyText->SetText(PressTextValue);
		}
	}*/
	}
}

void UMyRogueWidget::ReSumeMenuInit() {
	ReSumeButton = Cast<UButton>(GetWidgetFromName(TEXT("ReSumeButtons")));
	ReStartButton = Cast<UButton>(GetWidgetFromName(TEXT("ReStartButtons")));
	TitleMenuButton = Cast<UButton>(GetWidgetFromName(TEXT("TitleMenuButtons")));
	GameExitButton = Cast<UButton>(GetWidgetFromName(TEXT("GameExitButtons")));

	if (ReSumeButton != nullptr)
		ReSumeButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetKeyMenu);
	if (ReStartButton != nullptr)
		ReStartButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetNewGame);
	if (TitleMenuButton != nullptr)
		TitleMenuButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetTitleMenu);
	if (GameExitButton != nullptr) {
		PageMain = false;
		GameExitButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetExitGame);
	}
}

void UMyRogueWidget::ControllUIInit() {
	ControllBack = Cast<UButton>(GetWidgetFromName(TEXT("ControllBackButton")));
	SoundSlider = Cast<USlider>(GetWidgetFromName(TEXT("SoundSlide")));
	SoundVolumeValues = Cast<UTextBlock>(GetWidgetFromName(TEXT("SoundVolumeValue")));
	FOVSlider = Cast<USlider>(GetWidgetFromName(TEXT("FOVSlide")));
	FOVValues = Cast<UTextBlock>(GetWidgetFromName(TEXT("FOVValue")));
	CheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBoxs")));
	KorCheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("KoreanCheck")));
	EngCheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("EnglishCheck")));
	if (CheckBox != nullptr) {
		if(MyRogue->ViewArm->bUsePawnControlRotation == true)
			CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		else
			CheckBox->SetCheckedState(ECheckBoxState::Checked);
		CheckBox->OnCheckStateChanged.AddDynamic(this, &UMyRogueWidget::ChangeHeadShake);
	}
	if (KorCheckBox != nullptr && EngCheckBox != nullptr) {
		if (MyGameMode->LanguageType == 0) {
			KorCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
			EngCheckBox->SetCheckedState(ECheckBoxState::Checked);
		}
		else if (MyGameMode->LanguageType == 1) {
			KorCheckBox->SetCheckedState(ECheckBoxState::Checked);
			EngCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		}
		EngCheckBox->OnCheckStateChanged.AddDynamic(this, &UMyRogueWidget::ChangeLanguageEng);
		KorCheckBox->OnCheckStateChanged.AddDynamic(this, &UMyRogueWidget::ChangeLanguageKor);
	}
	
	/*if (CheckBox2 != nullptr) {
		if (MyRogue->GetRollingTrdCamera() == true)
			CheckBox2->SetCheckedState(ECheckBoxState::Checked);
		else
			CheckBox2->SetCheckedState(ECheckBoxState::Unchecked);
		CheckBox2->OnCheckStateChanged.AddDynamic(this, &UMyRogueWidget::ChangeTrdCamera);
	}*/
	
	if (ControllBack != nullptr) {
		ControllBack->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
	}
	if (SoundSlider != nullptr) {
		SoundSlider->SetValue(MyGameMode->FXSoundClass->Properties.Volume);
		SoundSlider->OnValueChanged.AddDynamic(this, &UMyRogueWidget::SetSoundVolume);
	}
	if (SoundVolumeValues != nullptr) {
		//FString ValueString = 
		FText ValueText = FText::FromString(FString::Printf(TEXT("%.0f"), SoundSlider->GetValue()*100.f/3.f));
		SoundVolumeValues->SetText(ValueText);
	}
	if (FOVSlider != nullptr) {
		FOVSlider->SetValue(MyGameMode->FOVValue/100.f);
		FOVSlider->OnValueChanged.AddDynamic(this, &UMyRogueWidget::SetFOVVolume);
	}
	if (FOVValues != nullptr) {
		FText ValueText = FText::FromString(FString::Printf(TEXT("%.0f"), FOVSlider->GetValue()*100.f));
		FOVValues->SetText(ValueText);
	}

}

void UMyRogueWidget::TabMenuInit() {
	ViewStatButton = Cast<UButton>(GetWidgetFromName(TEXT("ViewStatButtons")));
	ViewEquipButton = Cast<UButton>(GetWidgetFromName(TEXT("ViewEquipButtons")));
	ViewGameStateButton = Cast<UButton>(GetWidgetFromName(TEXT("ViewGameStateButtons")));
	TabBackButton = Cast<UButton>(GetWidgetFromName(TEXT("Tab_BackMainButtons")));

	if (ViewStatButton != nullptr)
		ViewStatButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetRogueStat);
	if (ViewEquipButton != nullptr)
		ViewEquipButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetRogueEquip);
	if (ViewGameStateButton != nullptr)
		ViewGameStateButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetGameState);
	if (TabBackButton != nullptr) {
		TabMenuIn = true;
		PageMain = false;
		TabBackButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
		
	}
}

void UMyRogueWidget::StatMenuInit() {
	RogueStatMaxHPValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxHpTextBlock")));
	RogueStatTotalDataValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TotalDataTextBlock")));
	RogueStatTotalKillValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TotalKillTextBlock")));
	RogueStatMoveSpeedValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("MoveSpeedTextBlock")));
	RogueStatSuperArmorValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("SuperArmorTextBlock")));
	RogueStatWeaponSpeedValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponSpeedTextBlock")));
	RogueStatWeaponLevelValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponLevelTextBlock")));
	RogueStatTorchLevelValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TorchLevelTextBlock")));
	RogueStatElementLevelValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("ElementLevelTextBlock")));
	RogueStatWeaponPhysicsDamegeValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponPhysicsDamegeTextBlock")));
	RogueStatWeaponElementDamegeValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponElementDamegeTextBlock")));
	RogueStatWeaponEffectPercentageValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponElementPercentageTextBlock")));
	RogueStatTorchStabDamegeValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TorchStabDamegeTextBlock")));
	RogueStatTorchElementDamegeValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TorchElementDamegeTextBlock")));
	RogueStatTorchEffectDamegeValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TorchEffectDamegeTextBlock")));
	RogueStatTorchEffectPercentageValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TorchEffectPercentageTextBlock")));
	RogueStatBackButton = Cast<UButton>(GetWidgetFromName(TEXT("RogueStatButton")));

	if (RogueStatBackButton != nullptr) {
		PageStat = true;
		
		RogueStatBackButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
		MyGameMode->Widget_CallStatWidgetDelegate.ExecuteIfBound();
		PageMain = false;
	}
}

void UMyRogueWidget::GameStateInit() {
	KillCountValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("KillCountBlock")));
	DeathCountValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("DeathCountBlock")));
	TotalDataValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TotalDataBlock")));
	UsedDataValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("UsedDataBlock")));
	DungeonClearValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("DungeonClearBlock")));
	GameStateBackButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStateButtons")));
	if (GameStateBackButton != nullptr) {
		GameStateBackButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
		MyGameMode->Widget_CallGameStateWidgetDelegate.ExecuteIfBound();
	}
}

void UMyRogueWidget::EquipMenuInit() {

	EquipWeaponValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("EquipWeaponTextBolck")));
	WeaponElementValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponElementTextBlock")));
	TorchElementValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TorchElementTextBlock")));
	AttackFormIValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackFormITextBlock")));
	AttackFormIIValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackFormIITextBlock")));
	AttackFormIIIValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackFormIIITextBlock")));
	RogueAbilityList = Cast<UScrollBox>(GetWidgetFromName(TEXT("AbilityLists")));
	RogueEquipmentBackButton = Cast<UButton>(GetWidgetFromName(TEXT("RogueEquipmentButtons")));

	if (RogueEquipmentBackButton != nullptr) {
		PageEquip = true;
		RogueEquipmentBackButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
		MyGameMode->Widget_CallEquipmentWidgetDelegate.ExecuteIfBound();
		RogueAbilityList->ClearChildren();
		MyGameMode->Widget_CallAbilityListDelegate.ExecuteIfBound();
		for (int i = 0; i <= AbilityLastIndex; i++) {
			GetRogueAbilityList(i, AbilityNames[i]);

		}
		PageMain = false;
	}
}

void UMyRogueWidget::BurningTotemMenuInit() {

	ChangedWeaponButtons = Cast<UButton>(GetWidgetFromName(TEXT("ChangedWeaponButton")));
	ChangedAttackFormButtons = Cast<UButton>(GetWidgetFromName(TEXT("ChangedAttackmotionButton")));
	ChangedElementalButtons = Cast<UButton>(GetWidgetFromName(TEXT("ChangeElmentalButton")));
	AddAbilityButtons = Cast<UButton>(GetWidgetFromName(TEXT("AddAbilityButton")));
	BurningTotemBackButtons = Cast<UButton>(GetWidgetFromName(TEXT("BonFire_BackMainButton")));

	if (BurningTotemBackButtons != nullptr) {
		MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
		PageMain = false;
		BonFireMenuIn = true;
		BurningTotemBackButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
		ChangedWeaponButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetChangedWeaponMenu);
		ChangedAttackFormButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetChangedAttackFormMenu);
		ChangedElementalButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetChangedElementalMenu);
		AddAbilityButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetAddAbilityMenu);
		
	}
}

void UMyRogueWidget::ChangedWeaponMenuInit() {
	
	SelectWeaponButtons = Cast<UButton>(GetWidgetFromName("ChangedWeaponSelectButton"));
	ChangedWeaponBackButtons = Cast<UButton>(GetWidgetFromName("ChangedWeaponBackButton"));
	ChangedWeaponList = Cast<UScrollBox>(GetWidgetFromName("WeaponList"));
	WeaponAttributes1 = Cast<UTextBlock>(GetWidgetFromName("WeaponAttribute1"));
	WeaponAttributes2 = Cast<UTextBlock>(GetWidgetFromName("WeaponAttribute2"));
	WeaponAttributes3 = Cast<UTextBlock>(GetWidgetFromName("WeaponAttribute3"));
	WeaponImages = Cast<UImage>(GetWidgetFromName("WeaponImage"));
	WeaponIcons1 = Cast<UImage>(GetWidgetFromName("WeaponIcon1"));
	WeaponIcons2 = Cast<UImage>(GetWidgetFromName("WeaponIcon2"));
	if (ChangedWeaponBackButtons != nullptr) {
		MyGameMode->Call_RogueUseWeaponReferenceDelegate.ExecuteIfBound();
		RogueUseWeaponRefCheck();
		PageMain = false;
		SelectWeaponButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::SelectWeaponButtonFuntion);
		ChangedWeaponBackButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
		ChangedWeaponList->ClearChildren();
		Call_HaveWeaponList();
	}
}

void UMyRogueWidget::ChangedAttackMotionInit() {
	ChangedAttackFromList = Cast<UScrollBox>(GetWidgetFromName("AttackFormList"));
	SlashListButtons = Cast<UButton>(GetWidgetFromName("SlashListButton"));
	SmashListButtons = Cast<UButton>(GetWidgetFromName("SmashListButton"));
	StabListButtons = Cast<UButton>(GetWidgetFromName("StabListButton"));
	SpecialListButtons = Cast<UButton>(GetWidgetFromName("SpecialListButton"));
	SelectedAttackFormSlotButtons1 = Cast<UButton>(GetWidgetFromName("SelectedAttackFormSlotButton1"));
	SelectedAttackFormSlotButtons2 = Cast<UButton>(GetWidgetFromName("SelectedAttackFormSlotButton2"));
	SelectedAttackFormSlotButtons3 = Cast<UButton>(GetWidgetFromName("SelectedAttackFormSlotButton3"));

	SelectedAttackForm1s = Cast<UTextBlock>(GetWidgetFromName("SelectAttackForm1"));
	SelectedAttackForm2s = Cast<UTextBlock>(GetWidgetFromName("SelectAttackForm2"));
	SelectedAttackForm3s = Cast<UTextBlock>(GetWidgetFromName("SelectAttackForm3"));
	SelectAttackFormButtons = Cast<UButton>(GetWidgetFromName("ChangedAttackFormSelectButton"));
	ChangedAttackFormBackButtons = Cast<UButton>(GetWidgetFromName("ChangedAttackFormBackButton"));
	//SelectAttackFormInitButtons = Cast<UButton>(GetWidgetFromName("SelectAttackFormInitButton"));
	SelectedAttackFormSlotOverlay1 = Cast<UOverlay>(GetWidgetFromName("SelectedAttackFormOverlayBox1"));
	SelectedAttackFormSlotOverlay2 = Cast<UOverlay>(GetWidgetFromName("SelectedAttackFormOverlayBox2"));
	SelectedAttackFormSlotOverlay3 = Cast<UOverlay>(GetWidgetFromName("SelectedAttackFormOverlayBox3"));
	if (ChangedAttackFormBackButtons != nullptr) {
		PageEquip = false;
		ChangedAttackFromList->ClearChildren();
		SelectedAttackFormSlotOne(); // 기본값
		MyGameMode->Widget_CallEquipmentWidgetDelegate.ExecuteIfBound();
		SelectedAttackForm1s->SetText(FText::FromString(RogueEquipmentString[3]));
		SelectedAttackForm2s->SetText(FText::FromString(RogueEquipmentString[4]));
		SelectedAttackForm3s->SetText(FText::FromString(RogueEquipmentString[5]));
		AttackFormPlayer[0] = Cast<UMediaPlayer>(StaticLoadObject(UMediaPlayer::StaticClass(), NULL,
			TEXT("MediaPlayer'/Game/AttackImage/AttackForm1_Media.AttackForm1_Media'")));
		AttackFormPlayer[1] = Cast<UMediaPlayer>(StaticLoadObject(UMediaPlayer::StaticClass(), NULL,
			TEXT("MediaPlayer'/Game/AttackImage/AttackForm2_Media.AttackForm2_Media'")));
		AttackFormPlayer[2] = Cast<UMediaPlayer>(StaticLoadObject(UMediaPlayer::StaticClass(), NULL,
			TEXT("MediaPlayer'/Game/AttackImage/AttackForm3_Media.AttackForm3_Media'")));
		AttackFormTexture[0] = Cast<UMediaTexture>(StaticLoadObject(UMediaTexture::StaticClass(), NULL,
			TEXT("MediaTexture'/Game/AttackImage/AttackForm1_Texture.AttackForm1_Texture'")));
		AttackFormTexture[1] = Cast<UMediaTexture>(StaticLoadObject(UMediaTexture::StaticClass(), NULL,
			TEXT("MediaTexture'/Game/AttackImage/AttackForm2_Texture.AttackForm2_Texture'")));
		AttackFormTexture[2]= Cast<UMediaTexture>(StaticLoadObject(UMediaTexture::StaticClass(), NULL,
			TEXT("MediaTexture'/Game/AttackImage/AttackForm3_Texture.AttackForm3_Texture'")));
		SelectAttackFormButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::SelectAttackFormButtonFuntion);
		ChangedAttackFormBackButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
		SlashListButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetSlashList);
		SmashListButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetSmashList);
		StabListButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetStabList);
		SpecialListButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetSpecialList);
		SelectedAttackFormSlotButtons1->OnClicked.AddDynamic(this, &UMyRogueWidget::SelectedAttackFormSlotOne);
		SelectedAttackFormSlotButtons2->OnClicked.AddDynamic(this, &UMyRogueWidget::SelectedAttackFormSlotTwo);
		SelectedAttackFormSlotButtons3->OnClicked.AddDynamic(this, &UMyRogueWidget::SelectedAttackFormSlotThree);
		for (int i = 0; i < 3; i++) {
			SelectedAttackFormNumber[i] = RogueEquipmentAttackForm[i];
			SelectedAttackFormIndex[i] = RogueEquipmentAttackFormIndex[i];
			/*AttackSource[i] = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
				RogueEquipmentAttackFormString[i]));
			AttackFormTexture[i]->SetMediaPlayer(AttackFormPlayer[i]);
			AttackFormPlayer[i]->OpenSource(AttackSource[i]);*/
		}
	}
}

void UMyRogueWidget::ChangedElementalInit() {
	
	StrenghtIcons = Cast<UImage>(GetWidgetFromName(TEXT("StrenghtIcon")));
	HeatIcons = Cast<UImage>(GetWidgetFromName(TEXT("HeatIcon")));
	ColdIcons = Cast<UImage>(GetWidgetFromName(TEXT("ColdIcon")));
	PoisonIcons = Cast<UImage>(GetWidgetFromName(TEXT("PoisonIcon")));
	ElectricIcons = Cast<UImage>(GetWidgetFromName(TEXT("ElectricIcon")));
	
	StrenghtIcons2 = Cast<UImage>(GetWidgetFromName(TEXT("StrenghtIcon_1")));
	HeatIcons2 = Cast<UImage>(GetWidgetFromName(TEXT("HeatIcon_1")));
	ColdIcons2 = Cast<UImage>(GetWidgetFromName(TEXT("ColdIcon_1")));
	PoisonIcons2 = Cast<UImage>(GetWidgetFromName(TEXT("PoisonIcon_1")));
	ElectricIcons2 = Cast<UImage>(GetWidgetFromName(TEXT("ElectricIcon_1")));

	SelectWeaponElementalIcons = Cast<UImage>(GetWidgetFromName(TEXT("SelectedWeaponElementalIcon")));
	SelectTorchElementalIcons = Cast<UImage>(GetWidgetFromName(TEXT("SelectedTorchElementalIcon")));
	WeaponElementalButton[0] = Cast<UButton>(GetWidgetFromName(TEXT("StrenghtWeaponButton")));
	WeaponElementalButton[1] = Cast<UButton>(GetWidgetFromName(TEXT("HeatWeaponButton")));
	WeaponElementalButton[2] = Cast<UButton>(GetWidgetFromName(TEXT("ColdWeaponButton")));
	WeaponElementalButton[3] = Cast<UButton>(GetWidgetFromName(TEXT("PoisonWeaponButton")));
	WeaponElementalButton[4] = Cast<UButton>(GetWidgetFromName(TEXT("ElectricWeaponButton")));
	WeaponElementalText[0] = Cast<UTextBlock>(GetWidgetFromName(TEXT("StrenghtWeaponText")));
	WeaponElementalText[1] = Cast<UTextBlock>(GetWidgetFromName(TEXT("HeatWeaponText")));
	WeaponElementalText[2] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ColdWeaponText")));
	WeaponElementalText[3] = Cast<UTextBlock>(GetWidgetFromName(TEXT("PoisonWeaponText")));
	WeaponElementalText[4] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ElectricWeaponText")));
	TorchElementalButton[0] = Cast<UButton>(GetWidgetFromName(TEXT("StrenghtTorchButton")));
	TorchElementalButton[1] = Cast<UButton>(GetWidgetFromName(TEXT("HeatTorchButton")));
	TorchElementalButton[2] = Cast<UButton>(GetWidgetFromName(TEXT("ColdTorchButton")));
	TorchElementalButton[3] = Cast<UButton>(GetWidgetFromName(TEXT("PoisonTorchButton")));
	TorchElementalButton[4] = Cast<UButton>(GetWidgetFromName(TEXT("ElectricTorchButton")));
	TorchElementalText[0] = Cast<UTextBlock>(GetWidgetFromName(TEXT("StrenghtTorchText")));
	TorchElementalText[1] = Cast<UTextBlock>(GetWidgetFromName(TEXT("HeatTorchText")));
	TorchElementalText[2] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ColdTorchText")));
	TorchElementalText[3] = Cast<UTextBlock>(GetWidgetFromName(TEXT("PoisonTorchText")));
	TorchElementalText[4] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ElectricTorchText")));
	ElementalText[0] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ElementalAttribute1")));
	ElementalText[1] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ElementalAttribute2")));
	ElementalText[2] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ElementalAttribute3")));
	ElementalText[3] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ElementalAttribute4")));
	ElementalText[4] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ElementalAttribute5")));
	ElementalText[5] = Cast<UTextBlock>(GetWidgetFromName(TEXT("ElementalAttribute6")));
	ElementPhase[0] = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponElementPhaseText")));
	ElementPhase[1] = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeaponElementPhaseText_1")));
	
	ChangedElementalSelectButtons = Cast<UButton>(GetWidgetFromName(TEXT("ChangedElementalSelectButton")));
	ChangedElementalBackButtons = Cast<UButton>(GetWidgetFromName(TEXT("ChangedElemantalBackButton")));

	if (ChangedElementalBackButtons != nullptr) {
		ChangedElementalBackButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
		ChangedElementalSelectButtons->OnClicked.AddDynamic(this, &UMyRogueWidget::SelectElementalButton);
		MyGameMode->Widget_CallEquipmentWidgetDelegate.ExecuteIfBound();
		ElementalPhaseCheck();
		for (int i = 1; i < 5; i++) {
			if (i < 2) {
				ElementPhase[0]->SetText(FText::FromString(FString::Printf(TEXT("Phase  %d"), WeaponElementalPhase)));
				ElementPhase[1]->SetText(FText::FromString(FString::Printf(TEXT("Phase  %d"), TorchElementalPhase)));
			}
			WeaponElementalButton[i]->SetIsEnabled(false);
			TorchElementalButton[i]->SetIsEnabled(false);
			WeaponElementalText[i]->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.1f)));
			TorchElementalText[i]->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.1f)));
		}
		StrenghtIcons->SetBrushFromTexture(SelectElementIcon[0][0]);
		HeatIcons->SetBrushFromTexture(SelectElementIcon[0][1]);
		ColdIcons->SetBrushFromTexture(SelectElementIcon[0][2]);
		PoisonIcons->SetBrushFromTexture(SelectElementIcon[0][3]);
		ElectricIcons->SetBrushFromTexture(SelectElementIcon[0][4]);

		StrenghtIcons2->SetBrushFromTexture(SelectElementIcon[1][0]);
		HeatIcons2->SetBrushFromTexture(SelectElementIcon[1][1]);
		ColdIcons2->SetBrushFromTexture(SelectElementIcon[1][2]);
		PoisonIcons2->SetBrushFromTexture(SelectElementIcon[1][3]);
		ElectricIcons2->SetBrushFromTexture(SelectElementIcon[1][4]);

		for (int i = 0; i < 5; i++) {
			WeaponElementalText[i]->SetText(FText::FromString(SelectElementString[0][i]));
			TorchElementalText[i]->SetText(FText::FromString(SelectElementString[1][i]));
		}
		
		ElementalText[0]->SetText(FText::FromString(RogueEquipmentString[1]));
		ElementalText[3]->SetText(FText::FromString(RogueEquipmentString[2]));
		
		RogueWeaponElementalNumber = RogueEquipNumberData[1];
		RogueTorchElementalNumber = RogueEquipNumberData[2];
		if (RogueEquipmentString[1] == TEXT("Physical") || 
			RogueEquipmentString[1] == TEXT("Strenght") ||
			RogueEquipmentString[1] == TEXT("Smite")) {
			
			SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][0]);
			ElementalText[1]->SetText(FText::FromString(TEXT("High Damage")));
			ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Stun")));
		}
		else if (RogueEquipmentString[1] == TEXT("Heat") ||
			RogueEquipmentString[1] == TEXT("Fire") || 
			RogueEquipmentString[1] == TEXT("Flame")) {
			SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][1]);
			ElementalText[1]->SetText(FText::FromString(TEXT("Dot & Nuke")));
			ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Burn")));
		}
		else if (RogueEquipmentString[1] == TEXT("Chill") || 
			RogueEquipmentString[1] == TEXT("Frost") || 
			RogueEquipmentString[1] == TEXT("Freeze")) {
			SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][2]);
			ElementalText[1]->SetText(FText::FromString(TEXT("Stack & Slow")));
			ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Chilling")));
		}
		else if (RogueEquipmentString[1] == TEXT("Toxin") ||
			RogueEquipmentString[1] == TEXT("Poison") ||
			RogueEquipmentString[1] == TEXT("Venom")) {
			SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][3]);
			ElementalText[1]->SetText(FText::FromString(TEXT("Stack & Dot")));
			ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Toxicosis")));
		}
		else if (RogueEquipmentString[1] == TEXT("Electric") ||
			RogueEquipmentString[1] == TEXT("Lightning") ||
			RogueEquipmentString[1] == TEXT("Thunderbolt")) {
			SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][4]);
			ElementalText[1]->SetText(FText::FromString(TEXT("Stack & HighDamege")));
			ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Charging")));
		}
		
		
		if (RogueEquipmentString[2] == TEXT("Physical") ||
			RogueEquipmentString[2] == TEXT("Strenght") ||
			RogueEquipmentString[2] == TEXT("Smite")) {
			
			SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][0]);
			ElementalText[4]->SetText(FText::FromString(TEXT("Easy Conditions")));
			ElementalText[5]->SetText(FText::FromString(TEXT("Ability : LevelDamege")));
		}
		else if (RogueEquipmentString[2] == TEXT("Heat") ||
			RogueEquipmentString[2] == TEXT("Fire") ||
			RogueEquipmentString[2] == TEXT("Flame")) {
			SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][1]);
			ElementalText[4]->SetText(FText::FromString(TEXT("HighRange & Nuke")));
			ElementalText[5]->SetText(FText::FromString(TEXT("Ability : BurnExplosion")));
		}
		else if (RogueEquipmentString[2] == TEXT("Chill") ||
			RogueEquipmentString[2] == TEXT("Frost") ||
			RogueEquipmentString[2] == TEXT("Freeze")) {
			SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][2]);
			ElementalText[4]->SetText(FText::FromString(TEXT("Enhanced Stack & Nuke")));
			ElementalText[5]->SetText(FText::FromString(TEXT("Ability : Freeze & IceBlast")));
		}
		else if (RogueEquipmentString[2] == TEXT("Toxin") ||
			RogueEquipmentString[2] == TEXT("Poison") ||
			RogueEquipmentString[2] == TEXT("Venom")) {
			SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][3]);
			ElementalText[4]->SetText(FText::FromString(TEXT("Enhanced Stack & Dot & Nuke")));
			ElementalText[5]->SetText(FText::FromString(TEXT("Ability : Envenoming")));
		}
		else if (RogueEquipmentString[2] == TEXT("Electric") ||
			RogueEquipmentString[2] == TEXT("Lightning") ||
			RogueEquipmentString[2] == TEXT("Thunderbolt")) {
			SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][4]);
			ElementalText[4]->SetText(FText::FromString(TEXT("HighDamage")));
			ElementalText[5]->SetText(FText::FromString(TEXT("Ability : Electric Shock")));
		}
		Call_HaveElementalList();
		
		
		
		//TorchElementalText[0]->SetText(FText::FromString(RogueEquipmentString[2]));

		// 1. 현재 장착되어 있는 속성 가져와서 붙이기 - 클리어
		// 2. 가지고 있는 속성 가져오기, 엘리멘탈레벨*웨펀, 토치 레벨로 3단계 나눔
		// 2-1. 먼저 AddAbility에 속성들 집어 넣어야 함 - Clear
		// 3. 아이콘 역시 웨펀엘리멘탈, 토치 엘레멘탈의 평균단계에 맞춰 아이콘 변경 (같은 속성끼리)
		// 4. 해당 버튼 누르면 우측에 나타나고 셀렉을 눌러야 장착 완료.
		// 5. 백을 누르면 뒤로, 설정 저장 안됌.
	}
}

void UMyRogueWidget::AddAbilityMenuInit() {
	
	SelectAbilityName1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("SelectAbility1")));
	SelectAbilityName2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("SelectAbility2")));
	SelectAbilityName3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("SelectAbility3")));
	SelectAbilityName4 = Cast<UTextBlock>(GetWidgetFromName(TEXT("SelectAbility4")));
	SelectAbilityButton1 = Cast<UButton>(GetWidgetFromName(TEXT("SelectAbilityButtons1")));
	SelectAbilityButton2 = Cast<UButton>(GetWidgetFromName(TEXT("SelectAbilityButtons2")));
	SelectAbilityButton3 = Cast<UButton>(GetWidgetFromName(TEXT("SelectAbilityButtons3")));
	SelectAbilityButton4 = Cast<UButton>(GetWidgetFromName(TEXT("SelectAbilityButtons4")));
	AddAbilityBackButton = Cast<UButton>(GetWidgetFromName(TEXT("AddAbilityBackButtons")));
	SelectClasses1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("SelectedClass1")));
	SelectClasses2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("SelectedClass2")));
	SelectClasses3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("SelectedClass3")));
	SelectClasses4 = Cast<UTextBlock>(GetWidgetFromName(TEXT("SelectedClass4")));
	AbilityIcon1 = Cast<UImage>(GetWidgetFromName(TEXT("ClassIcon1")));
	AbilityIcon2 = Cast<UImage>(GetWidgetFromName(TEXT("ClassIcon2")));
	AbilityIcon3 = Cast<UImage>(GetWidgetFromName(TEXT("ClassIcon3")));
	AbilityIcon4 = Cast<UImage>(GetWidgetFromName(TEXT("ClassIcon4")));
	NowDatas = Cast<UTextBlock>(GetWidgetFromName(TEXT("NowData")));

	if (AddAbilityBackButton != nullptr) {
		MyGameMode->Widget_RogueUIValueInitDelegate.ExecuteIfBound();
		MyGameMode->Widget_CallStatWidgetDelegate.ExecuteIfBound();
		for (int i = 0; i < 4; i++) {
			int32 RandAbilityIndex = FMath::FRandRange(0, 32);
			if (RandAbilityIndex <= 23) {
				RogueSelectAbilityString[i] = RogueAbilityListString[RandAbilityIndex];
				RogueSelectClassesString[i] = TEXT("Add Ability");
				AbilityClassIcon[i] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
						TEXT("Texture2D'/Game/FlatSkillsIcons100/89.89'")));
			}
			else if (RandAbilityIndex == 24) {
				AbilityRandIndex[i] = FMath::RandRange(0, 9);
				RogueSelectAbilityString[i] = RogueHaveWeaponListString[AbilityRandIndex[i]];
				if(AbilityRandIndex[i] == 2 || AbilityRandIndex[i] == 4 || AbilityRandIndex[i] == 6 || AbilityRandIndex[i] == 7 || AbilityRandIndex[i] == 8)
					RogueSelectClassesString[i] = TEXT("Slash Weapons");
				else if(AbilityRandIndex[i] == 1 || AbilityRandIndex[i] == 3)
					RogueSelectClassesString[i] = TEXT("Smash Weapons");
				else if(AbilityRandIndex[i] == 0 || AbilityRandIndex[i] == 5 || AbilityRandIndex[i] == 9)
					RogueSelectClassesString[i] = TEXT("Stab Weapons");
				AbilityClassIcon[i] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
					TEXT("Texture2D'/Game/FlatSkillsIcons100/46.46'")));
			}
			else if (RandAbilityIndex == 25) {
				AbilityRandIndex[i] = FMath::RandRange(0, 9);
				RogueSelectAbilityString[i] = RogueHaveWeaponListString[AbilityRandIndex[i]];
				if (AbilityRandIndex[i] == 2 || AbilityRandIndex[i] == 4 || AbilityRandIndex[i] == 6 || AbilityRandIndex[i] == 7 || AbilityRandIndex[i] == 8)
					RogueSelectClassesString[i] = TEXT("Slash Weapons");
				else if (AbilityRandIndex[i] == 1 || AbilityRandIndex[i] == 3)
					RogueSelectClassesString[i] = TEXT("Smash Weapons");
				else if (AbilityRandIndex[i] == 0 || AbilityRandIndex[i] == 5 || AbilityRandIndex[i] == 9)
					RogueSelectClassesString[i] = TEXT("Stab Weapons");
				AbilityClassIcon[i] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
					TEXT("Texture2D'/Game/FlatSkillsIcons100/46.46'")));
			}
			else if (RandAbilityIndex == 26) {
				AbilityRandIndex[i] = FMath::RandRange(0, 6);
				RogueSelectAbilityString[i] = RogueAttackFormListString[0][AbilityRandIndex[i]];
				RogueSelectClassesString[i] = TEXT("Slash AttackForm");
				AbilityClassIcon[i] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
					TEXT("Texture2D'/Game/FlatSkillsIcons100/94.94'")));
			}
			else if (RandAbilityIndex == 27) {
				AbilityRandIndex[i] = FMath::RandRange(0, 7);
				RogueSelectAbilityString[i] = RogueAttackFormListString[1][AbilityRandIndex[i]];
				RogueSelectClassesString[i] = TEXT("Smash AttackForm");
				AbilityClassIcon[i] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
					TEXT("Texture2D'/Game/FlatSkillsIcons100/94.94'")));
			}
			else if (RandAbilityIndex == 28) {
				AbilityRandIndex[i] = FMath::RandRange(0, 9);
				RogueSelectAbilityString[i] = RogueAttackFormListString[2][AbilityRandIndex[i]];
				RogueSelectClassesString[i] = TEXT("Stab AttackForm");
				AbilityClassIcon[i] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
					TEXT("Texture2D'/Game/FlatSkillsIcons100/94.94'")));
			}
			else if (RandAbilityIndex == 29) {
				AbilityRandIndex[i] = FMath::RandRange(0, 2);
				RogueSelectAbilityString[i] = RogueAttackFormListString[3][AbilityRandIndex[i]];
				RogueSelectClassesString[i] = TEXT("SpecialArts");
				AbilityClassIcon[i] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
					TEXT("Texture2D'/Game/FlatSkillsIcons100/94.94'")));
			}
			else if (RandAbilityIndex == 30 || RandAbilityIndex == 31 || RandAbilityIndex == 32) {
				ElementalPhaseCheck();
				AbilityRandIndex[i] = FMath::RandRange(0, 9);
				if (AbilityRandIndex[i] <= 4) {
					RogueSelectAbilityString[i] = SelectElementString[0][AbilityRandIndex[i]];
					RogueSelectClassesString[i] = TEXT("Weapon Elemental");
					AbilityClassIcon[i] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
						TEXT("Texture2D'/Game/FlatSkillsIcons100/1.1'")));
				}
				else {
					/*if (TorchElementalPhase == 0)
						RogueSelectAbilityString[i] = RogueElementString[AbilityRandIndex[i]];
					else if (TorchElementalPhase == 1)
						RogueSelectAbilityString[i] = RogueElementString[AbilityRandIndex[i] + 10];
					else if (TorchElementalPhase == 2)
						RogueSelectAbilityString[i] = RogueElementString[AbilityRandIndex[i] + 20];*/
					RogueSelectAbilityString[i] = SelectElementString[1][AbilityRandIndex[i]-5];
					RogueSelectClassesString[i] = TEXT("Torch Elemental");
					AbilityClassIcon[i] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
						TEXT("Texture2D'/Game/FlatSkillsIcons100/10.10'")));
				}
			}
			SelectAbilityIndex[i] = RandAbilityIndex;
		}
		RogueDataString = FString::Printf(TEXT("%d"), RogueData);
		NowDatas->SetText(FText::FromString(RogueDataString));
		SelectAbilityName1->SetText(FText::FromString(RogueSelectAbilityString[0]));
		SelectAbilityName2->SetText(FText::FromString(RogueSelectAbilityString[1]));
		SelectAbilityName3->SetText(FText::FromString(RogueSelectAbilityString[2]));
		SelectAbilityName4->SetText(FText::FromString(RogueSelectAbilityString[3]));
		SelectClasses1->SetText(FText::FromString(RogueSelectClassesString[0]));
		SelectClasses2->SetText(FText::FromString(RogueSelectClassesString[1]));
		SelectClasses3->SetText(FText::FromString(RogueSelectClassesString[2]));
		SelectClasses4->SetText(FText::FromString(RogueSelectClassesString[3]));
		AbilityIcon1->SetBrushFromTexture(AbilityClassIcon[0]);
		AbilityIcon2->SetBrushFromTexture(AbilityClassIcon[1]);
		AbilityIcon3->SetBrushFromTexture(AbilityClassIcon[2]);
		AbilityIcon4->SetBrushFromTexture(AbilityClassIcon[3]);
		AddAbilityBackButton->OnClicked.AddDynamic(this, &UMyRogueWidget::GetBackButton);
		SelectAbilityButton1->OnClicked.AddDynamic(this, &UMyRogueWidget::GetSelectRogueAbilityOne);
		SelectAbilityButton2->OnClicked.AddDynamic(this, &UMyRogueWidget::GetSelectRogueAbilityTwo);
		SelectAbilityButton3->OnClicked.AddDynamic(this, &UMyRogueWidget::GetSelectRogueAbilityThree);
		SelectAbilityButton4->OnClicked.AddDynamic(this, &UMyRogueWidget::GetSelectRogueAbilityFour);
		RogueAbilityList->ClearChildren();
		MyGameMode->Widget_CallAbilityListDelegate.ExecuteIfBound();
		for (int i = 0; i <= AbilityLastIndex; i++) {
			GetRogueAbilityList(i, AbilityNames[i]);
			AbilityCost *= 1.1;
		}
		PageMain = false;
	}
}

void UMyRogueWidget::RevivalMenuInit() {
	Revival = Cast<UTextBlock>(GetWidgetFromName(TEXT("RevivalText")));
	RevivalOutLine = Cast<UBorder>(GetWidgetFromName(TEXT("Outline")));
	if (Revival != nullptr) {
		MyGameMode->Widget_MouseCursorChangedDelegate.ExecuteIfBound(2);
		if(MyGameMode->StageIndex == 0)
			Revival->SetText(FText::FromString(TEXT("Castle")));
		else if (MyGameMode->StageIndex == 1)
			Revival->SetText(FText::FromString(TEXT("Maze")));
		else if (MyGameMode->StageIndex == 2)
			Revival->SetText(FText::FromString(TEXT("Hall")));
		else if (MyGameMode->StageIndex == 3)
			Revival->SetText(FText::FromString(TEXT("Underpass")));
		Revival->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, MyGameMode->RevivalTextAlphaValue)));
		if (MyGameMode->RevivalTextAlphaMax == true)
			RevivalOutLine->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, MyGameMode->RevivalTextAlphaValue));
		
		if (MyGameMode->RevivalTextAlphaMax == false && MyGameMode->RevivalTextAlphaValue == 0.00f) {
			MyGameMode->RevivalUIUpdate();
		}
	}
}

void UMyRogueWidget::DialogueMenuInit() {
	Dialogue = Cast<UTextBlock>(GetWidgetFromName(TEXT("NPC_Dialogue")));
}

void UMyRogueWidget::ChangeHeadShake(bool Check) {
	if(Check == true)
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("HeadTrue")));
	else
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("HeadFalse")));
	MyGameMode->Call_HeadShakeDelegate.ExecuteIfBound(Check);
	//MyRogue->ViewArm->bUsePawnControlRotation = Check;
	MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
}

void UMyRogueWidget::ChangeLanguageEng(bool Check) {
	KorCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	MyGameMode->LanguageType = 0;
}

void UMyRogueWidget::ChangeLanguageKor(bool Check) {
	EngCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	MyGameMode->LanguageType = 1;
}

void UMyRogueWidget::ChangeTrdCamera(bool Check) {
	MyGameMode->Call_RollingTrdCameraDelegate.ExecuteIfBound(Check);
	MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
}

void UMyRogueWidget::SetSoundVolume(float Value) {
	MyGameMode->FXSoundClass->Properties.Volume = Value;
	FText ValueText = FText::FromString(FString::Printf(TEXT("%.0f"), SoundSlider->GetValue() * 100.f / 3.f));
	SoundVolumeValues->SetText(ValueText);
	MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
}

void UMyRogueWidget::SetFOVVolume(float Value) {
	MyGameMode->FOVValue = 100 * Value;
	MyGameMode->Call_RogueFOVDelegate.ExecuteIfBound(MyGameMode->FOVValue);
	FText ValueText = FText::FromString(FString::Printf(TEXT("%.0f"), FOVSlider->GetValue() * 100.f));
	FOVValues->SetText(ValueText);
	MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
}

void UMyRogueWidget::GetExitGame() {
	MyGameMode->StageIndex = 0;
	MyGameMode->StageSubIndex = 0;
	//MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UMyRogueWidget::GetBackButton() {
	if (BonFireMenuIn == true) {
		BonFireMenuIn = false;
		MyRogue->MyRogueState->TotalEquipCount++;
	}
	MyGameMode->WidgetPop();
}

void UMyRogueWidget::GetTitleMenu() {
	UGameplayStatics::OpenLevel(this, FName(TEXT("StartMap")), false);
	
}

void UMyRogueWidget::GetNewGame() {
	MyGameMode->StageIndex = 0;
	MyGameMode->StageSubIndex = 0;
	MyGameMode->WidgetCount = 0;
	//MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
	MyGameMode->GetWidgetNumber(-2);
	//이거 나중에 초기값스타트 정보 들어가야함
	//MyGameMode->GetWidgetNumber(1);
	//MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(1);
	//UGameplayStatics::OpenLevel(this, FName(TEXT("Stage1+Game")), false);
}

void UMyRogueWidget::GetKeyMenu() {
	MyGameMode->GetWidgetNumber(-3);
}

void UMyRogueWidget::GetRogueMain() {
	MyGameMode->StageIndex = 0;
	MyGameMode->StageSubIndex = 0;
	MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
	MyGameMode->GetWidgetNumber(-2);
	//MyGameMode->GetWidgetNumber(1);
	//MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(1);
}

void UMyRogueWidget::GetControllOptionMenu() {
	MyGameMode->GetWidgetNumber(-3);
}

void UMyRogueWidget::GetTabMenu() {
	MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(3);
}

void UMyRogueWidget::GetRogueStat() {
	MyGameMode->GetWidgetNumber(4);
}

void UMyRogueWidget::GetRogueEquip() {
	MyGameMode->GetWidgetNumber(5);
	
}

void UMyRogueWidget::GetGameState() {
	MyGameMode->GetWidgetNumber(6);
}

void UMyRogueWidget::GetBurningTotemMenu() {
	MyGameMode->GetWidgetNumber(7);
	
}

void UMyRogueWidget::GetChangedWeaponMenu() {
	MyGameMode->GetWidgetNumber(8);
	
}
void UMyRogueWidget::GetChangedAttackFormMenu() {
	MyGameMode->GetWidgetNumber(9);
	
}
void UMyRogueWidget::GetAddAbilityMenu() {
	MyGameMode->Widget_RogueUIValueInitDelegate.ExecuteIfBound();
	if (RogueData >= 100)
		MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(50.f);
	else if (RogueData < 100)
		MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(0);
	MyGameMode->GetWidgetNumber(10);
	
}

void UMyRogueWidget::GetChangedElementalMenu() {
	MyGameMode->GetWidgetNumber(11);
	
}

void UMyRogueWidget::GetDialogue() {
	MyGameMode->GetWidgetNumber(99);
	
}

void UMyRogueWidget::GetRevival() {
	MyGameMode->GetWidgetNumber(-1);
}

void UMyRogueWidget::SelectWeaponButtonFuntion() {
	MyGameMode->Call_WeaponChangeDelegate.ExecuteIfBound(WeaponNumberIndex);
	MyGameMode->WidgetPop();
	//적용 내용 입력.
	//GetBurningTotemMenu();
}

void UMyRogueWidget::SelectElementalButton() {
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(RogueWeaponElementalNumber, true);
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(RogueTorchElementalNumber, true);

	MyGameMode->WidgetPop();
}

void UMyRogueWidget::SelectAttackFormButtonFuntion() {
	MyGameMode->Call_TakeAttackFormDelegate.ExecuteIfBound(SelectedAttackFormNumber[0], 
		SelectedAttackFormIndex[0], 0);
	MyGameMode->Call_TakeAttackFormDelegate.ExecuteIfBound(SelectedAttackFormNumber[1], 
		SelectedAttackFormIndex[1], 1);
	MyGameMode->Call_TakeAttackFormDelegate.ExecuteIfBound(SelectedAttackFormNumber[2],
		SelectedAttackFormIndex[2], 2);
	//적용 내용 입력.
	MyGameMode->WidgetPop();
}

void UMyRogueWidget::GetRogueHpValue(int32 SetHp) {
	RogueHp = SetHp;
	RogueHpString = FString::Printf(TEXT("%d"), RogueHp);
	if(PageMain == true)
		RogueHPValue->SetText(FText::FromString(RogueHpString));
}

void UMyRogueWidget::GetRogueDataValue(int32 SetData) {
	RogueData = SetData;
	RogueDataString = FString::Printf(TEXT("%d"), RogueData);
	if (PageMain == true)
		RogueDataValue->SetText(FText::FromString(RogueDataString));
}

void UMyRogueWidget::GetRogueKarmaValue(int32 SetKarma) {
	RogueKarma = SetKarma;
	RogueKarmaString = FString::Printf(TEXT("%d"), RogueKarma);
	if (PageMain == true)
		RogueKarmaValue->SetText(FText::FromString(RogueKarmaString));
}

void UMyRogueWidget::Return_GameStateData(float* SetData) {
	FString GameStateValueText[5];
	for (int i = 0; i < 5; i++) {
		GameStateValueText[i] = FString::Printf(TEXT("%.0f"), SetData[i]);
	}
	KillCountValue->SetText(FText::FromString(GameStateValueText[0]));
	DeathCountValue->SetText(FText::FromString(GameStateValueText[1]));
	TotalDataValue->SetText(FText::FromString(GameStateValueText[2]));
	UsedDataValue->SetText(FText::FromString(GameStateValueText[3]));
	DungeonClearValue->SetText(FText::FromString(GameStateValueText[4]));
}

void UMyRogueWidget::GetRogueStatValue(float* SetData) {

	for (int i = 0; i < 16; i++) {
		RogueStatData[i] = *SetData++;
		if (i == 3 || i == 5)
			RogueStatDataString[i] = FString::Printf(TEXT("%.0f"), RogueStatData[i] * 100);
		else
			RogueStatDataString[i] = FString::Printf(TEXT("%d"), (int32)RogueStatData[i]);
	}
	if (PageStat == true) {
		RogueStatMaxHPValue->SetText(FText::FromString(RogueStatDataString[0]));
		RogueStatTotalDataValue->SetText(FText::FromString(RogueStatDataString[1]));
		RogueStatTotalKillValue->SetText(FText::FromString(RogueStatDataString[2]));
		RogueStatMoveSpeedValue->SetText(FText::FromString(RogueStatDataString[3] + TEXT("%")));
		RogueStatSuperArmorValue->SetText(FText::FromString(RogueStatDataString[4] + TEXT("%")));
		RogueStatWeaponSpeedValue->SetText(FText::FromString(RogueStatDataString[5] + TEXT("%")));
		RogueStatWeaponLevelValue->SetText(FText::FromString(RogueStatDataString[6]));
		RogueStatTorchLevelValue->SetText(FText::FromString(RogueStatDataString[7]));
		RogueStatElementLevelValue->SetText(FText::FromString(RogueStatDataString[8]));
		RogueStatWeaponPhysicsDamegeValue->SetText(FText::FromString(RogueStatDataString[9]));
		RogueStatWeaponElementDamegeValue->SetText(FText::FromString(RogueStatDataString[10]));
		RogueStatWeaponEffectPercentageValue->SetText(FText::FromString(RogueStatDataString[11] + TEXT("%")));
		RogueStatTorchStabDamegeValue->SetText(FText::FromString(RogueStatDataString[12]));
		RogueStatTorchElementDamegeValue->SetText(FText::FromString(RogueStatDataString[13]));
		RogueStatTorchEffectDamegeValue->SetText(FText::FromString(RogueStatDataString[14]));
		RogueStatTorchEffectPercentageValue->SetText(FText::FromString(RogueStatDataString[15] + TEXT("%")));
		
	}
}

void UMyRogueWidget::GetRogueEquipmentValue(FString* EquipmentValues, TCHAR** EquipmentAttackFormString, 
	TCHAR** EquipmentAttackFormRef, int32* EquipmentAttackForm, int32* EquipmentAttackFormIndex,
	int32* EquipNumberData, float*OverlapData, float** TotalOverlapData) {
	for (int i = 0; i < 6; i++) {
		RogueEquipmentString[i] = *EquipmentValues++;
		RogueOverlapData[i] = OverlapData[i];
		TotalRogueOverlapData[i] = TotalOverlapData[i];
		if (i < 3) {
			RogueEquipmentAttackFormString[i] = *EquipmentAttackFormString++;
			RogueEquipmentAttackFormRef[i] = *EquipmentAttackFormRef++;
			RogueEquipmentAttackForm[i] = EquipmentAttackForm[i];
			RogueEquipmentAttackFormIndex[i] = EquipmentAttackFormIndex[i];
			RogueEquipNumberData[i] = EquipNumberData[i];
		}
	}
	if (PageEquip == true) {
		EquipWeaponValue->SetText(FText::FromString(RogueEquipmentString[0]));
		WeaponElementValue->SetText(FText::FromString(RogueEquipmentString[1]));
		TorchElementValue->SetText(FText::FromString(RogueEquipmentString[2]));
		AttackFormIValue->SetText(FText::FromString(RogueEquipmentString[3]));
		AttackFormIIValue->SetText(FText::FromString(RogueEquipmentString[4]));
		AttackFormIIIValue->SetText(FText::FromString(RogueEquipmentString[5]));
		
		for (int i = 0; i < 6; i++) {
			if (OverlapData[i] <= 5) {
				EquipWeaponValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f - (OverlapData[0] / 5), 1.f)));
				WeaponElementValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f - (OverlapData[1] / 5), 1.f)));
				TorchElementValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f - (OverlapData[2] / 5), 1.f)));
				AttackFormIValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f - (OverlapData[3] / 5), 1.f)));
				AttackFormIIValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f - (OverlapData[4] / 5), 1.f)));
				AttackFormIIIValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f - (OverlapData[5] / 5), 1.f)));
			}
			else if(OverlapData[i] <= 20){
				EquipWeaponValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f - ((OverlapData[0]-5) / 10), 0, 1.f)));
				WeaponElementValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f - ((OverlapData[1]-5) / 10), 0, 1.f)));
				TorchElementValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f - ((OverlapData[2]-5) / 10), 0, 1.f)));
				AttackFormIValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f - ((OverlapData[3]-5) / 10), 0, 1.f)));
				AttackFormIIValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f - ((OverlapData[4]-5) / 10), 0, 1.f)));
				AttackFormIIIValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f - ((OverlapData[5]-5) / 10), 0, 1.f)));
			}
			else {
				EquipWeaponValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0, 0, 1.f)));
				WeaponElementValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0, 0, 1.f)));
				TorchElementValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0, 0, 1.f)));
				AttackFormIValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0, 0, 1.f)));
				AttackFormIIValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0, 0, 1.f)));
				AttackFormIIIValue->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0, 0, 1.f)));
			}
		}
	}
	
}

void UMyRogueWidget::Call_HaveWeaponList() {
	MyGameMode->Call_RogueTakeHaveWeaponDelegate.ExecuteIfBound();
}

void UMyRogueWidget::Call_HaveAttackFormList() {
	MyGameMode->Call_RogueTakeHaveAttackFormDelegate.ExecuteIfBound();
}

void  UMyRogueWidget::Call_HaveAbilityList() {
	MyGameMode->Call_RogueTakeHaveAbilityDelegate.ExecuteIfBound();
}

void UMyRogueWidget::Call_HaveElementalList() {
	MyGameMode->Call_RogueTakeHaveElementalDelegate.ExecuteIfBound();
}

void UMyRogueWidget::Return_HaveAbilityList(bool *RogueAbilityLists, float* RogueAbilityOverlapCheck){
	for (int i = 0; i < 24; i++) {
		if (HaveAbilityList[i] == true)
			HaveAbilityOverlap[i] = RogueAbilityOverlapCheck[i];
		else
			HaveAbilityList[i] = RogueAbilityLists[i];
	}
}

void UMyRogueWidget::Return_HaveAttackFormList(bool ReturnAttackFormList[4][10], float AttackFormOverlap[4][10]) {
	ChangedAttackFromList->ClearChildren();
	ButtonStyleInit();
	UseNanumMyeonjo = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), NULL,
		TEXT("Font'/Game/Fonts/NanumMyeongjo-Regular_Font.NanumMyeongjo-Regular_Font'")));
	for (int j = 0; j <= AttackFormMaxIndex; j++) {
		HaveAttackFormList[AttackForm][j] = ReturnAttackFormList[AttackForm][j];
		HaveAttackFormOverlap[AttackForm][j] = AttackFormOverlap[AttackForm][j];
		if (HaveAttackFormList[AttackForm][j] == true) {
			AttackFormIndex = AttackForm * 10 + j;
			ViewAttackFormListText[AttackFormIndex] = NewObject<UTextBlock>();
			ViewAttackFormListText[AttackFormIndex]->SetText(FText::FromString(RogueAttackFormListString[AttackForm][j]));
			ViewAttackFormListText[AttackFormIndex]->SetFont(FSlateFontInfo(UseNanumMyeonjo, 30));

			if (HaveAttackFormOverlap[AttackForm][j] <= 5)
				ViewAttackFormListText[AttackFormIndex]->SetColorAndOpacity(FSlateColor(
					FLinearColor(1.f, 1.f, 1.f - (HaveAttackFormOverlap[AttackForm][j] / 5), 1.f)));

			else if (AttackFormOverlap[AttackForm][j] <= 20.f)
				ViewAttackFormListText[AttackFormIndex]->SetColorAndOpacity(FSlateColor(
					FLinearColor(1.f, 1.f - ((AttackFormOverlap[AttackForm][j]-5) / 10), 0, 1.f)));
			else
				ViewAttackFormListText[AttackFormIndex]->SetColorAndOpacity(FSlateColor(
					FLinearColor(1.f, 0, 0, 1.f)));

			ViewAttackFormListButton[AttackFormIndex] = NewObject<UButton>();
			ViewAttackFormListButton[AttackFormIndex]->SetStyle(NewWeaponAndSkillButton);
			ViewAttackFormListButton[AttackFormIndex]->AddChild(ViewAttackFormListText[AttackForm * 10 + j]);

			ChangedAttackFromList->AddChild(ViewAttackFormListButton[AttackFormIndex]);
			switch (AttackFormIndex){
			case 0:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInSlash);
				break;
			case 1:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInReverseSlash);
				break;
			case 2:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInBashSlash);
				break;
			case 3:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInUpperSlash);
				break;
			case 4:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInXSlash);
				break;
			case 5:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInDownUpper);
				break;
			case 6:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInWhiteFang);
				break;
			case 10:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInSmash);
				break;
			case 11:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInBreaker);
				break;
			case 12:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInSideSmash);
				break;
			case 13:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInSideBreaker);
				break;
			case 14:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInGroundBreaker);
				break;
			case 15:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInReverseSideSmash);
				break;
			case 16:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInHeadDancer);
				break;
			case 17:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInCranker);
				break;
			case 20:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInStab);
				break;
			case 21:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInQuickStab);
				break;
			case 22:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInDeepStab);
				break;
			case 23:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInHooks);
				break;
			case 24:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInUpperStab);
				break;
			case 25:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInOneInchStab);
				break;
			case 26:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInDoubleStab);
				break;
			case 27:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInTwoFace);
				break;
			case 28:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInPitFinish);
				break;
			case 29:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInWindHole);
				break;
			case 30:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInAirTrack);
				break;
			case 31:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInDeleteRow);
				break;
			case 32:
				ViewAttackFormListButton[AttackFormIndex]->OnClicked.AddDynamic(this, &UMyRogueWidget::AttackSlotInTurnEnd);
				break;
			}
		}
	}
}

void UMyRogueWidget::Return_HaveElementalList(bool ElementalCheck[10], float ElementalOverlap[10]) {
	for (int i = 0; i < 10; i++) {
		if (ElementalCheck[i] == true){
			if (i <= 4 ) {
				WeaponElementalButton[i]->SetIsEnabled(true);
				if(ElementalOverlap[i] <= 5)
					WeaponElementalText[i]->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f-(ElementalOverlap[i]/5), 1.f)));
				else if(ElementalOverlap[i] <= 20)
					WeaponElementalText[i]->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f - ((ElementalOverlap[i]-5) / 20), 0.f, 1.f)));
				else
					WeaponElementalText[i]->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0.f, 0.f, 1.f)));
				
			}
			else {
				TorchElementalButton[i-5]->SetIsEnabled(true);
				
				if (ElementalOverlap[i] <= 5)
					TorchElementalText[i-5]->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f - (ElementalOverlap[i] / 5), 1.f)));
				else if (ElementalOverlap[i] <= 20)
					TorchElementalText[i-5]->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f - ((ElementalOverlap[i] - 5) / 20), 0.f, 1.f)));
				else
					TorchElementalText[i-5]->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0.f, 0.f, 1.f)));
			}
		}
			
	}
	WeaponElementalButton[0]->OnClicked.AddDynamic(this, &UMyRogueWidget::WeaponElementStrenght);
	WeaponElementalButton[1]->OnClicked.AddDynamic(this, &UMyRogueWidget::WeaponElementHeat);
	WeaponElementalButton[2]->OnClicked.AddDynamic(this, &UMyRogueWidget::WeaponElementCold);
	WeaponElementalButton[3]->OnClicked.AddDynamic(this, &UMyRogueWidget::WeaponElementPoison);
	WeaponElementalButton[4]->OnClicked.AddDynamic(this, &UMyRogueWidget::WeaponElementElectric);

	TorchElementalButton[0]->OnClicked.AddDynamic(this, &UMyRogueWidget::TorchElementStrenght);
	TorchElementalButton[1]->OnClicked.AddDynamic(this, &UMyRogueWidget::TorchElementHeat);
	TorchElementalButton[2]->OnClicked.AddDynamic(this, &UMyRogueWidget::TorchElementCold);
	TorchElementalButton[3]->OnClicked.AddDynamic(this, &UMyRogueWidget::TorchElementPoison);
	TorchElementalButton[4]->OnClicked.AddDynamic(this, &UMyRogueWidget::TorchElementElectric);
}

void UMyRogueWidget::AttackSlotInSlash() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 0;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 0;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInReverseSlash() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 0;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 1;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInBashSlash() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 0;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 2;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInUpperSlash() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 0;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 3;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInXSlash() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 0;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 4;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInDownUpper() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 0;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 5;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInWhiteFang() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 0;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 6;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInSmash() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 1;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 0;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInBreaker() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 1;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 1;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInSideSmash() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 1;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 2;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInSideBreaker() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 1;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 3;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInShortPick() {
	/*PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 1;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 4;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);*/
}
void UMyRogueWidget::AttackSlotInGroundBreaker() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 1;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 4;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInReverseSideSmash() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 1;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 5;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInHeadDancer() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 1;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 6;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInCranker() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 1;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 7;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}


void UMyRogueWidget::AttackSlotInStab() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 0;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInQuickStab() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 1;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInDeepStab() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 2;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInHooks() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 3;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInUpperStab() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 4;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInOneInchStab() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 5;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInDoubleStab() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 6;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInTwoFace() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 7;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInPitFinish() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 8;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInWindHole() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 2;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 9;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInAirTrack() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 3;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 0;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInDeleteRow() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 3;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 1;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}
void UMyRogueWidget::AttackSlotInTurnEnd() {
	PlaySound(SelectSound);
	SelectedAttackFormNumber[SelectedAttackFormSlotNumber] = 3;
	SelectedAttackFormIndex[SelectedAttackFormSlotNumber] = 2;
	SetAttackForm(SelectedAttackFormNumber[SelectedAttackFormSlotNumber], SelectedAttackFormIndex[SelectedAttackFormSlotNumber]);
}

void UMyRogueWidget::WeaponElementStrenght() {
	RogueWeaponElementalNumber = 0;
	SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][0]);
	ElementalText[0]->SetText(FText::FromString(SelectElementString[0][0]));
	ElementalText[1]->SetText(FText::FromString(TEXT("High Damage")));
	ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Stun")));
}

void UMyRogueWidget::WeaponElementHeat() {
	RogueWeaponElementalNumber = 1;
	SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][1]);
	ElementalText[0]->SetText(FText::FromString(SelectElementString[0][1]));
	ElementalText[1]->SetText(FText::FromString(TEXT("Dot & Nuke")));
	ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Burn")));
}

void UMyRogueWidget::WeaponElementCold() {
	RogueWeaponElementalNumber = 2;
	SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][2]);
	ElementalText[0]->SetText(FText::FromString(SelectElementString[0][2]));
	ElementalText[1]->SetText(FText::FromString(TEXT("Stack & Slow")));
	ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Chilling")));
}

void UMyRogueWidget::WeaponElementPoison() {
	RogueWeaponElementalNumber = 3;
	SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][3]);
	ElementalText[0]->SetText(FText::FromString(SelectElementString[0][3]));
	ElementalText[1]->SetText(FText::FromString(TEXT("Stack & Dot")));
	ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Toxicosis")));
}

void UMyRogueWidget::WeaponElementElectric() {
	RogueWeaponElementalNumber = 4;
	SelectWeaponElementalIcons->SetBrushFromTexture(SelectElementIcon[0][4]);
	ElementalText[0]->SetText(FText::FromString(SelectElementString[0][4]));
	ElementalText[1]->SetText(FText::FromString(TEXT("Stack & HighDamege")));
	ElementalText[2]->SetText(FText::FromString(TEXT("Ability : Charging")));
}


void UMyRogueWidget::TorchElementStrenght() {
	RogueTorchElementalNumber = 0;
	SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][0]);
	ElementalText[3]->SetText(FText::FromString(SelectElementString[1][0]));
	ElementalText[4]->SetText(FText::FromString(TEXT("Easy Conditions")));
	ElementalText[5]->SetText(FText::FromString(TEXT("Ability : LevelDamege")));
}

void UMyRogueWidget::TorchElementHeat() {
	RogueTorchElementalNumber = 1;
	SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][1]);
	ElementalText[3]->SetText(FText::FromString(SelectElementString[1][1]));
	ElementalText[4]->SetText(FText::FromString(TEXT("HighRange & Nuke")));
	ElementalText[5]->SetText(FText::FromString(TEXT("Ability : BurnExplosion")));
}

void UMyRogueWidget::TorchElementCold() {
	RogueTorchElementalNumber = 2;
	SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][2]);
	ElementalText[3]->SetText(FText::FromString(SelectElementString[1][2]));
	ElementalText[4]->SetText(FText::FromString(TEXT("Enhanced Stack & Nuke")));
	ElementalText[5]->SetText(FText::FromString(TEXT("Ability : Freez & Iceberg")));
}

void UMyRogueWidget::TorchElementPoison() {
	RogueTorchElementalNumber = 3;
	SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][3]);
	ElementalText[3]->SetText(FText::FromString(SelectElementString[1][3]));
	ElementalText[4]->SetText(FText::FromString(TEXT("Enhanced Stack & Dot & Nuke")));
	ElementalText[5]->SetText(FText::FromString(TEXT("Ability : Venom")));
}

void UMyRogueWidget::TorchElementElectric() {
	RogueTorchElementalNumber = 4;
	SelectTorchElementalIcons->SetBrushFromTexture(SelectElementIcon[1][4]);
	ElementalText[3]->SetText(FText::FromString(SelectElementString[1][4]));
	ElementalText[4]->SetText(FText::FromString(TEXT("HighDamage")));
	ElementalText[5]->SetText(FText::FromString(TEXT("Ability : Electric Shock")));
}

void UMyRogueWidget::SetAttackForm(int32 Form, int32 FormIndex) {
	if (SelectedAttackFormSlotNumber == 0) {
		SelectedAttackForm1s->SetText(FText::FromString(RogueAttackFormListString[Form][FormIndex]));
		RogueEquipmentAttackFormString[0] = RogueAttackFormVideoString[Form][FormIndex];
	}
	else if (SelectedAttackFormSlotNumber == 1) {
		SelectedAttackForm2s->SetText(FText::FromString(RogueAttackFormListString[Form][FormIndex]));
		RogueEquipmentAttackFormString[1] = RogueAttackFormVideoString[Form][FormIndex];
	}
	else if (SelectedAttackFormSlotNumber == 2) {
		SelectedAttackForm3s->SetText(FText::FromString(RogueAttackFormListString[Form][FormIndex]));
		RogueEquipmentAttackFormString[2] = RogueAttackFormVideoString[Form][FormIndex];
	}
	for (int i = 0; i < 3; i++) {
		AttackSource[i] = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
			RogueEquipmentAttackFormString[i]));
		//AttackFormTexture[i]->SetMediaPlayer(AttackFormPlayer[i]);
		//AttackFormPlayer[i]->OpenSource(AttackSource[i]);
		//AttackFormPlayer[i]->Play();

	}
}


void UMyRogueWidget::SelectedAttackFormSlotOne() {
	SelectedAttackFormSlotNumber = 0;
	if (SelectedAttackFormSlotOverlay2->HasChild(SelectedSlotState) == true)
		SelectedAttackFormSlotOverlay2->RemoveChild(SelectedSlotState);
	if (SelectedAttackFormSlotOverlay3->HasChild(SelectedSlotState) == true)
		SelectedAttackFormSlotOverlay3->RemoveChild(SelectedSlotState);
	if (SelectedSlotState != nullptr)
		SelectedSlotState->RemoveFromParent();
	SelectedSlotState = NewObject<UCircularThrobber>();
	SelectedSlotState->NumberOfPieces = 25;
	SelectedSlotState->Radius = 25;
	SelectedSlotState->Period = 0.5f;
	SelectedSlotState->Image.SetImageSize(FVector2D(10.f, 10.f));
	SelectedAttackFormSlotOverlay1->AddChild(SelectedSlotState);
	//SelectedAttackFormSlotOverlay1->GetChildAt(SelectedAttackFormSlotOverlay1->GetChildIndex(SelectedSlotState)).Aliment
}

void UMyRogueWidget::SelectedAttackFormSlotTwo() {
	SelectedAttackFormSlotNumber = 1;
	if (SelectedAttackFormSlotOverlay1->HasChild(SelectedSlotState) == true)
		SelectedAttackFormSlotOverlay1->RemoveChild(SelectedSlotState);
	if (SelectedAttackFormSlotOverlay3->HasChild(SelectedSlotState) == true)
		SelectedAttackFormSlotOverlay3->RemoveChild(SelectedSlotState);
	if (SelectedSlotState != nullptr)
		SelectedSlotState->RemoveFromParent();
	SelectedSlotState = NewObject<UCircularThrobber>();
	SelectedSlotState->NumberOfPieces = 25;
	SelectedSlotState->Radius = 25;
	SelectedSlotState->Period = 0.5f;
	SelectedSlotState->Image.SetImageSize(FVector2D(10.f, 10.f));
	SelectedAttackFormSlotOverlay2->AddChild(SelectedSlotState);
}

void UMyRogueWidget::SelectedAttackFormSlotThree() {
	SelectedAttackFormSlotNumber = 2;
	if (SelectedAttackFormSlotOverlay1->HasChild(SelectedSlotState) == true)
		SelectedAttackFormSlotOverlay1->RemoveChild(SelectedSlotState);
	if (SelectedAttackFormSlotOverlay2->HasChild(SelectedSlotState) == true)
		SelectedAttackFormSlotOverlay2->RemoveChild(SelectedSlotState);
	if (SelectedSlotState != nullptr)
		SelectedSlotState->RemoveFromParent();
	SelectedSlotState = NewObject<UCircularThrobber>();
	SelectedSlotState->NumberOfPieces = 25;
	SelectedSlotState->Radius = 25;
	SelectedSlotState->Period = 0.5f;
	SelectedSlotState->Image.SetImageSize(FVector2D(10.f, 10.f));
	SelectedAttackFormSlotOverlay3->AddChild(SelectedSlotState);
}

void UMyRogueWidget::Return_HaveWeaponList(bool* ReturnWeaponList, float* WeaponOverlap) {
	ButtonStyleInit();
	for (int i = 0; i <= 9; i++){
		HaveWeaponList[i] = *(ReturnWeaponList + i);
		if (HaveWeaponList[i] == true) {
			
			ViewWeaponListText[i] = NewObject<UTextBlock>();
			ViewWeaponListText[i]->SetText(FText::FromString(RogueHaveWeaponListString[i]));
			ViewWeaponListText[i]->SetFont(FSlateFontInfo(UseCinzelFont, 30));
			
			if (WeaponOverlap[i] <= 5.f)
				ViewWeaponListText[i]->SetColorAndOpacity(FSlateColor(
					FLinearColor(1.f, 1.f, 1.f - WeaponOverlap[i]/5, 1.f)));
			
			else if(WeaponOverlap[i] <= 15)
				ViewWeaponListText[i]->SetColorAndOpacity(FSlateColor(
					FLinearColor(1.f, 1.f - ((WeaponOverlap[i]-5) / 10), 0, 1.f)));
			else
				ViewWeaponListText[i]->SetColorAndOpacity(FSlateColor(
					FLinearColor(1.f, 0, 0, 1.f)));
			
			ViewWeaponListButton[i] = NewObject<UButton>();
			ViewWeaponListButton[i]->SetStyle(NewWeaponAndSkillButton);
			ViewWeaponListButton[i]->AddChild(ViewWeaponListText[i]);
		
			ChangedWeaponList->AddChild(ViewWeaponListButton[i]);
			switch (i){
			case 0:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetDaggerImage);
				break;
			case 1:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetMaceImage);
				break;
			case 2:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetGAxeImage);
				break;
			case 3:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetGHammerImage);
				break;
			case 4:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetGSwordImage);
				break;
			case 5:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetSSwordImage);
				break;
			case 6:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetAxeImage);
				break;
			case 7:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetSpearImage);
				break;
			case 8:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetScytheImage);
				break;
			case 9:
				ViewWeaponListButton[i]->OnClicked.AddDynamic(this, &UMyRogueWidget::GetKnifeImage);
				break;
			}
		}
	}
}

void UMyRogueWidget::GetDaggerImage(){
	WeaponNumberIndex = 0;
	UTexture2D* DaggerIcon1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL, 
			TEXT("Texture2D'/Game/FlatSkillsIcons100/6.6'")));
	UTexture2D* DaggerIcon2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(),NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/11.11'")));
	UTexture2D* DaggerImage = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/DaggerImage.DaggerImage'")));
	if (DaggerIcon1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(DaggerIcon1);
		WeaponIcons2->SetBrushFromTexture(DaggerIcon2);
		WeaponImages->SetBrushFromTexture(DaggerImage);
		WeaponIcons1->SetToolTipText(IconToolTip[2]);
		WeaponIcons2->SetToolTipText(IconToolTip[3]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("VeryFast Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Stab Specialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("Elemental Specialization")));
	}
}
void UMyRogueWidget::GetMaceImage() {
	WeaponNumberIndex = 1;
	UTexture2D* MaceIcon1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/69.69'")));
	UTexture2D* MaceIcon2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/11.11'")));
	UTexture2D* MaceImage = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/MaceImage.MaceImage'")));
	if (MaceIcon1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(MaceIcon1);
		WeaponIcons2->SetBrushFromTexture(MaceIcon2);
		WeaponImages->SetBrushFromTexture(MaceImage);
		WeaponIcons1->SetToolTipText(IconToolTip[1]);
		WeaponIcons2->SetToolTipText(IconToolTip[3]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("Fast Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Smash Specialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("Elemental Suitable")));
	}
}
void UMyRogueWidget::GetGAxeImage() {
	WeaponNumberIndex = 2;
	UTexture2D* GAxeIcon1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/45.45'")));
	UTexture2D* GAxeIcon2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/69.69'")));
	UTexture2D* GreatAxeImage = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/GreatAxe.GreatAxe'")));
	if (GAxeIcon1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(GAxeIcon1);
		WeaponIcons2->SetBrushFromTexture(GAxeIcon2);
		WeaponImages->SetBrushFromTexture(GreatAxeImage);
		WeaponIcons1->SetToolTipText(IconToolTip[0]);
		WeaponIcons2->SetToolTipText(IconToolTip[1]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("Slow Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Slash Specialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("Smash Suitable")));
	}
}
void UMyRogueWidget::GetGHammerImage() {
	WeaponNumberIndex = 3;
	UTexture2D* GHammer1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/69.69'")));
	UTexture2D* GHammer2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/11.11'")));
	UTexture2D* GreatHammer = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/GreatHammer.GreatHammer'")));
	if (GHammer1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(GHammer1);
		WeaponIcons2->SetBrushFromTexture(GHammer2);
		WeaponImages->SetBrushFromTexture(GreatHammer);
		WeaponIcons1->SetToolTipText(IconToolTip[1]);
		WeaponIcons2->SetToolTipText(IconToolTip[3]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("VerySlow Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Smash HighSpecialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("Elemental Suitable, High Damage")));
	}
}
void UMyRogueWidget::GetGSwordImage() {
	WeaponNumberIndex = 4;
	UTexture2D* GSwordIcon1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/45.45'")));
	UTexture2D* GSwordIncon2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/20.20'")));
	UTexture2D* GreatSword = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/GreatSword.GreatSword'")));
	if (GSwordIcon1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(GSwordIcon1);
		WeaponIcons2->SetBrushFromTexture(GSwordIncon2);
		WeaponImages->SetBrushFromTexture(GreatSword);
		WeaponIcons1->SetToolTipText(IconToolTip[0]);
		WeaponIcons2->SetToolTipText(IconToolTip[5]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("Normal Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Slash HighSpecialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("Great Balance")));
	}
}
void UMyRogueWidget::GetSSwordImage() {
	WeaponNumberIndex = 5;
	UTexture2D* SSwordIcon1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/6.6'")));
	UTexture2D* SSwordIcon2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/7.7'")));
	UTexture2D* SSwordImage = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/ShortSword.ShortSword'")));
	if (SSwordIcon1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(SSwordIcon1);
		WeaponIcons2->SetBrushFromTexture(SSwordIcon2);
		WeaponImages->SetBrushFromTexture(SSwordImage);
		WeaponIcons1->SetToolTipText(IconToolTip[2]);
		WeaponIcons2->SetToolTipText(IconToolTip[4]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("VeryFast Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Stab HighSpecialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("High DPS")));
	};
}
void UMyRogueWidget::GetAxeImage() {
	WeaponNumberIndex = 6;
	UTexture2D* AxeIcon1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/45.45'")));
	UTexture2D* AxeIcon2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/7.7'")));
	UTexture2D* AxeImage = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/HandAxe.HandAxe'")));
	if (AxeIcon1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(AxeIcon1);
		WeaponIcons2->SetBrushFromTexture(AxeIcon2);
		WeaponImages->SetBrushFromTexture(AxeImage);
		WeaponIcons1->SetToolTipText(IconToolTip[0]);
		WeaponIcons2->SetToolTipText(IconToolTip[4]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("VeryFast Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Slash Specialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("High DPS")));
	}
}
void UMyRogueWidget::GetSpearImage() {
	WeaponNumberIndex = 7;
	UTexture2D* SpearIcon1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/45.45'")));
	UTexture2D* SpearIcon2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/7.7'")));
	UTexture2D* SpearImage = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/Spear.Spear'")));
	if (SpearIcon1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(SpearIcon1);
		WeaponIcons2->SetBrushFromTexture(SpearIcon2);
		WeaponImages->SetBrushFromTexture(SpearImage);
		WeaponIcons1->SetToolTipText(IconToolTip[0]);
		WeaponIcons2->SetToolTipText(IconToolTip[4]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("VerySlow Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Slash HighSpecialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("High DPS")));
	}
}
void UMyRogueWidget::GetScytheImage() {
	WeaponNumberIndex = 8;
	UTexture2D* ScytheIcon1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/45.45'")));
	UTexture2D* ScytheIcon2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/11.11'")));
	UTexture2D* ScytheImage = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/Scythe.Scythe'")));
	if (ScytheIcon1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(ScytheIcon1);
		WeaponIcons2->SetBrushFromTexture(ScytheIcon2);
		WeaponImages->SetBrushFromTexture(ScytheImage);
		WeaponIcons1->SetToolTipText(IconToolTip[0]);
		WeaponIcons2->SetToolTipText(IconToolTip[3]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("VerySlow Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Slash Specialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("Elemental Suitable, High Damage")));
	}
}
void UMyRogueWidget::GetKnifeImage() {
	WeaponNumberIndex = 9;
	UTexture2D* KnifeIcon1 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/11.11'")));
	UTexture2D* KnifeIcon2 = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/FlatSkillsIcons100/6.6'")));
	UTexture2D* KnifeImage = Cast<UTexture2D>
		(StaticLoadObject(UTexture2D::StaticClass(), NULL,
			TEXT("Texture2D'/Game/WeaponFixImage/Knife.Knife'")));
	if (KnifeIcon1) {
		PlaySound(SelectSound);
		WeaponIcons1->SetBrushFromTexture(KnifeIcon1);
		WeaponIcons2->SetBrushFromTexture(KnifeIcon2);
		WeaponImages->SetBrushFromTexture(KnifeImage);
		WeaponIcons1->SetToolTipText(IconToolTip[3]);
		WeaponIcons2->SetToolTipText(IconToolTip[2]);
		WeaponAttributes1->SetText(FText::FromString(TEXT("VeryFast Rate")));
		WeaponAttributes2->SetText(FText::FromString(TEXT("Elemental HighSpecialization")));
		WeaponAttributes3->SetText(FText::FromString(TEXT("Stab Specialization")));
	}
}

void UMyRogueWidget::GetRogueAbilityList(int32 AbilityListIndex, FString AbilityName) {
	Call_HaveAbilityList();
	AbilityListValue[AbilityListIndex] = NewObject<UTextBlock>();
	AbilityListValue[AbilityListIndex]->AddToRoot();
	AbilityListValue[AbilityListIndex]->SetText(FText::FromString(AbilityName));
	AbilityListValue[AbilityListIndex]->SetFont(FSlateFontInfo(UseCardo, 20));
	RogueAbilityList->AddChild(AbilityListValue[AbilityListIndex]);
}

void UMyRogueWidget::GetRogueAbilityIndexAndString(int32 LastIndex, FString* AbilityName) {
	AbilityLastIndex = LastIndex;
	AbilityNames = AbilityName;
}

void UMyRogueWidget::GetSlashList() {
	AttackForm = 0;
	AttackFormMaxIndex = 6;
	Call_HaveAttackFormList();
}

void UMyRogueWidget::GetSmashList() {
	AttackForm = 1;
	AttackFormMaxIndex = 7;
	Call_HaveAttackFormList();
}

void UMyRogueWidget::GetStabList() {
	AttackForm= 2;
	AttackFormMaxIndex = 9;
	Call_HaveAttackFormList();
}

void UMyRogueWidget::GetSpecialList() {
	AttackForm = 3;
	AttackFormMaxIndex = 2;
	Call_HaveAttackFormList();
}
void UMyRogueWidget::GetSelectRogueAbilityOne() {
	if (RogueData > AbilityCost * 50.f) {
		MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(AbilityCost * 50.f);
		AbilityCost = 1.f;
		
		if (SelectAbilityIndex[0] <= 23) {
			MyGameMode->RogueTakeAbilityDelegate.ExecuteIfBound(SelectAbilityIndex[0]);
			MyGameMode->Widget_CallAbilityListDelegate.ExecuteIfBound();
		}
		else if (SelectAbilityIndex[0] == 24 || SelectAbilityIndex[0] == 25) {
			MyGameMode->Call_RogueHavingWeaponCheckDelegate.ExecuteIfBound(AbilityRandIndex[0]);
		}
		else if (SelectAbilityIndex[0] == 26) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(0, AbilityRandIndex[0]);
		}
		else if (SelectAbilityIndex[0] == 27) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(1, AbilityRandIndex[0]);
		}
		else if (SelectAbilityIndex[0] == 28) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(2, AbilityRandIndex[0]);
		}
		else if (SelectAbilityIndex[0] == 29) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(3, AbilityRandIndex[0]);
		}
		else if (SelectAbilityIndex[0] == 30 || SelectAbilityIndex[0] == 31) {
			MyGameMode->Call_RogueHavingElementalCheckDelegate.ExecuteIfBound(AbilityRandIndex[0]);
		}
		MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(10);
	}
}

void UMyRogueWidget::GetSelectRogueAbilityTwo() {
	if (RogueData > AbilityCost * 50.f) {
		MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(AbilityCost * 50.f);
		AbilityCost = 1.f;
		if (SelectAbilityIndex[1] <= 23) {
			MyGameMode->RogueTakeAbilityDelegate.ExecuteIfBound(SelectAbilityIndex[1]);
			MyGameMode->Widget_CallAbilityListDelegate.ExecuteIfBound();
		}
		else if (SelectAbilityIndex[1] == 24 || SelectAbilityIndex[1] == 25) {
			MyGameMode->Call_RogueHavingWeaponCheckDelegate.ExecuteIfBound(AbilityRandIndex[1]);
		}
		else if (SelectAbilityIndex[1] == 26) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(0, AbilityRandIndex[1]);
		}
		else if (SelectAbilityIndex[1] == 27) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(1, AbilityRandIndex[1]);
		}
		else if (SelectAbilityIndex[1] == 28) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(2, AbilityRandIndex[1]);
		}
		else if (SelectAbilityIndex[1] == 29) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(3, AbilityRandIndex[1]);
		}
		else if (SelectAbilityIndex[1] == 30 || SelectAbilityIndex[1] == 31) {
			MyGameMode->Call_RogueHavingElementalCheckDelegate.ExecuteIfBound(AbilityRandIndex[1]);
		}
		MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(10);
	}
}

void UMyRogueWidget::GetSelectRogueAbilityThree() {
	if (RogueData > AbilityCost * 50.f) {
		MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(AbilityCost * 50.f);
		AbilityCost = 1.f;
		if (SelectAbilityIndex[2] <= 23) {
			MyGameMode->RogueTakeAbilityDelegate.ExecuteIfBound(SelectAbilityIndex[2]);
			MyGameMode->Widget_CallAbilityListDelegate.ExecuteIfBound();
		}
		else if (SelectAbilityIndex[2] == 24 || SelectAbilityIndex[2] == 25) {
			MyGameMode->Call_RogueHavingWeaponCheckDelegate.ExecuteIfBound(AbilityRandIndex[2]);
		}
		else if (SelectAbilityIndex[2] == 26) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(0, AbilityRandIndex[2]);
		}
		else if (SelectAbilityIndex[2] == 27) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(1, AbilityRandIndex[2]);
		}
		else if (SelectAbilityIndex[2] == 28) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(2, AbilityRandIndex[2]);
		}
		else if (SelectAbilityIndex[2] == 29) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(3, AbilityRandIndex[2]);
		}
		else if (SelectAbilityIndex[2] == 30 || SelectAbilityIndex[2] == 31) {
			MyGameMode->Call_RogueHavingElementalCheckDelegate.ExecuteIfBound(AbilityRandIndex[2]);
		}
		MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(10);
	}
}

void UMyRogueWidget::GetSelectRogueAbilityFour() {
	if (RogueData > AbilityCost * 50.f) {
		MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(AbilityCost * 50.f);
		AbilityCost = 1.f;
		if (SelectAbilityIndex[3] <= 23) {
			
			MyGameMode->RogueTakeAbilityDelegate.ExecuteIfBound(SelectAbilityIndex[3]);
			MyGameMode->Widget_CallAbilityListDelegate.ExecuteIfBound();
		}
		else if (SelectAbilityIndex[3] == 24 || SelectAbilityIndex[3] == 25) {
			MyGameMode->Call_RogueHavingWeaponCheckDelegate.ExecuteIfBound(AbilityRandIndex[3]);
		}
		else if (SelectAbilityIndex[3] == 26) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(0, AbilityRandIndex[3]);
		}
		else if (SelectAbilityIndex[3] == 27) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(1, AbilityRandIndex[3]);
		}
		else if (SelectAbilityIndex[3] == 28) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(2, AbilityRandIndex[3]);
		}
		else if (SelectAbilityIndex[3] == 29) {
			MyGameMode->Call_RogueHavingAttackFormCheckDelegate.ExecuteIfBound(3, AbilityRandIndex[3]);
		}
		else if (SelectAbilityIndex[3] == 30 || SelectAbilityIndex[3] == 31) {
			MyGameMode->Call_RogueHavingElementalCheckDelegate.ExecuteIfBound(AbilityRandIndex[3]);
		}
		MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(10);
	}
}

void UMyRogueWidget::GetDialogue(FString* DialogueData, int32 DialogueIndex) {

}

void UMyRogueWidget::AbilityListString() {
	RogueAbilityListString[0] = TEXT("Slash DamegeUp");
	RogueAbilityListString[1] = TEXT("Smash Damege Up");
	RogueAbilityListString[2] = TEXT("Stab DamegeUp");
	RogueAbilityListString[3] = TEXT("BurnAttack DamegeUp");
	RogueAbilityListString[4] = TEXT("Physics DamegeUp");
	RogueAbilityListString[5] = TEXT("Fire DamegeUp");
	RogueAbilityListString[6] = TEXT("Ice DamegeUp");
	RogueAbilityListString[7] = TEXT("Poison DamegeUp");
	RogueAbilityListString[8] = TEXT("Lightning DamegeUp");
	RogueAbilityListString[9] = TEXT("BurnAttack HitUp");
	RogueAbilityListString[10] = TEXT("Move SpeedUp");
	RogueAbilityListString[11] = TEXT("Hit KnockBack");
	RogueAbilityListString[12] = TEXT("SuperArmorUp");
	RogueAbilityListString[13] = TEXT("Absorbed");
	RogueAbilityListString[14] = TEXT("Thrifty Spirit");
	RogueAbilityListString[15] = TEXT("TorchSkill PercentUp");
	RogueAbilityListString[16] = TEXT("WeaponSkill PercentUp");
	RogueAbilityListString[17] = TEXT("TorchSkill DamegeUp");
	RogueAbilityListString[18] = TEXT("WeaponSkill DamegeUp");
	RogueAbilityListString[19] = TEXT("Attack SpeedUp");
	RogueAbilityListString[20] = TEXT("Heroics Power");
	RogueAbilityListString[21] = TEXT("Arrogant Power");
	RogueAbilityListString[22] = TEXT("Berserk Fury");
	RogueAbilityListString[23] = TEXT("HpUp");
}

void UMyRogueWidget::WeaponListString() {
	RogueHaveWeaponListString[0] = TEXT("Dagger");
	RogueHaveWeaponListString[1] = TEXT("Mace");
	RogueHaveWeaponListString[2] = TEXT("GreatAxe");
	RogueHaveWeaponListString[3] = TEXT("GreatHammer");
	RogueHaveWeaponListString[4] = TEXT("LongSword");
	RogueHaveWeaponListString[5] = TEXT("ShortSword");
	RogueHaveWeaponListString[6] = TEXT("HandAxe");
	RogueHaveWeaponListString[7] = TEXT("Spear");
	RogueHaveWeaponListString[8] = TEXT("Scythe");
	RogueHaveWeaponListString[9] = TEXT("Knife");
}

void UMyRogueWidget::AttackFormString() {
	RogueAttackFormListString[0][0] = TEXT("Slash");
	RogueAttackFormListString[0][1] = TEXT("Reverse Slash");
	RogueAttackFormListString[0][2] = TEXT("Bash Slash");
	RogueAttackFormListString[0][3] = TEXT("Upper Slash");
	RogueAttackFormListString[0][4] = TEXT("X Slash");
	RogueAttackFormListString[0][5] = TEXT("DownUpper Combo");
	RogueAttackFormListString[0][6] = TEXT("White Fang");

	RogueAttackFormListString[1][0] = TEXT("Smash");
	RogueAttackFormListString[1][1] = TEXT("Breaker");
	RogueAttackFormListString[1][2] = TEXT("Side Smash");
	RogueAttackFormListString[1][3] = TEXT("Side Breaker");
	RogueAttackFormListString[1][4] = TEXT("Ground Breaker");
	RogueAttackFormListString[1][5] = TEXT("ReverseSide Smash");
	RogueAttackFormListString[1][6] = TEXT("HeadDancer");
	RogueAttackFormListString[1][7] = TEXT("Cranker");

	RogueAttackFormListString[2][0] = TEXT("Stab");
	RogueAttackFormListString[2][1] = TEXT("Quick Stab");
	RogueAttackFormListString[2][2] = TEXT("Deep Stab");
	RogueAttackFormListString[2][3] = TEXT("Side Stab");
	RogueAttackFormListString[2][4] = TEXT("Upper Stab");
	RogueAttackFormListString[2][5] = TEXT("OneInch Stab");
	RogueAttackFormListString[2][6] = TEXT("Double Stab");
	RogueAttackFormListString[2][7] = TEXT("Double Faces");
	RogueAttackFormListString[2][8] = TEXT("Double Holes");
	RogueAttackFormListString[2][9] = TEXT("Double Lanes");

	RogueAttackFormListString[3][0] = TEXT("AirTrack");
	RogueAttackFormListString[3][1] = TEXT("DeleteLeg");
	RogueAttackFormListString[3][2] = TEXT("TurnEnd");

	RogueAttackFormVideoString[0][0] = TEXT("FileMediaSource'/Game/AttackImage/Slash/DefaultSlash1.DefaultSlash1'");
	RogueAttackFormVideoString[0][1] = TEXT("FileMediaSource'/Game/AttackImage/Slash/DefaultSlash2.DefaultSlash2'");
	RogueAttackFormVideoString[0][2] = TEXT("FileMediaSource'/Game/AttackImage/Slash/BashSlash1.BashSlash1'");
	RogueAttackFormVideoString[0][3] = TEXT("FileMediaSource'/Game/AttackImage/Slash/UpperSlash1.UpperSlash1'");
	RogueAttackFormVideoString[0][4] = TEXT("FileMediaSource'/Game/AttackImage/Slash/XSalsh1.XSalsh1'");
	RogueAttackFormVideoString[0][5] = TEXT("FileMediaSource'/Game/AttackImage/Slash/SlashCombo1.SlashCombo1'");
	RogueAttackFormVideoString[0][6] = TEXT("FileMediaSource'/Game/AttackImage/Slash/WhiteFang1.WhiteFang1'");

	RogueAttackFormVideoString[1][0] = TEXT("FileMediaSource'/Game/AttackImage/Smash/DefaultSmash.DefaultSmash'");
	RogueAttackFormVideoString[1][1] = TEXT("FileMediaSource'/Game/AttackImage/Smash/DefaultBreaker.DefaultBreaker'");
	RogueAttackFormVideoString[1][2] = TEXT("FileMediaSource'/Game/AttackImage/Smash/SideSmash.SideSmash'");
	RogueAttackFormVideoString[1][3] = TEXT("FileMediaSource'/Game/AttackImage/Smash/PowerSideSmash.PowerSideSmash'");
	RogueAttackFormVideoString[1][4] = TEXT("FileMediaSource'/Game/AttackImage/Smash/GroundBreak.GroundBreak'");
	RogueAttackFormVideoString[1][5] = TEXT("FileMediaSource'/Game/AttackImage/Smash/ReverseSideSmash.ReverseSideSmash'");
	RogueAttackFormVideoString[1][6] = TEXT("FileMediaSource'/Game/AttackImage/Smash/HeadDancer.HeadDancer'");
	RogueAttackFormVideoString[1][7] = TEXT("FileMediaSource'/Game/AttackImage/Smash/Cranker.Cranker'");

	RogueAttackFormVideoString[2][0] = TEXT("FileMediaSource'/Game/AttackImage/Stab/DefaultStab.DefaultStab'");
	RogueAttackFormVideoString[2][1] = TEXT("FileMediaSource'/Game/AttackImage/Stab/QuickStab.QuickStab'");
	RogueAttackFormVideoString[2][2] = TEXT("FileMediaSource'/Game/AttackImage/Stab/DeepStab.DeepStab'");
	RogueAttackFormVideoString[2][3] = TEXT("FileMediaSource'/Game/AttackImage/Stab/SideStab.SideStab'");
	RogueAttackFormVideoString[2][4] = TEXT("FileMediaSource'/Game/AttackImage/Stab/UpperStab.UpperStab'");
	RogueAttackFormVideoString[2][5] = TEXT("FileMediaSource'/Game/AttackImage/Stab/OneInchStab.OneInchStab'");
	RogueAttackFormVideoString[2][6] = TEXT("FileMediaSource'/Game/AttackImage/Stab/DoubleStab.DoubleStab'");
	RogueAttackFormVideoString[2][7] = TEXT("FileMediaSource'/Game/AttackImage/Stab/DoubleLane.DoubleLane'");
	RogueAttackFormVideoString[2][8] = TEXT("FileMediaSource'/Game/AttackImage/Stab/DoubleHoles.DoubleHoles'");
	RogueAttackFormVideoString[2][9] = TEXT("FileMediaSource'/Game/AttackImage/Stab/DoubleFace.DoubleFace'");
	
	RogueAttackFormVideoString[3][0] = TEXT("FileMediaSource'/Game/AttackImage/SpecialArts/AirTrack.AirTrack'");
	RogueAttackFormVideoString[3][1] = TEXT("FileMediaSource'/Game/AttackImage/SpecialArts/DeleteLeg.DeleteLeg'");
	RogueAttackFormVideoString[3][2] = TEXT("FileMediaSource'/Game/AttackImage/SpecialArts/TurnEnd.TurnEnd'");
}

void UMyRogueWidget::ElementString() {
	RogueElementString[0] = TEXT("Physical");
	RogueElementString[1] = TEXT("Heat");
	RogueElementString[2] = TEXT("Chill");
	RogueElementString[3] = TEXT("Toxin");
	RogueElementString[4] = TEXT("Electric");
	RogueElementString[5] = TEXT("Physical");
	RogueElementString[6] = TEXT("Heat");
	RogueElementString[7] = TEXT("Chill");
	RogueElementString[8] = TEXT("Toxin");
	RogueElementString[9] = TEXT("Electric");

	RogueElementString[10] = TEXT("Strenght");
	RogueElementString[11] = TEXT("Fire");
	RogueElementString[12] = TEXT("Frost");
	RogueElementString[13] = TEXT("Poison");
	RogueElementString[14] = TEXT("Lightning");
	RogueElementString[15] = TEXT("Strenght");
	RogueElementString[16] = TEXT("Fire");
	RogueElementString[17] = TEXT("Frost");
	RogueElementString[18] = TEXT("Poison");
	RogueElementString[19] = TEXT("Lightning");

	RogueElementString[20] = TEXT("Smite");
	RogueElementString[21] = TEXT("Flame");
	RogueElementString[22] = TEXT("Freeze");
	RogueElementString[23] = TEXT("Venom");
	RogueElementString[24] = TEXT("Thunderbolt");
	RogueElementString[25] = TEXT("Smite");
	RogueElementString[26] = TEXT("Flame");
	RogueElementString[27] = TEXT("Freeze");
	RogueElementString[28] = TEXT("Venom");
	RogueElementString[29] = TEXT("Thunderbolt");
}

void UMyRogueWidget::ButtonStyleInit() {
	const FSlateColor HoveredColor(FLinearColor(1.f, 1.f, 1.f, 0.4f));
	const FSlateColor PressedColor(FLinearColor(1.f, 1.f, 1.f, 0.8f));
	FSlateBrush ButtonBrush[3];
	ButtonBrush[0].DrawAs = ESlateBrushDrawType::NoDrawType;
	ButtonBrush[1].DrawAs = ESlateBrushDrawType::Box;
	ButtonBrush[2].DrawAs = ESlateBrushDrawType::Box;
	ButtonBrush[1].TintColor = HoveredColor;
	ButtonBrush[2].TintColor = PressedColor;
	NewWeaponAndSkillButton
		.SetNormal(ButtonBrush[0])
		.SetHovered(ButtonBrush[1])
		.SetPressed(ButtonBrush[2]);
		//.SetNormalPadding(FMargin(2, 2, 2, 2))
		//.SetPressedPadding(FMargin(2, 2, 2, 2));
}

void UMyRogueWidget::WeaponImagesRefInit() {
	WeaponImagesRef[0] = TEXT("Texture2D'/Game/WeaponFixImage/DaggerImage.DaggerImage'");
	WeaponImagesRef[1] = TEXT("Texture2D'/Game/WeaponFixImage/MaceImage.MaceImage'");
	WeaponImagesRef[2] = TEXT("Texture2D'/Game/WeaponFixImage/GreatAxe.GreatAxe'");
	WeaponImagesRef[3] = TEXT("Texture2D'/Game/WeaponFixImage/GreatHammer.GreatHammer'");
	WeaponImagesRef[4] = TEXT("Texture2D'/Game/WeaponFixImage/GreatSword.GreatSword'");
	WeaponImagesRef[5] = TEXT("Texture2D'/Game/WeaponFixImage/ShortSword.ShortSword'");
	WeaponImagesRef[6] = TEXT("Texture2D'/Game/WeaponFixImage/HandAxe.HandAxe'");
	WeaponImagesRef[7] = TEXT("Texture2D'/Game/WeaponFixImage/Spear.Spear'");
	WeaponImagesRef[8] = TEXT("Texture2D'/Game/WeaponFixImage/Scythe.Scythe'");
	WeaponImagesRef[9] = TEXT("Texture2D'/Game/WeaponFixImage/Knife.Knife'");
}

void UMyRogueWidget::Receive_ReturnRogueUseWeaponRef(int32 UseWeaponNumber) {
	UsedWeaponNumber = UseWeaponNumber;
}

void UMyRogueWidget::RogueUseWeaponRefCheck() {
	switch (UsedWeaponNumber) {
	case 0:
		GetDaggerImage();
		break;
	case 1:
		GetMaceImage();
		break;
	case 2:
		GetGAxeImage();
		break;
	case 3:
		GetGHammerImage();
		break;
	case 4:
		GetGSwordImage();
		break;
	case 5:
		GetSSwordImage();
		break;
	case 6:
		GetAxeImage();
		break;
	case 7:
		GetSpearImage();
		break;
	case 8:
		GetScytheImage();
		break;
	case 9:
		GetKnifeImage();
		break;
	}
}

void UMyRogueWidget::ToolTipInit() {
	IconToolTip[0] = FText::FromString(TEXT("Slash Specialization"));
	IconToolTip[1] = FText::FromString(TEXT("Smash Specialization"));
	IconToolTip[2] = FText::FromString(TEXT("Stab Specialization"));
	IconToolTip[3] = FText::FromString(TEXT("Elemental Specialization"));
	IconToolTip[4] = FText::FromString(TEXT("High DPS"));
	IconToolTip[5] = FText::FromString(TEXT("Great Balance"));
	
}

void UMyRogueWidget::ElementIconInit() {
	ElementIcon[0] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/64.64'")));
	ElementIcon[1] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/76.76'")));
	ElementIcon[2] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/36.36'")));
	ElementIcon[3] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/80.80'")));
	ElementIcon[4] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/34.34'")));
	
	ElementIcon[5] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/65.65'")));
	ElementIcon[6] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/78.78'")));
	ElementIcon[7] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/82.82'")));
	ElementIcon[8] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/92.92'")));
	ElementIcon[9] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/49.49'")));
	
	ElementIcon[10] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/66.66'")));
	ElementIcon[11] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/79.79'")));
	ElementIcon[12] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/83.83'")));
	ElementIcon[13] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/26.26'")));
	ElementIcon[14] = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL,
		TEXT("Texture2D'/Game/FlatSkillsIcons100/53.53'")));
}

void UMyRogueWidget::ElementalPhaseCheck() {
	MyGameMode->Widget_StatDataDelegate.BindUObject(this, &UMyRogueWidget::GetRogueStatValue);
	MyGameMode->Widget_CallStatWidgetDelegate.ExecuteIfBound();
	if (RogueStatData[8] > 10 && RogueStatData[6] > 10) {
		WeaponElementalPhase = 2;
		for (int i = 0; i < 5; i++) {
			SelectElementIcon[0][i] = ElementIcon[i + 10];
			SelectElementString[0][i] = RogueElementString[i+20];
		}
	}
	else if (RogueStatData[8] > 5 && RogueStatData[6] > 5) {
		WeaponElementalPhase = 1;
		for (int i = 0; i < 5; i++) {
			SelectElementIcon[0][i] = ElementIcon[i + 5];
			SelectElementString[0][i] = RogueElementString[i + 10];
		}
	}
	else if (RogueStatData[8] <= 5 || RogueStatData[6] <= 5) {
		WeaponElementalPhase = 0;
		for (int i = 0; i < 5; i++) {
			SelectElementIcon[0][i] = ElementIcon[i];
			SelectElementString[0][i] = RogueElementString[i];
		}
	}
	
	if (RogueStatData[8] > 10 && RogueStatData[7] > 10) {
		TorchElementalPhase = 2;
		for (int i = 0; i < 5; i++) {
			SelectElementIcon[1][i] = ElementIcon[i + 10];
			SelectElementString[1][i] = RogueElementString[i + 20];
		}
	}
	else if (RogueStatData[8] > 5 && RogueStatData[7] > 5) {
		TorchElementalPhase = 1;
		for (int i = 0; i < 5; i++) {
			SelectElementIcon[1][i] = ElementIcon[i + 5];
			SelectElementString[1][i] = RogueElementString[i + 10];
		}
	}
	else if (RogueStatData[8] <= 5 || RogueStatData[7] <= 5) {
		TorchElementalPhase = 0;
		for (int i = 0; i < 5; i++) {
			SelectElementIcon[1][i] = ElementIcon[i];
			SelectElementString[1][i] = RogueElementString[i];
		}
	}
}

void UMyRogueWidget::TaskSetting() {
	
}