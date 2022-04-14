// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RogueSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API URogueSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	URogueSaveGame();

	UPROPERTY()
		int32 WeaponLevel;
	UPROPERTY()
		int32 TorchLevel;
	UPROPERTY()
		int32 ElementalLevel;

	UPROPERTY()
		float WeaponLevelEx;
	UPROPERTY()
		float TorchLevelEx;
	UPROPERTY()
		float ElementalLevelEx;

	UPROPERTY()
		int32 RogueKill;
	UPROPERTY()
		int32 RogueDeath;
	UPROPERTY()
		int32 RogueTotalKill;

	UPROPERTY()
		int32 DungeonClearAllCount;

	UPROPERTY()
		int32 DungeonClearCount[3];

	/*UPROPERTY()
		TArray<int32> TotalEquipAbilityDataList;
	UPROPERTY()
		int32 TotalEquipAbilityCount;
	
	UPROPERTY()
		TArray<int32> TotalTakeWeaponDataList;
	UPROPERTY()
		int32 TotalTakeWeaponCount;

	UPROPERTY()
		TArray<int32> TotalTakeElementalDataList;
	UPROPERTY()
		int32 TotalTakeElementalCount;

	UPROPERTY()
		TArray<int32> TotalAttackFormDataList1;
	UPROPERTY()
		TArray<int32> TotalAttackFormDataList2;
	UPROPERTY()
		int32 TotalAttackFormCount;

	UPROPERTY()
		int32 WeaponNumber;
	UPROPERTY()
		int32 WeaponElemental;
	UPROPERTY()
		int32 TorchElemental;
	UPROPERTY()
		int32 WeaponLevel;
	UPROPERTY()
		int32 TorchLevel;
	UPROPERTY()
		int32 ElementalLevel;
	
	UPROPERTY()
		int32 RogueHp;
	UPROPERTY()
		int32 RogueData;
	UPROPERTY()
		int32 RogueKarma;
	
	UPROPERTY()
		bool NewGameStart;

	UPROPERTY()
		FVector LastLocation;

	UPROPERTY()
		int32 StageIndex;
	UPROPERTY()
		int32 StageSubIndex;

	UPROPERTY()
		int32 AttackForm[3];
	UPROPERTY()
		int32 AttackFormDetail[3];

	UPROPERTY()
		bool DungeonIn;

	

	UPROPERTY()
		int32 StoryProgress[3];

	UPROPERTY()
		int32 DialogueIndex;
	
	UPROPERTY()
		int32 StartDialogueState[7];

	UPROPERTY()
		int32 MainDialogueState[5];

	UPROPERTY()
		int32 SubDialogueState[8];

	
	UPROPERTY()
		int32 StartDialogueIndex;

	UPROPERTY()
		int32 MainDialogueIndex;

	UPROPERTY()
		int32 SubDialogueKinds;

	UPROPERTY()
		int32 SubDialogueIndex;

	
	UPROPERTY()
		int32 ItemCount;

	UPROPERTY()
		int32 DialogueTutorialCount;

	UPROPERTY()
		float RogueMoveSpeed;

	

	UPROPERTY()
		bool RollingTrdCamera;

	UPROPERTY()
		int32 DungeonClearCount[3];

	UPROPERTY()
		int32 DungeonClearAllCount;

	UPROPERTY()
		int32 RogueKill;

	UPROPERTY()
		int32 RogueTotalKill;

	UPROPERTY()
		int32 RogueDeath;

	UPROPERTY()
		int32 UsedData;

	UPROPERTY()
		int32 AllData;

	UPROPERTY()
		int32 DoorOpenCheck[10];


	UPROPERTY()
		int32 AttackIncreaseValue[3];
	UPROPERTY()
		int32 BurnAttackDmgIncreaseValue;
	UPROPERTY()
		int32 ElementalSynergy[5];
	UPROPERTY()
		int32 BurnHitIncrease;
	UPROPERTY()
		int32 MoveSpeedIncrease;
	UPROPERTY()
		int32 HitKnokback;
	UPROPERTY()
		int32 SuperArmorCount;
	UPROPERTY()
		int32 AttackCriticalStreamPerValue;
	UPROPERTY()
		int32 AttackUseDataLow;
	UPROPERTY()
		int32 TorchCriticalPerIncrease;
	UPROPERTY()
		int32 WeaponCriticalPerIncrease;
	UPROPERTY()
		int32 TorchCriticalDmgIncrease;
	UPROPERTY()
		int32 WeaponDmgPerIncrease;
	UPROPERTY()
		int32 AttackSpeedPerValue;
	UPROPERTY()
		int32 LowHpAttackSynergy;
	UPROPERTY()
		int32 FullHpAttackSynergy;
	UPROPERTY()
		int32 AttackDmgIncreaseStreamValue;
	UPROPERTY()
		int32 FullHp;
	UPROPERTY()
		int32 AbilityCount;
	UPROPERTY()
		int32 AbilityQue[100];*/

};
