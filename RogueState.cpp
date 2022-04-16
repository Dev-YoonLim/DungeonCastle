// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueState.h"
#include "Rogue.h"
#include "EnemyRogue.h"


ARogueState::ARogueState() {
	TorchElementInit();
	WeaponElementInit();
	DataInit();
	KarmaInit();
	RogueKillInit();
	AbilityInit();
	SetFullMaxRogueHp(300.f);
	CurrentHpInit();
	HadWeaponCheckInit();
	HadAttackFormCheckInit();
	AbilityHadCheckInit();
	ElementalHadCheckInit();
	DialogueRefInit();
	SaveState = false;
	for (int i = 0; i < 10; i++) {
		DoorStateCheck[i] = 0;
	}
}

void ARogueState::AbilityInit() {
	DialogueRefInit();
	TotalEquipCount = 0;
	EquipAbilityCount = 0;
	DialogueTutorialCount = 1;
	ItemCount = 0;
	WeaponElementNumber = 0;
	TorchElementNumber = 0;
	Strength = 0;
	Concentration = 0;
	Calmness = 0;
	Agility = 0;
	ElementLevel = 1.f;
	ElementLevelValue = 1.f + ElementLevel * 0.05;
	TorchElementSpecialSynergy = 1.f;
	TorchElementCriper = 1.f;
	TorchBurnAttackSynergy = 1.f;
	UseDataValuePercent = 1.f;
	CurrentData = 300;
	SlashValueBonus = 1.f;
	BreakValueBonus = 1.f;
	StabValueBonus = 1.f;
	TorchBurnAttackSynergyValue = 1.f;
	TorchElementCriperValue = 1.f;
	WeaponElementValueBonus = 1.f;
	WeaponSpeedValueBonus = 1.f;
	WeaponElementDamegeBonus = 1.f;
	TorchSpecialTotalDamegeValue = 1.f;
	MoveSpeedIncreaseCountValue = 1.f;
	HitToKnockBackCount = 0;
	TotalAbilityCount = 0;
	TotalWeaponCount = 0;
	TotalElementCount = 0;
	TotalAttackFormCount = 0;
	WeaponLevel = 1;
	TorchLevel = 1;
	ElementLevel = 1;
	WeaponLevelEx = 0.f;
	TorchLevelEx = 0.f;
	ElementLevelEx = 0.f;
	WeaponLevelExMax = 10.f;
	TorchLevelExMax = 10.f;
	ElementLevelExMax = 10.f;
	WeaponLevelValue = 1.f+WeaponLevel * 0.05;
	TorchLevelValue = 1.f + TorchLevel * 0.05;
	ElementLevelValue = 1.f + ElementLevel * 0.05;
	SaveSlotName = TEXT("SaveSlot");
	GameSettingName = TEXT("GameSettingSave");
	DialogueIndex = 0;
}

void ARogueState::BeginPlay() {
	Super::BeginPlay();
	HadWeaponCheckInit();
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("RogueStateOn")));
	DialgoueStateInit();
	getWorldGameModeBase();
	TorchElementDelegateInit();
	WeaponElementDelegateInit();
	WeaponChangeDelegateInit();
	AttackAnimationDelegateInit();
	DamegeDelegateInit();
	RogueDataAndKarmaDelegateInit();
	LastWeaponDamegeSetting();
	LastTorchDamegeSetting();
	LastSpeedSetting();
	RogueAttackPlusIncreaseDelegateInit();
	MyGameMode->RogueWeaponLevelDelegate.BindUObject(this, &ARogueState::SetWeaponLevelUp);
	MyGameMode->Widget_RogueUIValueInitDelegate.BindUObject(this, &ARogueState::Widget_ViewInit);
	MyGameMode->Rogue_SpeedValueDelegate.BindUObject(this, &ARogueState::GetMoveSpeed);
	MyGameMode->Widget_CallStatWidgetDelegate.BindUObject(this, &ARogueState::SetStatData);
	MyGameMode->Widget_CallGameStateWidgetDelegate.BindUObject(this, &ARogueState::SetGameState);
	MyGameMode->Widget_CallEquipmentWidgetDelegate.BindUObject(this, &ARogueState::SetEquipmentStrings);
	MyGameMode->RogueTakeAbilityDelegate.BindUObject(this, &ARogueState::AbilityRandTake);
	MyGameMode->Widget_CallAbilityListDelegate.BindUObject(this, &ARogueState::GetRogueAbilityIndexAndString);
	MyGameMode->Call_RogueTakeHaveWeaponDelegate.BindUObject(this, &ARogueState::Call_HadWeapon);
	MyGameMode->Call_RogueTakeHaveAttackFormDelegate.BindUObject(this, &ARogueState::Call_HadAttackForm);
	MyGameMode->Call_RogueTakeHaveAbilityDelegate.BindUObject(this, &ARogueState::Call_HadAbility);
	MyGameMode->Call_RogueTakeHaveElementalDelegate.BindUObject(this, &ARogueState::Call_Elemental);
	MyGameMode->Call_RogueHavingWeaponCheckDelegate.BindUObject(this, &ARogueState::WeaponHadCheck);
	MyGameMode->Call_RogueHavingAttackFormCheckDelegate.BindUObject(this, &ARogueState::AttackFormHadCheck);
	MyGameMode->Call_RogueHavingAbilityCheckDelegate.BindUObject(this, &ARogueState::AbilityHadCheck);
	MyGameMode->Call_RogueHavingElementalCheckDelegate.BindUObject(this, &ARogueState::ElementalHadCheck);
	MyGameMode->Call_GameStartWeaponNumberDelegate.BindUObject(this, &ARogueState::Call_RogueStartWeaponNumber);
	MyGameMode->Call_GameStartAttackFormNumberDelegate.BindUObject(this, &ARogueState::Call_RogueStartAttackFormNumber);
	MyGameMode->Call_GameStartTorchElementalNumberDelegate.BindUObject(this, &ARogueState::Call_RogueStartTorchElementalNumber);
	MyGameMode->Call_TakeAttackFormRefDelegate.BindUObject(this, &ARogueState::SetEquipmentAttackFormString);
	MyGameMode->Call_TakeAttackFormDelegate.BindUObject(this, &ARogueState::AttackFormChange);
	MyGameMode->Call_RogueDamageDelegate.BindUObject(this, &ARogueState::SetDamegedRogue);
	MyGameMode->Call_GameSaveDelegate.BindUObject(this, &ARogueState::SaveGameData);
	MyGameMode->Call_GameSettingSaveDelegate.BindUObject(this, &ARogueState::SaveGameSetting);
	//RogueDataInit();
	//Call_RogueStartAttackFormNumber();
	//Call_RogueStartWeaponNumber();
	//Call_RogueStartTorchElementalNumber();
}

void ARogueState::GameSettingSaveInit() {
	UGameSettingSave* LoadSetting = Cast<UGameSettingSave>(UGameplayStatics::LoadGameFromSlot(GameSettingName, 0));
	if (LoadSetting == nullptr) {
		//MyGameMode->NewGameStart = true;
		GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Orange, FString::Printf(TEXT("LoadFailCheck")));
		LoadSetting = GetMutableDefault<UGameSettingSave>();
	}
	else {
		//MyGameMode->NewGameStart = false;
		LoadGameSetting(LoadSetting);
	}
	SaveGameSetting();
}

void ARogueState::LoadGameSetting(UGameSettingSave* LoadSettingData) {
	UGameSettingSave* LoadSettings = Cast<UGameSettingSave>(LoadSettingData);
	ARogue* myRogue = Cast<ARogue>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	MyGameMode->FXSoundClass->Properties.Volume = LoadSettings->FXSoundVolume;
	MyGameMode->FOVValue = LoadSettings->FOVValue;
	myRogue->RogueHeadShake = LoadSettings->HeadTracking;
	MyGameMode->LanguageType = LoadSettings->LanguageType;
}

void ARogueState::RogueDataInit() {
	URogueSaveGame* LoadGame = Cast<URogueSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (LoadGame == nullptr) {
		//MyGameMode->NewGameStart = true;
		GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Orange, FString::Printf(TEXT("LoadFailCheck")));
		LoadGame = GetMutableDefault<URogueSaveGame>();
	}
	else {
		//MyGameMode->NewGameStart = false;
		LoadGameData(LoadGame);
	}
	SaveGameData();
}

void ARogueState::LoadGameData(URogueSaveGame* LoadData) {
	URogueSaveGame* LoadGame = Cast<URogueSaveGame>(LoadData);
	//if (UGameplayStatics::GetCurrentLevelName(GetWorld(), false) != TEXT("StartMap")) {
	GEngine->AddOnScreenDebugMessage(-1, 600, FColor::Purple, FString::Printf(TEXT("Load")));
	ARogue* myRogue = Cast<ARogue>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	for (int i = 2; i <= LoadGame->WeaponLevel; i++) {
		SetWeaponLevelUp();
		WeaponLevelExMax = WeaponLevelExMax + (5 * 1.2 * WeaponLevel);
	}
	for (int i = 2; i <= LoadGame->TorchLevel; i++) {
		SetTorchLevelUp();
		TorchLevelExMax = WeaponLevelExMax + (5 * 1.2 * TorchLevel);
	}
	for (int i = 2; i <= LoadGame->ElementalLevel; i++) {
		SetElementLevelUp();
		ElementLevelExMax = WeaponLevelExMax + (5 * 1.2 * ElementLevel);
	}

	WeaponLevelEx = LoadGame->WeaponLevelEx;
	TorchLevelEx = LoadGame->TorchLevelEx;
	ElementLevelEx = LoadGame->ElementalLevelEx;
	RogueDeath = LoadGame->RogueDeath;
	RogueKill = LoadGame->RogueKill;
	RogueTotalKill = LoadGame->RogueTotalKill;

	DungeonClearAllCount = LoadGame->DungeonClearAllCount;
	for (int i = 0; i < 3; i++) {
		DungeonClearCount[i] = LoadGame->DungeonClearCount[i];
	}
	for (int i = 0; i < 10; i++) {
		DoorStateCheck[i] = LoadGame->DoorOpenCheck[i];
	}

	/*TSubclassOf<AEnemyRogue> EnemyRogueClass;
	//AEnemyRogue* enemyRogue = Cast<AEnemyRogue>(UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyRogueClass, EnemyRogueClass));
	for (int i = 0; i < 10; i++) {
		DoorStateCheck[i] = LoadGame->DoorOpenCheck[i];
	}
	for (int i = 0; i < LoadGame->TotalEquipAbilityCount; i++) {
		int Index = LoadGame->TotalEquipAbilityDataList[i];
		AbilityRandTake(Index);
	}
	for (int i = 0; i < LoadGame->TotalTakeWeaponCount; i++) {
		int Index = LoadGame->TotalTakeWeaponDataList[i];
		WeaponHadCheck(Index);
	}
	for (int i = 0; i < LoadGame->TotalTakeElementalCount; i++) {
		int Index = LoadGame->TotalTakeElementalDataList[i];
		ElementalHadCheck(Index);
	}
	for (int i = 0; i < LoadGame->TotalAttackFormCount; i++) {
		int Index1 = LoadGame->TotalAttackFormDataList1[i];
		int Index2 = LoadGame->TotalAttackFormDataList2[i];
		AttackFormHadCheck(Index1, Index2);
		
	}
	for (int i = 2; i <= LoadGame->WeaponLevel; i++) {
		SetWeaponLevelUp();
		WeaponLevelExMax = WeaponLevelExMax + (5 * 1.2 * WeaponLevel);
	}
	for (int i = 2; i <= LoadGame->TorchLevel; i++) {
		SetTorchLevelUp();
		TorchLevelExMax = WeaponLevelExMax + (5 * 1.2 * TorchLevel);
	}
	for (int i = 2; i <= LoadGame->ElementalLevel; i++) {
		SetElementLevelUp();
		ElementLevelExMax = WeaponLevelExMax + (5 * 1.2 * ElementLevel);
	}
	myRogue->SetRollingTrdCamera(LoadGame->RollingTrdCamera);

	MyGameMode->StageIndex = LoadGame->StageIndex;
	MyGameMode->StageSubIndex = LoadGame->StageSubIndex;
	GEngine->AddOnScreenDebugMessage(-1, 600, FColor::Purple, FString::Printf(TEXT("Load Stage Index %d"), LoadGame->StageIndex));
	WeaponNumber = LoadGame->WeaponNumber;
	GEngine->AddOnScreenDebugMessage(-1, 600, FColor::Orange, FString::Printf(TEXT("LoadWeapon %d"), WeaponNumber));
	WeaponElementNumber = LoadGame->WeaponElemental;
	TorchElementNumber = LoadGame->TorchElemental;
	FullMaxHp = LoadGame->RogueHp;
	RogueHp = LoadGame->RogueHp;
	CurrentData = LoadGame->RogueData;
	CurrentKarma = LoadGame->RogueKarma;
	AllData = LoadGame->AllData;
	MyGameMode->NewGameStart = LoadGame->NewGameStart;
	SetDialogueIndex(LoadGame->DialogueIndex);
	ItemCount = LoadGame->ItemCount;
	RogueDeath = LoadGame->RogueDeath;
	RogueKill = LoadGame->RogueKill;
	RogueTotalKill = LoadGame->RogueTotalKill;
	UsedData = LoadGame->UsedData;
	//RogueMoveSpeed = LoadGame->RogueMoveSpeed;
	//MyGameMode->StageIndex = LoadGame->StageNumber;
	//myRogue->SetActorLocation(LoadGame->LastLocation);
	DungeonClearAllCount = LoadGame->DungeonClearAllCount;
	for (int i = 0; i < 3; i++) {
		DungeonClearCount[i] = LoadGame->DungeonClearCount[i];
	}
	for (int i = 0; i < 3; i++) {
		AttackForm[i] = LoadGame->AttackForm[i];
		AttackFormIndex[i] = LoadGame->AttackFormDetail[i];
	}
	if (UGameplayStatics::GetCurrentLevelName(GetWorld(), false) == TEXT("StartMap_2")) {
		LoadGame->StageIndex = 0;
		MyGameMode->StageIndex = LoadGame->StageIndex;
	}
	for (int i = 0; i < 7; i++)
		StartDialogueState[i] = LoadGame->StartDialogueState[i];

	for (int i = 0; i < 5; i++) {
		MainDialogueState[i] = LoadGame->MainDialogueState[i];
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			SubDialogueState[i][j] = LoadGame->SubDialogueState[(i*4)+j];
		}
	}
	myRogue->SetStartDialogueIndex(LoadGame->StartDialogueIndex);
	myRogue->SetMainDialogueIndex(LoadGame->MainDialogueIndex);
	myRogue->SetSubDialogueIndex(LoadGame->SubDialogueIndex);
	myRogue->SetSubDialogueKinds(LoadGame->SubDialogueKinds);
	DialogueTutorialCount = LoadGame->DialogueTutorialCount;
	
	else {
		LoadGame->StageIndex = 0;
		MyGameMode->StageIndex = LoadGame->StageIndex;
	}*/
}

void ARogueState::SaveGameSetting() {
	UGameSettingSave* SettingData = NewObject<UGameSettingSave>();
	ARogue* myRogue = Cast<ARogue>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("GameSettingSave")));
	SettingData->FXSoundVolume = MyGameMode->FXSoundClass->Properties.Volume;
	SettingData->FOVValue = MyGameMode->FOVValue;
	SettingData->HeadTracking = myRogue->RogueHeadShake;
	SettingData->LanguageType = MyGameMode->LanguageType;
	if (UGameplayStatics::SaveGameToSlot(SettingData, GameSettingName, 0) == false) {
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("SaveError")));
	}
}

void ARogueState::SaveGameData() {
	URogueSaveGame* PlayerData = NewObject<URogueSaveGame>();
	
	ARogue* myRogue = Cast<ARogue>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//ShortCutDoor = Cast<TArray<ADoor>>(UGameplayStatics::GetActorOfClass(GetWorld(), ADoor::StaticClass()));
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("GameSave")));
	if (SaveState == true) {
		PlayerData->WeaponLevel = WeaponLevel;
		PlayerData->TorchLevel = TorchLevel;
		PlayerData->ElementalLevel = ElementLevel;
		PlayerData->WeaponLevelEx = WeaponLevelEx;
		PlayerData->TorchLevelEx = TorchLevelEx;
		PlayerData->ElementalLevelEx = ElementLevelEx;

		PlayerData->RogueKill = RogueKill;
		PlayerData->RogueDeath = RogueDeath;
		PlayerData->RogueTotalKill = RogueTotalKill;

		PlayerData->DungeonClearAllCount = DungeonClearAllCount;
		for (int i = 0; i < 3; i++) {
			PlayerData->DungeonClearCount[i] = DungeonClearCount[i];
		}
		for (int i = 0; i < 10; i++) {
			PlayerData->DoorOpenCheck[i] = DoorStateCheck[i];
		}
		/*PlayerData->FXSoundVolume = MyGameMode->FXSoundClass->Properties.Volume;
		PlayerData->FOVValue = MyGameMode->FOVValue;
		PlayerData->HeadTracking = myRogue->RogueHeadShake;
		PlayerData->LanguageType = MyGameMode->LanguageType;
		PlayerData->DialogueTutorialCount = DialogueTutorialCount;
		PlayerData->StageIndex = MyGameMode->StageIndex;
		PlayerData->StageSubIndex = MyGameMode->StageSubIndex;
		PlayerData->TotalEquipAbilityCount = TotalAbilityCount;
		PlayerData->TotalTakeWeaponCount = TotalWeaponCount;
		PlayerData->TotalTakeElementalCount = TotalElementCount;
		PlayerData->TotalAttackFormCount = TotalAttackFormCount;

		PlayerData->TotalEquipAbilityDataList = TotalEquipAbilityDataList;
		PlayerData->TotalTakeWeaponDataList = TotalWeaponDataList;
		PlayerData->TotalTakeElementalDataList = TotalElementDataList;
		PlayerData->TotalAttackFormDataList1 = TotalAttackFormDataList1;
		PlayerData->TotalAttackFormDataList2 = TotalAttackFormDataList2;

		PlayerData->WeaponNumber = WeaponNumber;

		PlayerData->TorchElemental = TorchElementNumber;
		PlayerData->WeaponElemental = WeaponElementNumber;
		/*PlayerData->WeaponElemental = WeaponElementNumber;
		PlayerData->TorchElemental = TorchElementNumber;

		PlayerData->WeaponLevel = WeaponLevel;
		PlayerData->TorchLevel = TorchLevel;
		PlayerData->ElementalLevel = ElementLevel;

		PlayerData->RogueHp = GetRogueFullHp();
		PlayerData->RogueData = CurrentData;
		PlayerData->AllData = AllData;
		PlayerData->RogueKarma = CurrentKarma;
		PlayerData->NewGameStart = MyGameMode->NewGameStart;
		PlayerData->ItemCount = ItemCount;
		PlayerData->RollingTrdCamera = myRogue->GetRollingTrdCamera();
		//PlayerData->RogueMoveSpeed = RogueMoveSpeed;
		PlayerData->DungeonClearAllCount = DungeonClearAllCount;
		PlayerData->RogueDeath = RogueDeath;
		PlayerData->RogueKill = RogueKill;
		PlayerData->RogueTotalKill = RogueTotalKill;
		PlayerData->UsedData = UsedData;
		for (int i = 0; i < 10; i++) {
			PlayerData->DoorOpenCheck[i] = DoorStateCheck[i];
		}
		for (int i = 0; i < 3; i++) {
			PlayerData->DungeonClearCount[i] = DungeonClearCount[i];
		}
		for (int i = 0; i < 3; i++) {
			PlayerData->AttackForm[i] = AttackForm[i];
			PlayerData->AttackFormDetail[i] = AttackFormIndex[i];
			PlayerData->StoryProgress[i] = MyGameMode->StoryProgress[i];
		}
		for (int i = 0; i < 7; i++)
			PlayerData->StartDialogueState[i] = StartDialogueState[i];

		for (int i = 0; i < 5; i++) {
			PlayerData->MainDialogueState[i] = MainDialogueState[i];
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				int index;
				if (i == 0)
					index = j;
				else
					index = 4 * i + j;
				PlayerData->SubDialogueState[index] = SubDialogueState[i][j]; //2차배열이 안돼서 이렇게 짰다. 근데 사실 다른방법도 있긴 한데...ㅜㅜ
			}
		}
		PlayerData->StartDialogueIndex = myRogue->GetStartDialogueIndex();
		PlayerData->MainDialogueIndex = myRogue->GetMainDialogueIndex();
		PlayerData->SubDialogueIndex = myRogue->GetSubDialogueIndex();
		PlayerData->SubDialogueKinds = myRogue->GetSubDialogueKinds();
		//PlayerData->LastLocation = myRogue->GetActorLocation();

		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Save")));
		if (UGameplayStatics::SaveGameToSlot(PlayerData, SaveSlotName, 0) == false) {
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("SaveError")));
		}*/
	}
}

void ARogueState::Call_RogueStartWeaponNumber() {
	
	//WeaponNumber = StartWeaponNumber;
	//WeaponElementNumber = StartWeaponElementNumber;
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("StartWeapon")));
	if (MyGameMode->NewGameStart == true) {
		int StartingWeapon = FMath::RandRange(0, 2);
		switch (StartingWeapon) {
		case 0:
			WeaponNumber = 1;
			break;
		case 1:
			WeaponNumber = 6;
			break;
		case 2:
			WeaponNumber = 5;
			break;
		}
	}
	MyGameMode->Return_WeaponChangeDelegate.ExecuteIfBound(WeaponNumber);
	MyGameMode->WeaponElementChangeDelegate_.ExecuteIfBound(WeaponElementNumber, ElementLevelValue);
	MyGameMode->Call_RogueHavingWeaponCheckDelegate.ExecuteIfBound(WeaponNumber);

	SaveGameData();

	//MyGameMode->WeaponElementChangeDelegate_.ExecuteIfBound(StartWeaponElementNumber, ElementLevelValue);
	/*WeaponNumber = FMath::FRandRange(0, 9);
	while(WeaponNumber == 0 || WeaponNumber ==9 || WeaponNumber == 7)
		WeaponNumber = FMath::FRandRange(0, 9);
	//WeaponHadCheck(WeaponNumber);*/
	//MyGameMode->Return_GameStartWeaponNumberDelegate.ExecuteIfBound(WeaponNumber);
}

void ARogueState::Call_RogueStartTorchElementalNumber() {
	//TorchElementNumber = StartTorchElementNumber;
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("StartTorch")));
	MyGameMode->TorchElementChangeDelegate_.ExecuteIfBound(TorchElementNumber, ElementLevelValue);
	SaveGameData();
}


void ARogueState::Call_RogueStartAttackFormNumber() {
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("StartAttackForm")));
	AttackFormInit();
	if (MyGameMode->NewGameStart == true) {
		
		AttackFormHadCheck(AttackForm[0], AttackFormIndex[0]);
		AttackFormHadCheck(AttackForm[1], AttackFormIndex[1]);
		AttackFormHadCheck(AttackForm[2], AttackFormIndex[2]);
		//MyGameMode->NewGameStart = false;

	}
	SaveGameData();
	SetAttackAnimation();
	//MyGameMode->Return_GameStartAttackFormNumberDelegate.ExcuteIfBound(AttackForm, AttackFormIndex);
}

void ARogueState::Widget_ViewInit() {
	MyGameMode->Widget_GetRogueHpDelegate.ExecuteIfBound(GetRogueHp());
	MyGameMode->Widget_GetRogueDataDelegate.ExecuteIfBound(CurrentData);
	MyGameMode->Widget_GetRogueKarmaDelegate.ExecuteIfBound(GetCurrentKarma());
	//MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(1);
}

void ARogueState::AttackFormChange(int32 TakeAttackForm, int32 TakeAttackFormIndex, int32 TakeAttackSlot) {
	AttackForm[TakeAttackSlot] = TakeAttackForm;
	AttackFormIndex[TakeAttackSlot] = TakeAttackFormIndex;
	
	SetAttackAnimation();
}

void ARogueState::AttackFormInit() {
	if(MyGameMode->NewGameStart == true && TotalAttackFormCount == 0){
		for (int i = 0; i < 3; i++) {
			if (WeaponNumber == 1) {
				AttackForm[i] = 1;
			}
			else if (WeaponNumber == 5) {
				AttackForm[i] = 0;
			}
			else {
				AttackForm[i] = 0;
			}
			switch (AttackForm[i]) {
			case 0:
				AttackFormIndex[i] = FMath::RandRange(0, 6);
				break;
			case 1:
				AttackFormIndex[i] = FMath::RandRange(0, 7);
				break;
			case 2:
				AttackFormIndex[i] = FMath::RandRange(0, 8);
				break;
			}
		}
	}
}

void ARogueState::SetDamegedRogue(float Dameged) {
	RogueHp -= Dameged;
	if (RogueHp <= 0)
		RogueHp = 0;
	if (RogueHp > FullMaxHp)
		RogueHp = FullMaxHp;
	MyGameMode->Rogue_GetHpDelegate.ExecuteIfBound(GetRogueHp());
	MyGameMode->Widget_GetRogueHpDelegate.ExecuteIfBound(GetRogueHp());
	MyGameMode->MainUIUpdate();
}

void ARogueState::SetRogueDeshData(float UseDataValue, float Data) {
	UseDeshData += UseDataValue;
	if (UseDeshData >= 5.f) {
		if (Data > 0)
			UsedData += Data;
		else
			AllData -= Data;
		CurrentData -= Data;
		if (CurrentData <= 0)
			CurrentData = 0;
		MyGameMode->Widget_GetRogueDataDelegate.ExecuteIfBound(CurrentData);
		if (MyGameMode->MainWidgetState == true)
			MyGameMode->MainUIUpdate();
		UseDeshData = 0.f;
	}

}

void ARogueState::SetStaticRogueData(int32 UseDataValue) {
	if (UseDataValue < 0)
		AllData -= UseDataValue;
	else {
		if (CurrentData < UseDataValue)
			UsedData += CurrentData;
		else
			UsedData += UseDataValue;
	}
	CurrentData -= UseDataValue;
	if (CurrentData <= 0)
		CurrentData = 0;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Current StaticData : %d"), CurrentData));
	MyGameMode->Widget_GetRogueDataDelegate.ExecuteIfBound(CurrentData);
	if(MyGameMode->MainWidgetState == true)
		MyGameMode->MainUIUpdate();
}

void ARogueState::SetDynamicRogueData(int32 UseDataValue) {
	if (UseDataValue < 0)
		AllData -= UseDataValue * UseDataValuePercent;
	else {
		if (CurrentData < UseDataValue * UseDataValuePercent)
			UsedData += CurrentData;
		else
			UsedData += UseDataValue * UseDataValuePercent;
	}
	CurrentData -= UseDataValue * UseDataValuePercent;
	if (CurrentData <= 0)
		CurrentData = 0;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Current DynamicData : %d"), CurrentData));
	MyGameMode->Widget_GetRogueDataDelegate.ExecuteIfBound(CurrentData);
	if (MyGameMode->MainWidgetState == true)
		MyGameMode->MainUIUpdate();

}

void ARogueState::SetCurrentKarma(int32 newKarma) { 
	CurrentKarma = newKarma; 
	MyGameMode->Widget_GetRogueKarmaDelegate.ExecuteIfBound(CurrentKarma);
	MyGameMode->MainUIUpdate();
}

void ARogueState::SetPlusCurrentKarma(int32 newKarma) { 
	CurrentKarma += newKarma; 
	MyGameMode->Widget_GetRogueKarmaDelegate.ExecuteIfBound(CurrentKarma);
	MyGameMode->MainUIUpdate();
}

void ARogueState::DataInit() {
	CurrentData = 300;
	AllData = 300;
}
void ARogueState::KarmaInit() {
	CurrentKarma = 100;
}
void ARogueState::CurrentHpInit() {
	SetRogueHp(FullMaxHp);
}
void ARogueState::RogueKillInit() {
	setRogueKill(0);
}

void ARogueState::TorchElementInit() {
	for (int i = 0; i < 5; i++) {
		HadTorchElement[i] = false;
		SelectedElementBonus[i] = 1.f;
	}
}
void ARogueState::WeaponElementInit() {
	for (int i = 0; i < 5; i++)
		HadWeaponElement[i] = false;
}

void ARogueState::getWorldGameModeBase() {
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
}

void ARogueState::RogueDataAndKarmaDelegateInit() {
	MyGameMode->RogueSetDataDelegate.BindUObject(this, &ARogueState::SetDynamicRogueData);
	MyGameMode->Call_SetStaticDataChangeDelegate.BindUObject(this, &ARogueState::SetStaticRogueData);
	MyGameMode->RogueSetKarmaDelegate.BindUObject(this, &ARogueState::SetPlusCurrentKarma);
}

void ARogueState::TorchElementDelegateInit() {
	MyGameMode->TorchElementChangeDelegate.BindUObject(this, &ARogueState::SetTorchElementOne);
	MyGameMode->TorchStatusSynergyDelegate.BindUObject(this, &ARogueState::GetTorchStatusSynergy);
}

void ARogueState::WeaponElementDelegateInit() {
	MyGameMode->WeaponElementChangeDelegate.BindUObject(this, &ARogueState::SetWeaponElementOne);
	MyGameMode->WeaponElementSynergyDelegate.BindUObject(this, &ARogueState::GetWeaponElementSynergy);
}

void ARogueState::WeaponChangeDelegateInit() {
	MyGameMode->Call_WeaponChangeDelegate.BindUObject(this, &ARogueState::SetSelectWeapon);
	MyGameMode->WeaponSynergyDelegate.BindUObject(this, &ARogueState::GetWeaponSynergy);
}

void ARogueState::DamegeDelegateInit() {
	MyGameMode->WeaponTotalDamegeSettingDelegate.BindUObject(this, &ARogueState::LastWeaponDamegeSetting);
	MyGameMode->TorchTotalDamgeSettingDelegate.BindUObject(this, &ARogueState::GetTorchDemege);
}

void ARogueState::AttackAnimationDelegateInit() {
	MyGameMode->AttackAnimationChangeDelegate.BindUObject(this, &ARogueState::SetAttackAnimation);
	MyGameMode->AttackFormSynergyDelegate.BindUObject(this, &ARogueState::GetAttackFormSynergy);
}

void ARogueState::RogueAttackPlusIncreaseDelegateInit() {
	MyGameMode->WeaponAttackToEffectPercentIncreaseDelegate_.BindUObject(this, &ARogueState::AttackSuccessToSpecialperPlus);
}

void ARogueState::GetTorchStatusSynergy(float ElementStabDefaultDamege, float ElementBurnAttacksDefaultDamege, float ElementSpecialDefaultDamege,
	float ElementCriper) {
	TorchStabDefaultDamege = ElementStabDefaultDamege;
	TorchBurnAttacksDefaultDamege = ElementBurnAttacksDefaultDamege;
	TorchElementSpecialDefaultDamege = ElementSpecialDefaultDamege;
	TorchElementCriper = ElementCriper;
}

void ARogueState::GetTorchDemege() {
	TorchStabTotalDamege = TorchStabDefaultDamege * TorchLevelValue  * ElementLevelValue * SelectedElementBonus[TorchElementNumber];
	
	TorchBurnAttacksTotalDamege = TorchBurnAttacksDefaultDamege * ElementLevelValue * SelectedElementBonus[TorchElementNumber] *
		TorchBurnAttackSynergy * TorchBurnAttackSynergyValue;
	
	TorchSpecialTotalDamege = TorchElementSpecialDefaultDamege * SelectedElementBonus[TorchElementNumber] * ElementLevelValue *
		TorchElementSpecialSynergy * TorchSpecialTotalDamegeValue;
	
	MyGameMode->TorchTotalDamegeDelegate.ExecuteIfBound(TorchStabTotalDamege, TorchBurnAttacksTotalDamege, TorchSpecialTotalDamege, TorchElementCriper);
}

void ARogueState::SetTorchElementOne(int32 SelectElementNumber, bool Take) {
	
	HadTorchElement[SelectElementNumber] = Take;
	TorchElementNumber = SelectElementNumber;
	MyGameMode->TorchElementChangeDelegate_.ExecuteIfBound(SelectElementNumber, ElementLevelValue); //현재는 키보드 입력으로
}

void ARogueState::SetWeaponElementOne(int32 SelectElementNumber, bool Take) {
	
	HadWeaponElement[SelectElementNumber] = Take;
	WeaponElementNumber = SelectElementNumber;
	MyGameMode->WeaponElementChangeDelegate_.ExecuteIfBound(SelectElementNumber, ElementLevelValue); //현재는 키보드입력으로
}

void ARogueState::GetWeaponElementSynergy(float ElementSynergy, float ElementDefaultDamege, float ElementValue) {
	WeaponElementSynergy = ElementSynergy;
	WeaponElementDefaultDamge = ElementDefaultDamege;
	WeaponElementValue = ElementValue;
}

void ARogueState::SetSelectWeapon(int32 SelectWeaponNumber) {
	WeaponNumber = SelectWeaponNumber;
	
	MyGameMode->Return_WeaponChangeDelegate.ExecuteIfBound(WeaponNumber);
}

void ARogueState::GetWeaponSynergy(int32 WeaponNumbers, float Slash, float Break, float Stab, float WeaponDefaultDameges, float WeaponSpeeds) {
	SlashSynergy = Slash;
	BreakSynergy = Break;
	StabSynergy = Stab;
	WeaponDefaultDamege = WeaponDefaultDameges;
	WeaponSpeed = WeaponSpeeds;
	WeaponNumber = WeaponNumbers;
	MyGameMode->WeaponSpeedSynergyDelegate.ExecuteIfBound(WeaponSpeed, WeaponSpeedValueBonus, WeaponLevelValue); //간이용 나중에 LastAttackSpeed로 마무리 할 것.
}

void ARogueState::SetAttackAnimation() {
	for (int i = 0; i < 3; i++) {
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Green, FString::Printf(TEXT("AttackForm %d // Index %d\n"), AttackForm[i], AttackFormIndex[i]));
	}
	MyGameMode->AttackAnimationChangeDelegate_.ExecuteIfBound(AttackForm[0], AttackFormIndex[0], AttackForm[1], AttackFormIndex[1], AttackForm[2], AttackFormIndex[2]);
	LastSpeedSetting();
}

void ARogueState::GetAttackFormSynergy(float* AttackFormSynergys, bool* CheckDoubleAttack, int32 CheckAttackDirection[3][2]) {
	for (int i = 0; i < 3; i++) {
		DoubleAttackCheck[i] = CheckDoubleAttack[i];
		AttackDirectionCheck[i][0] = CheckAttackDirection[i][0];
		AttackDirectionCheck[i][1] = CheckAttackDirection[i][1];
		for (int j = 0; j < 3; j++) {
			AttackFormSynergy[i][j] = *AttackFormSynergys++;
			
		}
	}
	LastWeaponDamegeSetting();
}

void ARogueState::GetWeaponPhysicsDamege() {
	for (int i = 0; i < 3; i++) {
		WeaponPhysicsDamege[i] =
			WeaponDefaultDamege*WeaponLevelValue*
			(SlashSynergy* SlashValueBonus * AttackFormSynergy[i][0] + 
				BreakSynergy * BreakValueBonus * AttackFormSynergy[i][1] + 
				StabSynergy * StabValueBonus * AttackFormSynergy[i][2])* (1 + HadAttackFormOverlap[AttackForm[i]][AttackFormIndex[i]] / 10) * (1 + HadWeaponOverlap[WeaponNumber] / 10);
	}
	AvgWeaponDamege = (WeaponPhysicsDamege[0] + WeaponPhysicsDamege[1] + WeaponPhysicsDamege[2]) / 3;
}

void ARogueState::GetWeaponElementDamege() {
	WeaponElementDamege = WeaponElementSynergy * WeaponElementDefaultDamge * SelectedElementBonus[WeaponElementNumber] * ElementLevelValue
		* (1 + HadElementalOverlap[WeaponElementNumber] / 10);
	WeaponElementDamege *= WeaponElementDamegeBonus;
}

void ARogueState::GetWeaponTotalDamege() {
	GetWeaponPhysicsDamege();
	GetWeaponElementDamege();

	for (int i = 0; i < 3; i++)
		WeaponTotalDamege[i] = (WeaponPhysicsDamege[i] + WeaponElementDamege);
}

void ARogueState::SetTorchLevelUp() {
	TorchLevelExMax += (5 * 1.2 * TorchLevel);
	TorchLevel += 1;
	TorchLevelValue = 1.f + TorchLevel * 0.05;
	//MyGameMode->RogueTorchLevelUpDelegate.ExecuteIfBound();
	MyGameMode->TorchSpeedSynergyDelegate.ExecuteIfBound(TorchLevelValue);
	LastTorchDamegeSetting();
	SetStaticRogueData(100 * TorchLevel * TorchLevelValue);
}

void ARogueState::SetWeaponLevelUp() {
	WeaponLevelExMax += (5 * 1.2 * WeaponLevel);
	WeaponLevel += 1;
	WeaponLevelValue = 1.0f + WeaponLevel * 0.05; 
	MyGameMode->WeaponSpeedSynergyDelegate.ExecuteIfBound(WeaponSpeed, WeaponSpeedValueBonus, WeaponLevelValue);
	//GetWeaponSynergy(WeaponNumber, SlashSynergy, BreakSynergy, StabSynergy, WeaponDefaultDamege, WeaponSpeed);
	LastWeaponDamegeSetting();
	SetStaticRogueData(100 * WeaponLevel * WeaponLevelValue);
}

void ARogueState::SetElementLevelUp() {
	ElementLevelExMax += (5 * 1.2 * ElementLevel);
	ElementLevel++;
	ElementLevelValue = 1.f + ElementLevel * 0.05;
	MyGameMode->RogueElementLevelToWeaponDelegate.ExecuteIfBound(ElementLevel, ElementLevelValue);
	MyGameMode->RogueElementLevelToTorchDelegate.ExecuteIfBound(ElementLevel, ElementLevelValue);
	LastWeaponDamegeSetting();
	LastTorchDamegeSetting();
	SetStaticRogueData(100 * ElementLevel * ElementLevelValue);
}

void ARogueState::GetMoveSpeed(float MoveSpeed) {
	RogueMoveSpeed = MoveSpeed;
}

void ARogueState::SetEquipmentStrings() {
	switch (WeaponNumber){
	case 0:
		WeaponName = TEXT("Dagger");
		break;
	case 1:
		WeaponName = TEXT("Mace");
		break;
	case 2:
		WeaponName = TEXT("GreatAxe");
		break;
	case 3:
		WeaponName = TEXT("GreatHammer");
		break;
	case 4:
		WeaponName = TEXT("LongSword");
		break;
	case 5:
		WeaponName = TEXT("ShortSword");
		break;
	case 6:
		WeaponName = TEXT("Axe");
		break;
	case 7:
		WeaponName = TEXT("Spear");
		break;
	case 8:
		WeaponName = TEXT("Scythe");
		break;
	case 9:
		WeaponName = TEXT("Knife");
		break;
	}
	
	if (WeaponElementNumber == 0) {
		if(ElementLevel > 10 && WeaponLevel > 10)
			WeaponElementName = TEXT("Smite");
		else if(ElementLevel > 5 && WeaponLevel > 5)
			WeaponElementName = TEXT("Strenght");
		else if (ElementLevel <= 5 || WeaponLevel <= 5)
			WeaponElementName = TEXT("Physical");
	}
	if (WeaponElementNumber == 1) {
		if (ElementLevel > 10 && WeaponLevel > 10)
			WeaponElementName = TEXT("Flame");
		else if (ElementLevel > 5 && WeaponLevel > 5)
			WeaponElementName = TEXT("Fire");
		else if (ElementLevel <= 5 || WeaponLevel <= 5)
			WeaponElementName = TEXT("Heat");
	}
	if (WeaponElementNumber == 2) {
		if (ElementLevel > 10 && WeaponLevel > 10)
			WeaponElementName = TEXT("Freez");
		else if (ElementLevel > 5 && WeaponLevel > 5)
			WeaponElementName = TEXT("Frost");
		else if (ElementLevel <= 5 || WeaponLevel <= 5)
			WeaponElementName = TEXT("Chill");
	}
	if (WeaponElementNumber == 3) {
		if (ElementLevel > 10 && WeaponLevel > 10)
			WeaponElementName = TEXT("Venom");
		else if (ElementLevel > 5 && WeaponLevel > 5)
			WeaponElementName = TEXT("Poison");
		else if (ElementLevel <= 5 || WeaponLevel <= 5)
			WeaponElementName = TEXT("Toxin");
	}
	if (WeaponElementNumber == 4) {
		if (ElementLevel > 10 && WeaponLevel > 10)
			WeaponElementName = TEXT("Thunderbolt");
		else if (ElementLevel > 5 && WeaponLevel > 5)
			WeaponElementName = TEXT("Lightning");
		else if (ElementLevel <= 5 || WeaponLevel <= 5)
			WeaponElementName = TEXT("Electric");
	}
	
	
	if (TorchElementNumber == 0) {
		if (ElementLevel > 10 && TorchLevel > 10)
			TorchElementName = TEXT("Smite");
		else if (ElementLevel > 5 && TorchLevel > 5)
			TorchElementName = TEXT("Strenght");
		else if (ElementLevel <= 5 || TorchLevel <= 5)
			TorchElementName = TEXT("Physical");
	}
	if (TorchElementNumber == 1) {
		if (ElementLevel > 10 && TorchLevel > 10)
			TorchElementName = TEXT("Flame");
		else if (ElementLevel > 5 && TorchLevel > 5)
			TorchElementName = TEXT("Fire");
		else if (ElementLevel <= 5 || TorchLevel <= 5)
			TorchElementName = TEXT("Heat");
	}
	if (TorchElementNumber == 2) {
		if (ElementLevel > 10 && TorchLevel > 10)
			TorchElementName = TEXT("Freeze");
		else if (ElementLevel > 5 && TorchLevel > 5)
			TorchElementName = TEXT("Frost");
		else if (ElementLevel <= 5 || TorchLevel <= 5)
			TorchElementName = TEXT("Chill");
	}
	if (TorchElementNumber == 3) {
		if (ElementLevel > 10 && TorchLevel > 10)
			TorchElementName = TEXT("Venom");
		else if (ElementLevel > 5 && TorchLevel > 5)
			TorchElementName = TEXT("Poison");
		else if (ElementLevel <= 5 || TorchLevel <= 5)
			TorchElementName = TEXT("Toxin");
	}
	if (TorchElementNumber == 4) {
		if (ElementLevel > 10 && TorchLevel > 10)
			TorchElementName = TEXT("Thunderbolt");
		else if (ElementLevel > 5 && TorchLevel > 5)
			TorchElementName = TEXT("Lightning");
		else if (ElementLevel <= 5 || TorchLevel <= 5)
			TorchElementName = TEXT("Electric");
	}
	
	AttackFormName[0][0] = TEXT("Slash");
	AttackFormName[0][1] = TEXT("Reverse Slash");
	AttackFormName[0][2] = TEXT("Bash Slash");
	AttackFormName[0][3] = TEXT("Upper Slash");
	AttackFormName[0][4] = TEXT("X Slash");
	AttackFormName[0][5] = TEXT("DownUpper Combo");
	AttackFormName[0][6] = TEXT("White Fang");

	AttackFormName[1][0] = TEXT("Smash");
	AttackFormName[1][1] = TEXT("Breaker");
	AttackFormName[1][2] = TEXT("Side Smash");
	AttackFormName[1][3] = TEXT("Side Breaker");
	//AttackFormName[1][4] = TEXT("ShortPick");
	AttackFormName[1][4] = TEXT("Ground Breaker");
	AttackFormName[1][5] = TEXT("ReverseSide Smash");
	AttackFormName[1][6] = TEXT("HeadDancer");
	AttackFormName[1][7] = TEXT("Cranker");

	AttackFormName[2][0] = TEXT("Stab");
	AttackFormName[2][1] = TEXT("Quick Stab");
	AttackFormName[2][2] = TEXT("Deep Stab");
	AttackFormName[2][3] = TEXT("Side Stab");
	AttackFormName[2][4] = TEXT("Upper Stab");
	AttackFormName[2][5] = TEXT("OneInch Stab");
	AttackFormName[2][6] = TEXT("Double Stab");
	AttackFormName[2][7] = TEXT("Double Faces");
	AttackFormName[2][8] = TEXT("Double Holes");
	AttackFormName[2][9] = TEXT("Double Lanes");

	AttackFormName[3][0] = TEXT("AirTrack");
	AttackFormName[3][1] = TEXT("DeleteLeg");
	AttackFormName[3][2] = TEXT("TurnEnd");

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
	RogueAttackFormVideoString[1][4] = TEXT("FileMediaSource'/Game/AttackImage/Smash/ShortPick.ShortPick'");
	RogueAttackFormVideoString[1][5] = TEXT("FileMediaSource'/Game/AttackImage/Smash/GroundBreak.GroundBreak'");
	RogueAttackFormVideoString[1][6] = TEXT("FileMediaSource'/Game/AttackImage/Smash/ReverseSideSmash.ReverseSideSmash'");
	RogueAttackFormVideoString[1][7] = TEXT("FileMediaSource'/Game/AttackImage/Smash/HeadDancer.HeadDancer'");
	RogueAttackFormVideoString[1][8] = TEXT("FileMediaSource'/Game/AttackImage/Smash/Cranker.Cranker'");

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

	RogueAttackFormVideoString[3][0] = TEXT("");
	RogueAttackFormVideoString[3][1] = TEXT("");
	RogueAttackFormVideoString[3][2] = TEXT("");

	
	EquipData[0] = WeaponName;
	EquipData[1] = WeaponElementName;
	EquipData[2] = TorchElementName;
	EquipData[3] = AttackFormName[AttackForm[0]][AttackFormIndex[0]];
	EquipData[4] = AttackFormName[AttackForm[1]][AttackFormIndex[1]];
	EquipData[5] = AttackFormName[AttackForm[2]][AttackFormIndex[2]];
	EquipNumberData[0] = WeaponNumber;
	EquipNumberData[1] = WeaponElementNumber;
	EquipNumberData[2] = TorchElementNumber;
	EquipAttackFormVideoData[0] = RogueAttackFormVideoString[AttackForm[0]][AttackFormIndex[0]];
	EquipAttackFormVideoData[1] = RogueAttackFormVideoString[AttackForm[1]][AttackFormIndex[1]];
	EquipAttackFormVideoData[2] = RogueAttackFormVideoString[AttackForm[2]][AttackFormIndex[2]];
	OverlapData[0] = HadWeaponOverlap[WeaponNumber];
	OverlapData[1] = HadElementalOverlap[WeaponElementNumber];
	OverlapData[2] = HadElementalOverlap[TorchElementNumber+5];
	OverlapData[3] = HadAttackFormOverlap[AttackForm[0]][AttackFormIndex[0]];
	OverlapData[4] = HadAttackFormOverlap[AttackForm[1]][AttackFormIndex[1]];
	OverlapData[5] = HadAttackFormOverlap[AttackForm[2]][AttackFormIndex[2]];
	TotalOverlapData[0] = HadWeaponOverlap;
	TotalOverlapData[1] = HadElementalOverlap;
	TotalOverlapData[2] = HadAttackFormOverlap[0];
	TotalOverlapData[3] = HadAttackFormOverlap[1];
	TotalOverlapData[4] = HadAttackFormOverlap[2];
	TotalOverlapData[5] = HadAttackFormOverlap[3];
	MyGameMode->Widget_GetRogueEquipmentDelegate.ExecuteIfBound(EquipData, EquipAttackFormVideoData,
		EquipAttackFormRefData, AttackForm, AttackFormIndex, EquipNumberData, OverlapData, TotalOverlapData);
}

void ARogueState::SetEquipmentAttackFormString(TCHAR** AttackFormString) {
	EquipAttackFormRefData[0] = AttackFormString[0];
	EquipAttackFormRefData[1] = AttackFormString[1];
	EquipAttackFormRefData[2] = AttackFormString[2];
}


void ARogueState::SetGameState() {
	GameStateData[0] = GetRogueTotalKill();
	GameStateData[1] = GetRogueDeath();
	GameStateData[2] = GetRogueAllData();
	GameStateData[3] = GetRogueUsedData();
	GameStateData[4] = GetDungeonClearAllCount();
	MyGameMode->Widget_ReturnGameStateWidgetDelegate.ExecuteIfBound(GameStateData);
}

void ARogueState::SetStatData() {
	StatData[0] = GetRogueFullHp();
	StatData[1] = GetRogueData();
	StatData[2] = GetRogueKill();
	StatData[3] = RogueMoveSpeed;
	
	StatData[4] = SuperArmorCount * 10.f;
	StatData[5] = WeaponSpeed * WeaponLevelValue * WeaponSpeedValueBonus;
	StatData[6] = WeaponLevel;
	StatData[7] = TorchLevel;
	StatData[8] = ElementLevel;
	StatData[9] = LastAvgWeaponDamege;
	StatData[10] = LastAvgWeaponEDamge;
	StatData[11] = WeaponElementValue * WeaponElementValueBonus;
	
	StatData[12] = TorchStabTotalDamege;
	StatData[13] = TorchBurnAttacksTotalDamege;
	StatData[14] = TorchSpecialTotalDamege;
	StatData[15] = TorchElementCriper* TorchElementCriperValue;
	MyGameMode->Widget_StatDataDelegate.ExecuteIfBound(StatData);
}

//전투지속과 관련된 효과들은 전부 2차구현으로 넘기자.

void ARogueState::SlashSynergyIncrease() {
	SlashSynergyIncreaseCount++;
	SlashValueBonus *= 1.2;
	GetWeaponPhysicsDamege();
}

void ARogueState::DeleteSlashSynergyIncrease() {
	SlashSynergyIncreaseCount = 0;
	SlashValueBonus = 1.f;
	GetWeaponPhysicsDamege();
}

void ARogueState::BreakSynergyIncrease() {
	BreakSynergyIncreaseCount++;
	BreakValueBonus *= 1.2;
	GetWeaponPhysicsDamege();
}

void ARogueState::DeleteBreakSynergyIncrease() {
	BreakSynergyIncreaseCount = 0;
	BreakValueBonus = 1.f;
	GetWeaponPhysicsDamege();
}

void ARogueState::StabSynergyIncrease() {
	StabSynergyIncreaseCount++;
	StabValueBonus *= 1.2;
	GetWeaponPhysicsDamege();
}

void ARogueState::DeleteStabSynergyIncrease() {
	StabSynergyIncreaseCount = 0;
	StabValueBonus = 1.f;
	GetWeaponPhysicsDamege();
}

void ARogueState::BurnAttacksDamegeIncrease() {
	BurnAttacksDamegeIncreaseCount++;
	TorchBurnAttackSynergyValue *= 1.2;
	GetTorchDemege();
}

void ARogueState::DeleteBurnAttacksDamegeIncrease() {
	BurnAttacksDamegeIncreaseCount = 0;
	TorchBurnAttackSynergyValue = 1.f;
	GetTorchDemege();
}

void ARogueState::CertainIncrease(int32 ElementNumber) {
	CertainIncreaseCount++;
	SelectedElementBonus[ElementNumber] *= 1.2;
	GetTorchDemege();
	GetWeaponElementDamege();
}

void ARogueState::DeleteCertainIncrease(int32 SelectElment) {
	//int32 SelectElment = FMath::FRandRange(0, 4);
	CertainIncreaseCount = 0;
	SelectedElementBonus[SelectElment] = 1.f;
	GetTorchDemege();
	GetWeaponElementDamege();
}

void ARogueState::BurnAttacksHitIncrease() {
	BurnAttacksHitIncreaseCount++;
	MyGameMode->TorchBurnAttacksHitValueDelegate.ExecuteIfBound(BurnAttacksHitIncreaseCount);
}

void ARogueState::DeleteBurnAttacksHitIncrease() {
	BurnAttacksHitIncreaseCount = 0;
	MyGameMode->TorchBurnAttacksHitValueDelegate.ExecuteIfBound(BurnAttacksHitIncreaseCount);
}

void ARogueState::MoveSpeedIncrease() {
	MoveSpeedIncreaseCount++;
	MoveSpeedIncreaseCountValue *= 1.05;
	MyGameMode->RogueSpeedIncreaseDelegate.ExecuteIfBound(0.1 * MoveSpeedIncreaseCountValue);
}

void ARogueState::DeleteMoveSpeedIncrease() {
	MoveSpeedIncreaseCount = 0;
	MoveSpeedIncreaseCountValue = 1.f;
	MyGameMode->RogueSpeedIncreaseDelegate.ExecuteIfBound(0.1 * MoveSpeedIncreaseCountValue);
}

void ARogueState::HitToKnockBack() {
	HitToKnockBackCount = 1;
	MyGameMode->WeaponHitKnockBackDelegate.ExecuteIfBound(HitToKnockBackCount);
}

void ARogueState::DeleteHitToKnockBack() {
	HitToKnockBackCount = 0;
	MyGameMode->WeaponHitKnockBackDelegate.ExecuteIfBound(HitToKnockBackCount);
}

void ARogueState::SuperArmor() {
	SuperArmorCount++;
	MyGameMode->RogueSuperArmorDelegate.ExecuteIfBound(10.f);
}

void ARogueState::DeleteSuperArmor() {

	MyGameMode->RogueSuperArmorDelegate.ExecuteIfBound(-10.f*SuperArmorCount);
	SuperArmorCount = 0;
}

void ARogueState::AttackSuccessToSpecialperPlus() {
	AttackSuccessToSpecialPerPlusCount++;
	MyGameMode->WeaponAttackToEffectPercentIncreaseDelegate.ExecuteIfBound(AttackSuccessToSpecialPerPlusCount);
	//피격당했을때는 2차구현때 하자. // 완성
}

void ARogueState::DeleteAttackSuccessToSpecialperPlus() {
	AttackSuccessToSpecialPerPlusCount = 0;
	MyGameMode->WeaponAttackToEffectPercentIncreaseDelegate.ExecuteIfBound(AttackSuccessToSpecialPerPlusCount);
	//피격당했을때는 2차구현때 하자.
}

void ARogueState::AttackTryToLowDataDecrease() {
	AttackTryToLowDataDecreaseCount++;
	UseDataValuePercent *= 1.1;
}

void ARogueState::DeleteAttackTryToLowDataDecrease() {
	AttackTryToLowDataDecreaseCount = 0;
	UseDataValuePercent = 1.f;
}

void ARogueState::TorchSpecialPerIncrease() {
	TorchSpecialPerIncreaseCount++;
	TorchElementCriperValue *= 1.2;
	//MyGameMode->TorchBurnAttacksSpecialPercentIncreaseDelegate.ExecuteIfBound(1.2);
}

void ARogueState::DeleteTorchSpecialPerIncrease() {
	TorchSpecialPerIncreaseCount = 0;
	TorchElementCriperValue = 1.f;
	//MyGameMode->TorchBurnAttacksSpecialPercentIncreaseDelegate.ExecuteIfBound(1.2);
}

void ARogueState::WeaponSpecialPerIncrease() {
	WeaponSpecialPerIncreaseCount++;
	WeaponElementValueBonus *= 1.1;
		//MyGameMode->WeaponSpecialPercentIncreaseDelegate.ExecuteIfBound(1.1);
}

void ARogueState::DeleteWeaponSpecialPerIncrease() {
	WeaponSpecialPerIncreaseCount = 0;
	WeaponElementValueBonus = 1.f;
	//MyGameMode->WeaponSpecialPercentIncreaseDelegate.ExecuteIfBound(1.1);
}

void ARogueState::TorchSpecialDamegeIncrease() {
	TorchSpecialDamegeIncreaseCount++;
	TorchSpecialTotalDamegeValue *= 1.1;
		//MyGameMode->TorchBurnAttacksSpecialDamegeIncreaseDelegate.ExecuteIfBound(1.1);
}

void ARogueState::DeleteTorchSpecialDamegeIncrease() {
	TorchSpecialDamegeIncreaseCount = 0;
	TorchSpecialTotalDamegeValue = 1.f;
	//MyGameMode->TorchBurnAttacksSpecialDamegeIncreaseDelegate.ExecuteIfBound(1.1);
}

void ARogueState::WeaponSpecialDamegeIncrease() {
	WeaponSpecialDamegeIncreaseCount++;
	WeaponElementDamegeBonus *= 1.1;
		//->WeaponSpecialDamegeIncreaseDelegate.ExecuteIfBound(1.1);
}

void ARogueState::DeleteWeaponSpecialDamegeIncrease() {
	WeaponSpecialDamegeIncreaseCount = 0;
	WeaponElementDamegeBonus = 1.f;
	//->WeaponSpecialDamegeIncreaseDelegate.ExecuteIfBound(1.1);
}

void ARogueState::AttackFormSpeedIncrease() {
	AttackFormSpeedIncreaseCount++;
	WeaponSpeedValueBonus *= 1.05;
}

void ARogueState::DeleteAttackFormSpeedIncrease() {
	AttackFormSpeedIncreaseCount = 0;
	WeaponSpeedValueBonus = 1.f;
}

void ARogueState::LowHpToHighAttackSynergy() {
	LowHpToHighAttackSynergyCount = 1;
}

void ARogueState::DeleteLowHpToHighAttackSynergy() {
	LowHpToHighAttackSynergyCount = 0;
}

void ARogueState::FullHpToHighAttackSynergy() {
	FullHpToHighAttackSynergyCount = 1;
}

void ARogueState::DeleteFullHpToHighAttackSynergy() {
	FullHpToHighAttackSynergyCount = 0;
}


void ARogueState::NoHitToHighAttackSynergy() {
	//2차 설계때
	NoHitToHighAttackSynergyCount++;
	MyGameMode->WeaponAttackToDmgIncreaseDelegate.ExecuteIfBound(NoHitToHighAttackSynergyCount);
}

void ARogueState::DeleteNoHitToHighAttackSynergy() {
	//2차 설계때
	NoHitToHighAttackSynergyCount = 0;
	MyGameMode->WeaponAttackToDmgIncreaseDelegate.ExecuteIfBound(NoHitToHighAttackSynergyCount);
}

void ARogueState::HpIncrease() {
	//float FullHp = 300.f;
	HpIncreaseCount++;
	FullMaxHp *= 1.1;
	SetFullMaxRogueHp(FullMaxHp);
}

void ARogueState::DeleteHpIncrease() {
	//float FullHp = 300.f;
	HpIncreaseCount = 0;
	FullMaxHp = 300;
	SetFullMaxRogueHp(FullMaxHp);
}

void ARogueState::DeleteAbility() {
	DeleteSlashSynergyIncrease();
	DeleteBreakSynergyIncrease();
	DeleteStabSynergyIncrease();
	DeleteBurnAttacksDamegeIncrease();
	DeleteCertainIncrease(0);
	DeleteCertainIncrease(1);
	DeleteCertainIncrease(2);
	DeleteCertainIncrease(3);
	DeleteCertainIncrease(4);
	DeleteBurnAttacksHitIncrease();
	DeleteMoveSpeedIncrease();
	DeleteHitToKnockBack();
	DeleteSuperArmor();
	DeleteAttackSuccessToSpecialperPlus();
	DeleteAttackTryToLowDataDecrease();
	DeleteTorchSpecialPerIncrease();
	DeleteWeaponSpecialPerIncrease();
	DeleteTorchSpecialDamegeIncrease();
	DeleteWeaponSpecialDamegeIncrease();
	DeleteAttackFormSpeedIncrease();
	DeleteLowHpToHighAttackSynergy();
	DeleteFullHpToHighAttackSynergy();
	DeleteNoHitToHighAttackSynergy();
	DeleteHpIncrease();
	DataInit();
	FullMaxHp = 300;
	//KarmaInit();
	TotalEquipCount = 0;
	TotalAbilityCount = 0;
	TotalWeaponCount = 0;
	TotalElementCount = 0;
	TotalAttackFormCount = 0;
	TotalEquipAbilityDataList.Empty();
	TotalWeaponDataList.Empty();
	TotalElementDataList.Empty();;
	TotalAttackFormDataList1.Empty();
	TotalAttackFormDataList2.Empty();
	EquipAbilityCount = 0;
	WeaponNumber = 1;
	WeaponElementNumber = 0;
	TorchElementNumber = 0;
	RogueKill = 0;
	LastWeaponDamegeSetting();
	LastTorchDamegeSetting();
	LastSpeedSetting();
	MyGameMode->StageIndex = 0;
	MyGameMode->StageSubIndex = 0;
	SaveGameData();
}
//------------------------------------------------------------------------------------------------------------------
void ARogueState::AbilityRandTake(int32 AbilityIndex) {
	if (EquipAbilityCount <= 100) {
		AbilityQue[EquipAbilityCount] = AbilityIndex;
		TotalEquipAbilityDataList.Add(AbilityIndex);
		TotalAbilityCount++;
		switch (AbilityQue[EquipAbilityCount]) {
		case 0:
			SlashSynergyIncrease();
			AbilityName[EquipAbilityCount] = TEXT("SlashDamegeUp");
			break;
		case 1:
			BreakSynergyIncrease();
			AbilityName[EquipAbilityCount] = TEXT("SmashDamegeUp");
			break;
		case 2:
			StabSynergyIncrease();
			AbilityName[EquipAbilityCount] = TEXT("StabDamegeUp");
			break;
		case 3:
			BurnAttacksDamegeIncrease();
			AbilityName[EquipAbilityCount] = TEXT("BurnAttack DamegeUp");
			break;
		case 4:
			CertainIncrease(0);
			AbilityName[EquipAbilityCount] = TEXT("PhysicsDamegeUp");
			break;
		case 5:
			CertainIncrease(1);
			AbilityName[EquipAbilityCount] = TEXT("FireDamegeUp");
			break;
		case 6:
			CertainIncrease(2);
			AbilityName[EquipAbilityCount] = TEXT("IceDamegeUp");
			break;
		case 7:
			CertainIncrease(3);
			AbilityName[EquipAbilityCount] = TEXT("IceDamegeUp");
			break;
		case 8:
			CertainIncrease(4);
			AbilityName[EquipAbilityCount] = TEXT("LightningDamegeUp");
			break;
		case 9:
			BurnAttacksHitIncrease();
			AbilityName[EquipAbilityCount] = TEXT("BurnAttack HitUp");
			break;
		case 10:
			MoveSpeedIncrease();
			AbilityName[EquipAbilityCount] = TEXT("MoveSpeedUp");
			break;
		case 11:
			HitToKnockBack();
			AbilityName[EquipAbilityCount] = TEXT("HitKnock-Back");
			break;
		case 12:
			SuperArmor();
			AbilityName[EquipAbilityCount] = TEXT("SuperArmorUp");
			break;
		case 13:
			AttackSuccessToSpecialperPlus();
			AbilityName[EquipAbilityCount] = TEXT("Critical Absorbed");
			break;
		case 14:
			AttackTryToLowDataDecrease();
			AbilityName[EquipAbilityCount] = TEXT("Increase AttackIncome");
			break;
		case 15:
			TorchSpecialPerIncrease();
			AbilityName[EquipAbilityCount] = TEXT("TorchEffectPercent Up");
			break;
		case 16:
			WeaponSpecialPerIncrease();
			AbilityName[EquipAbilityCount] = TEXT("WeaponEffectPercent Up");
			break;
		case 17:
			TorchSpecialDamegeIncrease();
			AbilityName[EquipAbilityCount] = TEXT("TorchEffect DamegeUp");
			break;
		case 18:
			WeaponSpecialDamegeIncrease();
			AbilityName[EquipAbilityCount] = TEXT("WeaponEffect DamegeUp");
			break;
		case 19:
			AttackFormSpeedIncrease();
			AbilityName[EquipAbilityCount] = TEXT("AttackSpeedUp");
			break;
		case 20:
			LowHpToHighAttackSynergy();
			AbilityName[EquipAbilityCount] = TEXT("Heroics Power");
			break;
		case 21:
			FullHpToHighAttackSynergy();
			AbilityName[EquipAbilityCount] = TEXT("Arrogant Power");
			break;
		case 22:
			NoHitToHighAttackSynergy();
			AbilityName[EquipAbilityCount] = TEXT("Berserk Fury");
			break;
		case 23:
			HpIncrease();
			AbilityName[EquipAbilityCount] = TEXT("HpUp");
			break;
		case 24:
			break;
		}
		LastWeaponDamegeSetting();
		LastTorchDamegeSetting();
		LastSpeedSetting();
		//AbilityHadCheck(AbilityIndex);
		//MyGameMode->Widget_AbilityListDelegate.ExecuteIfBound(EquipAbilityCount, AbilityName);
		for (int i = 0; i < EquipAbilityCount; i++) {
			if (AbilityQue[i] == AbilityIndex) {
				HadAbilityOverlap[AbilityIndex]++;
				AbilityOverlapString[i] = FString::Printf(TEXT(" x%.f"), HadAbilityOverlap[AbilityIndex]);
				AbilityTotalName[i] = AbilityName[i] + AbilityOverlapString[i];
				EquipAbilityOverlap = true;
			}
		}
		if (EquipAbilityOverlap == false) {
			AbilityOverlapString[EquipAbilityCount] = FString::Printf(TEXT(" x%.f"), HadAbilityOverlap[AbilityIndex]);
			AbilityTotalName[EquipAbilityCount] = AbilityName[EquipAbilityCount] + AbilityOverlapString[EquipAbilityCount];
			EquipAbilityCount++;
		}
		EquipAbilityOverlap = false;
		if(SaveState == true)
			SaveGameData();
	}
}

void ARogueState::WeaponHadCheck(int32 WeaponNumbers) {
	TotalWeaponDataList.Add(WeaponNumbers);
	TotalWeaponCount++;
	if (HadWeaponCheck[WeaponNumbers] == false)
		HadWeaponCheck[WeaponNumbers] = true;
	else
		HadWeaponOverlap[WeaponNumbers] += 1.f;
}

void ARogueState::HadWeaponCheckInit() {
	for (int i = 0; i <= 9; i++) {
		HadWeaponCheck[i] = false;
		HadWeaponOverlap[i] = 0;
	}
}

void ARogueState::Call_HadWeapon() {
	MyGameMode->Return_RogueTakeHaveWeaponDelegate.ExecuteIfBound(HadWeaponCheck, HadWeaponOverlap);
}

void ARogueState::GetRogueAbilityIndexAndString() {
	MyGameMode->Widget_AbilityListDelegate.ExecuteIfBound(EquipAbilityCount, AbilityTotalName);
}

void ARogueState::AttackFormHadCheck(int32 AttackForms, int32 AttackFormIndexs) {
	TotalAttackFormDataList1.Add(AttackForms);
	TotalAttackFormDataList2.Add(AttackFormIndexs);
	TotalAttackFormCount++;
	if(HadAttackFormCheck[AttackForms][AttackFormIndexs] == false)
		HadAttackFormCheck[AttackForms][AttackFormIndexs] = true;
	else {
		HadAttackFormOverlap[AttackForms][AttackFormIndexs] += 1.f;
	}
}

void ARogueState::AbilityHadCheck(int32 AbilityIndexNumber) {
	if (HadAbilityCheck[AbilityIndexNumber] == false)
		HadAbilityCheck[AbilityIndexNumber] = true;
	else if (HadAbilityCheck[AbilityIndexNumber] == true)
		HadAbilityOverlap[AbilityIndexNumber]+=1;
}

void ARogueState::AbilityHadCheckInit() {
	for (int i = 0; i < 24; i++) {
		HadAbilityCheck[i] = false;
		HadAbilityOverlap[i] = 1.f;
	}
}

void ARogueState::ElementalHadCheck(int32 ElementalIndexNumber) {
	TotalElementDataList.Add(ElementalIndexNumber);
	TotalElementCount++;
	if (HadElementalCheck[ElementalIndexNumber] == false)
		HadElementalCheck[ElementalIndexNumber] = true;
	else {
		HadElementalOverlap[ElementalIndexNumber] += 1.f;
	}
}

void ARogueState::ElementalHadCheckInit() {
	for (int i = 0; i < 10; i++) {
		HadElementalCheck[i] = false;
		HadElementalOverlap[i] = 0.f;
		if( i == 5 || i == 0)
			HadElementalOverlap[i] = 1.f;;
	}
}

void ARogueState::Call_HadAttackForm() {
	MyGameMode->Return_RogueTakeAttackFormDelegate.ExecuteIfBound(HadAttackFormCheck, HadAttackFormOverlap);
}

void ARogueState::Call_HadAbility() {
	MyGameMode->Return_RogueTakeAbilityDelegate.ExecuteIfBound(HadAbilityCheck, HadAbilityOverlap);
}

void ARogueState::Call_Elemental() {
	MyGameMode->Return_RogueTakeElementalDelegate.ExecuteIfBound(HadElementalCheck, HadElementalOverlap);
}

void ARogueState::HadAttackFormCheckInit() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; i < 10; i++) {
			HadAttackFormCheck[i][j] = false;
			HadAttackFormOverlap[i][j] = 0.f;
		}
}

int32 ARogueState::GetDialogueIndex() {
	return DialogueIndex;
}

void ARogueState::SetDialogueIndex(int32 NewIndex) {
	DialogueIndex = NewIndex;
}






//최종 세팅 라인--------------------------------------------------------------------------------------------------

void ARogueState::LastWeaponDamegeSetting() {
	//float AttackThreeFormSynergy = 1.f;
	float LastWeaponDmgSum = 0.f;
	float LastWeaponEDmgSum = 0.f;
	GetWeaponTotalDamege();
	/*if (AttackForm[0] == AttackForm[1] && AttackForm[1] == AttackForm[2]) {
		if (AttackFormIndex[0] == AttackFormIndex[1] && AttackFormIndex[1] == AttackFormIndex[2]) {
			AttackThreeFormSynergy = 0.8f;
		}
		else
			AttackThreeFormSynergy = 1.f;
	}
	else {
		AttackThreeFormSynergy = 1.1;
	}*/
	for (int i = 0; i < 3; i++) {
		if (LowHpToHighAttackSynergyCount == 1 && GetRogueHp() < GetRogueHp() / 4) {
			WeaponPhysicsDamege[i] *= 1.5;
			WeaponElementDamege *= 1.5;
		}

		if (FullHpToHighAttackSynergyCount == 1 && GetRogueHp() == FullMaxHp) {
			WeaponPhysicsDamege[i] *= 1.3;
			WeaponElementDamege *= 1.3;
		}

		LastWeaponDmgSum += WeaponPhysicsDamege[i];
		//LastWeaponEDmgSum = (WeaponElementDamege * (1 + HadElementalOverlap[WeaponElementNumber] / 10));
	}

	LastAvgWeaponDamege = LastWeaponDmgSum / 3;
	LastAvgWeaponEDamge = WeaponElementDamege;

	
	MyGameMode->WeaponTotalDamegeDelegate.ExecuteIfBound(WeaponPhysicsDamege, WeaponElementDamege, WeaponElementValue * WeaponElementValueBonus);
	
	MyGameMode->WeaponDoubleAttackAndAttackDirectionDelegate.ExecuteIfBound(DoubleAttackCheck[0], DoubleAttackCheck[1],
		DoubleAttackCheck[2], AttackDirectionCheck[0][0], AttackDirectionCheck[0][1], AttackDirectionCheck[1][0],
		AttackDirectionCheck[1][1], AttackDirectionCheck[2][0], AttackDirectionCheck[2][1]);
}

void ARogueState::LastTorchDamegeSetting() {
	TorchStabTotalDamege = TorchStabDefaultDamege * TorchLevelValue * ElementLevelValue * SelectedElementBonus[TorchElementNumber];
	
	TorchBurnAttacksTotalDamege = TorchBurnAttacksDefaultDamege * ElementLevelValue * SelectedElementBonus[TorchElementNumber] 
		* TorchBurnAttackSynergyValue * (1 + HadElementalOverlap[TorchElementNumber+5] / 10);

	TorchSpecialTotalDamege = TorchElementSpecialDefaultDamege * SelectedElementBonus[TorchElementNumber] * ElementLevelValue 
		* TorchSpecialTotalDamegeValue * (1 + HadElementalOverlap[TorchElementNumber+5] / 10);
	
	MyGameMode->TorchTotalDamegeDelegate.ExecuteIfBound(TorchStabTotalDamege, TorchBurnAttacksTotalDamege, TorchSpecialTotalDamege, TorchElementCriper* TorchElementCriperValue);
}

void ARogueState::LastSpeedSetting() {
	MyGameMode->WeaponSpeedSynergyDelegate.ExecuteIfBound(WeaponSpeed, WeaponSpeedValueBonus, WeaponLevelValue);
	MyGameMode->TorchSpeedSynergyDelegate.ExecuteIfBound(TorchLevelValue);
}

void ARogueState::DialgoueStateInit() {
	for (int i = 0; i < 7; i++) {
		StartDialogueState[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		MainDialogueState[i] = 0;
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			SubDialogueState[i][j] = 0;
		}
	}
}

void ARogueState::DialogueRefInit() {
	StartDialogueSourceRef[0][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Tutorial/Opening_0.Opening_0'");
	StartDialogueSourceRef[1][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Tutorial/PupleFire_Item.PupleFire_Item'");
	StartDialogueSourceRef[2][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Tutorial/Castle_main_in.Castle_main_in'");
	StartDialogueSourceRef[3][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Tutorial/Enemy.Enemy'");
	StartDialogueSourceRef[4][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Tutorial/Smelting_One.Smelting_One'");
	StartDialogueSourceRef[5][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Tutorial/Smelting_Two.Smelting_Two'");
	StartDialogueSourceRef[6][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Tutorial/Smelting_Three.Smelting_Three'");

	StartDialogueSourceRef[0][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Tutorial/Opening_0.Opening_0'");
	StartDialogueSourceRef[1][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Tutorial/PupleFire_Item.PupleFire_Item'");
	StartDialogueSourceRef[2][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Tutorial/Castle_main_in.Castle_main_in'");
	StartDialogueSourceRef[3][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Tutorial/Enemy.Enemy'");
	StartDialogueSourceRef[4][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Tutorial/Smelting_One.Smelting_One'");
	StartDialogueSourceRef[5][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Tutorial/Smelting_Two.Smelting_Two'");
	StartDialogueSourceRef[6][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Tutorial/Smelting_Three.Smelting_Three'");

	StartDialogueSourceRef[0][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/GameStart_Cue.GameStart_Cue'");
	StartDialogueSourceRef[1][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/GetFire_Cue.GetFire_Cue'");
	StartDialogueSourceRef[2][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/StartCamp_Cue.StartCamp_Cue'");
	StartDialogueSourceRef[3][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/FirstEnemy_Cue.FirstEnemy_Cue'");
	StartDialogueSourceRef[4][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/FirstBonFire_Cue.FirstBonFire_Cue'");
	StartDialogueSourceRef[5][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/SecondBonFire_Cue.SecondBonFire_Cue'");
	StartDialogueSourceRef[6][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/ThirdBonFire_Cue.ThirdBonFire_Cue'");

	/*StartDialogueSoundRef[0] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/GameStart_Cue.GameStart_Cue'");
	StartDialogueSoundRef[1] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/GetFire_Cue.GetFire_Cue'");
	StartDialogueSoundRef[2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/StartCamp_Cue.StartCamp_Cue'");
	StartDialogueSoundRef[3] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/FirstEnemy_Cue.FirstEnemy_Cue'");
	StartDialogueSoundRef[4] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/FirstBonFire_Cue.FirstBonFire_Cue'");
	StartDialogueSoundRef[5] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/SecondBonFire_Cue.SecondBonFire_Cue'");
	StartDialogueSoundRef[6] = TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/ThirdBonFire_Cue.ThirdBonFire_Cue'");*/

	
	MainStoryDialogueSourceRef[0][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Main/Main1_1.Main1_1'");
	MainStoryDialogueSourceRef[1][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Main/Main1_2.Main1_2'");
	MainStoryDialogueSourceRef[2][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Main/Main1_3.Main1_3'");
	MainStoryDialogueSourceRef[3][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Main/Main1_4.Main1_4'");
	MainStoryDialogueSourceRef[4][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Main/Main1_5.Main1_5'");

	MainStoryDialogueSourceRef[0][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Main/Main1_1.Main1_1'");
	MainStoryDialogueSourceRef[1][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Main/Main1_2.Main1_2'");
	MainStoryDialogueSourceRef[2][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Main/Main1_3.Main1_3'");
	MainStoryDialogueSourceRef[3][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Main/Main1_4.Main1_4'");
	MainStoryDialogueSourceRef[4][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Main/Main1_5.Main1_5'");

	MainStoryDialogueSourceRef[0][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Main/Audio/Main1_1_Cue.Main1_1_Cue'");
	MainStoryDialogueSourceRef[1][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Main/Audio/Main1_2_Cue.Main1_2_Cue'");
	MainStoryDialogueSourceRef[2][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Main/Audio/Main1_3_Cue.Main1_3_Cue'");
	MainStoryDialogueSourceRef[3][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Main/Audio/Main1_4_Cue.Main1_4_Cue'");
	MainStoryDialogueSourceRef[4][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Main/Audio/Main1_5_Cue.Main1_5_Cue'");

	SubStoryDialogueSourceRef[0][0][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Sub/Sub1/Sub1_1.Sub1_1'");
	SubStoryDialogueSourceRef[0][1][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Sub/Sub1/Sub1_2.Sub1_2'");
	SubStoryDialogueSourceRef[0][2][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Sub/Sub1/Sub1_3.Sub1_3'");
	SubStoryDialogueSourceRef[0][3][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Sub/Sub1/Sub1_4.Sub1_4'");

	SubStoryDialogueSourceRef[0][0][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Sub/Sub1/Sub1_1.Sub1_1'");
	SubStoryDialogueSourceRef[0][1][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Sub/Sub1/Sub1_2.Sub1_2'");
	SubStoryDialogueSourceRef[0][2][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Sub/Sub1/Sub1_3.Sub1_3'");
	SubStoryDialogueSourceRef[0][3][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Sub/Sub1/Sub1_4.Sub1_4'");

	SubStoryDialogueSourceRef[0][0][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Sub/Sub1/Audio/Sub1_1_Cue.Sub1_1_Cue'");
	SubStoryDialogueSourceRef[0][1][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Sub/Sub1/Audio/Sub1_2_Cue.Sub1_2_Cue'");
	SubStoryDialogueSourceRef[0][2][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Sub/Sub1/Audio/Sub1_3_Cue.Sub1_3_Cue'");
	SubStoryDialogueSourceRef[0][3][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Sub/Sub1/Audio/Sub1_4_Cue.Sub1_4_Cue'");
	
	SubStoryDialogueSourceRef[1][0][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Sub/Sub2/Sub2_1.Sub2_1'");
	SubStoryDialogueSourceRef[1][1][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Sub/Sub2/Sub2_2.Sub2_2'");
	SubStoryDialogueSourceRef[1][2][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Sub/Sub2/Sub2_3.Sub2_3'");
	SubStoryDialogueSourceRef[1][3][0] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Eng/Sub/Sub2/Sub2_4.Sub2_4'");

	SubStoryDialogueSourceRef[1][0][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Sub/Sub2/Sub2_1.Sub2_1'");
	SubStoryDialogueSourceRef[1][1][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Sub/Sub2/Sub2_2.Sub2_2'");
	SubStoryDialogueSourceRef[1][2][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Sub/Sub2/Sub2_3.Sub2_3'");
	SubStoryDialogueSourceRef[1][3][1] = TEXT("FileMediaSource'/Game/Movies/NewDialogue/Sub/Sub2/Sub2_4.Sub2_4'");

	SubStoryDialogueSourceRef[1][0][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Sub/Sub2/Audio/Sub2_1_Cue.Sub2_1_Cue'");
	SubStoryDialogueSourceRef[1][1][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Sub/Sub2/Audio/Sub2_2_Cue.Sub2_2_Cue'");
	SubStoryDialogueSourceRef[1][2][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Sub/Sub2/Audio/Sub2_3_Cue.Sub2_3_Cue'");
	SubStoryDialogueSourceRef[1][3][2] = TEXT("SoundCue'/Game/Movies/NewDialogue/Sub/Sub2/Audio/Sub2_4_Cue.Sub2_4_Cue'");
}

void ARogueState::PlusDungeonClearCount(int32 DungeonIndex) {
	DungeonClearCount[DungeonIndex - 1]++;
	DungeonClearAllCount++;
}

int32 ARogueState::GetDungeonClearCount(int32 DungeonIndex) {
	return DungeonClearCount[DungeonIndex - 1];
}

int32 ARogueState::GetDungeonClearAllCount() {
	return DungeonClearAllCount;
}