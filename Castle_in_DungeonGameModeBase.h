// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "RogueSaveGame.h"
#include "Sound/SoundClass.h"
#include "RogueLevel.h"
#include "Castle_in_DungeonGameModeBase.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(WeaponWallCrashDelegateSignature);
DECLARE_DELEGATE(TorchWallCrashDelegateSignature);
DECLARE_DELEGATE(TorchWallLeaveDelegateSignature);
DECLARE_DELEGATE_OneParam(TorchWallSideCrashDelegateSignature, bool);
DECLARE_DELEGATE_OneParam(TorchWallSideLeaveDelegateSignature, bool);

DECLARE_DELEGATE_TwoParams(KeyInputTorchElementChangeDelegateSignature, int32, bool);
DECLARE_DELEGATE_TwoParams(KeyInputWeaponElementChangeDelegateSignature, int32, bool);
DECLARE_DELEGATE_OneParam(Call_WeaponChangeDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Return_WeaponChangeDelegateSignature, int32);
DECLARE_DELEGATE(KeyInputAttackAnimationChangeDelegateSignature);

DECLARE_DELEGATE_TwoParams(TorchElementChangeDelegateSignature, int32, float);
DECLARE_DELEGATE_TwoParams(WeaponElementChangeDelegateSignature, int32, float);
DECLARE_DELEGATE_OneParam(WeaponChangeDelegateSignature, int32);
DECLARE_DELEGATE_SixParams(AttackAnimationChangeDelegateSignature, int32, int32, int32, int32, int32, int32);

DECLARE_DELEGATE_SixParams(WeaponSynergyDelegateSignature, int32, float, float, float, float, float);
DECLARE_DELEGATE_ThreeParams(WeaponElementSynergyDelegateSignature, float, float, float);
DECLARE_DELEGATE_ThreeParams(AttackFormSynergyDelegateSignature, float*, bool*, int32[3][2]);
DECLARE_DELEGATE_FourParams(TorchStatusSynergyDelegateSignature, float, float, float, float);

DECLARE_DELEGATE(WeaponTotalDamegeSettingDelegateSignature);
DECLARE_DELEGATE_FourParams(WeaponTotalDamegeDelegateSignature, float, float, float, float);
DECLARE_DELEGATE_NineParams(WeaponDoubleAttackAndAttackDirectionDelegateSignaure, bool, bool, bool, int32, int32, int32, int32, int32, int32);
DECLARE_DELEGATE_OneParam(WeaponAttackQueDelegateSignature, int32);

DECLARE_DELEGATE_FourParams(TorchTotalDamegeDelegateSignature, float, float, float, float);
DECLARE_DELEGATE(TorchTotalDamgeSettingDelegateSignature);

DECLARE_DELEGATE_ThreeParams(WeaponSpeedSynergyDelegateSignature, float, float, float);
DECLARE_DELEGATE_OneParam(TorchSpeedSynergyDelegateSignature, float);

DECLARE_DELEGATE_NineParams(EnemyRogueTakeWeaponDamegeDelegateSignature, float, float, float, int32, int32, bool*, bool, int32, int32);
DECLARE_DELEGATE_EightParams(EnemyRogueTakeTorchDamegeDelegateSignaturem, float, float, float, int32*, bool, bool*, bool*, int32);

DECLARE_DELEGATE_OneParam(RogueSetDataDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Call_SetStaticDataChangeDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(RogueSetKarmaDelegateSignature, int32);

DECLARE_MULTICAST_DELEGATE_OneParam(RogueAttackVectorToEnemyRogueDelegateSignature, FVector);

DECLARE_DELEGATE(RogueTorchLevelUpDelegateSignature);
DECLARE_DELEGATE(RogueWeaponLevelUpDelegateSignature);
DECLARE_DELEGATE_TwoParams(RogueElementLevelToWeaponDelegateSignature, int32, float);
DECLARE_DELEGATE_TwoParams(RogueElementLevelToTorchDelegateSignature, int32, float);

DECLARE_DELEGATE_OneParam(TorchBurnAttacksHitValueDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(WeaponHitKnockBackDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(RogueSpeedIncreaseDelegateSignature, float);
DECLARE_DELEGATE_OneParam(Rogue_SpeedValueDelegateSignature, float);
DECLARE_DELEGATE_OneParam(RogueSuperArmorDelegateSignature, float);
DECLARE_DELEGATE_OneParam(WeaponAttackToEffectPercentIncreaseDelegateSignature, float);
DECLARE_DELEGATE_OneParam(WeaponAttackToDmgIncreaseDelegateSignature, float);
DECLARE_DELEGATE(WeaponAttackToEffectPercentIncreaseDelegateSignature_);
//DECLARE_DELEGATE_OneParam(RogueAttackTryToLowDataDecreaseDelegateSignature, float);

DECLARE_DELEGATE(EnemyRogueEffectStateCheckDelegateSignature);
DECLARE_DELEGATE_OneParam(RogueTakeAbilityDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Call_RogueHavingWeaponCheckDelegateSignature, int32);
DECLARE_DELEGATE_TwoParams(Call_RogueHavingAttackFormCheckDelegateSignature, int32, int32);
DECLARE_DELEGATE_OneParam(Call_RogueHavingAbilityCheckDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Call_RogueHavingElementalCheckDelegateSignature, int32);

DECLARE_DELEGATE_TwoParams(Return_RogueTakeHaveWeaponDelegateSignature, bool*, float*);
DECLARE_DELEGATE_TwoParams(Return_RogueTakeHaveAttackFormDelegateSignature, bool AttackForm[4][10], float AttackFormOverlap[4][10]);
DECLARE_DELEGATE_TwoParams(Return_RogueTakeHaveAbilityDelegateSignature, bool*, float*);
DECLARE_DELEGATE_TwoParams(Return_RogueTakeHaveElementalDelegateSignature, bool*, float*);
DECLARE_DELEGATE(Call_RogueTakeHaveWeaponDelegateSignature);
DECLARE_DELEGATE(Call_RogueTakeHaveAttackFormDelegateSignature);
DECLARE_DELEGATE(Call_RogueTakeHaveAbilityDelegateSignature);
DECLARE_DELEGATE(Call_RogueTakeHaveElementalDelegateSignature);

DECLARE_DELEGATE(Call_RogueUseWeaponReferenceDelegateSignature);
DECLARE_DELEGATE_OneParam(Return_RogueUseWeaponReferenceDelegateSignature, int32);

DECLARE_DELEGATE_OneParam(Widget_GetRogueHpDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Rogue_GetHpDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Widget_GetRogueDataDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Widget_GetRogueKarmaDelegateSignature, int32);
DECLARE_DELEGATE_EightParams(Widget_GetRogueEquipmentDelegateSignature, FString*, TCHAR**, TCHAR**, 
int32*, int32*, int32*, float*, float**);

DECLARE_DELEGATE_OneParam(Widget_ChangedWidgetDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Widget_ChangedWidgetButtonDelegateSignature, int32);
DECLARE_DELEGATE(Widget_RogueUIValueInitDelegateSignature);
DECLARE_DELEGATE_OneParam(Widget_StatDataDelegateSignature, float*);
DECLARE_DELEGATE(Widget_CallStatWidgetDelegateSignature);
DECLARE_DELEGATE(Widget_CallEquipmentWidgetDelegateSignature);
DECLARE_DELEGATE_TwoParams(Widget_AbilityListDelegateSignature, int32, FString*);
DECLARE_DELEGATE(Widget_CallAbilityListDelegateSignature);
DECLARE_DELEGATE_OneParam(Widget_MouseCursorChangedDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Widget_MouseCursorOnRogueNotInputDelegateSignature, int32);

DECLARE_DELEGATE_ThreeParams(Call_TakeAttackFormDelegateSignature, int32, int32, int32);
DECLARE_DELEGATE(Call_GameStartWeaponNumberDelegateSignature);
DECLARE_DELEGATE(Call_GameStartTorchElementalNumberDelegateSignature);
DECLARE_DELEGATE_OneParam(Return_GameStartWeaponNumberDelegateSignature, int32);

DECLARE_DELEGATE(Call_GameStartAttackFormNumberDelegateSignature);

DECLARE_DELEGATE_OneParam(Call_TakeAttackFormRefDelegateSignature, TCHAR**);
DECLARE_DELEGATE_OneParam(Call_RogueDamageDelegateSignature, float);

DECLARE_DELEGATE(Call_GameSaveDelegateSignature);
DECLARE_DELEGATE_OneParam(Call_StageIndexDelegateSignature, int32);
DECLARE_DELEGATE_OneParam(Call_RogueFOVDelegateSignature, float);

////------------버그보완

DECLARE_DELEGATE(RogueTorchAttackFinishDelegateSignature);
UCLASS()
class CASTLE_IN_DUNGEON_API ACastle_in_DungeonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACastle_in_DungeonGameModeBase();
	virtual void BeginPlay() override;
	WeaponWallCrashDelegateSignature WeaponWallCrash;
	TorchWallCrashDelegateSignature TorchWallCrash;
	TorchWallLeaveDelegateSignature TorchWallLeave;
	TorchWallSideCrashDelegateSignature TorchWallSideCrash;
	TorchWallSideLeaveDelegateSignature TorchWallSideLeave;
	
	KeyInputTorchElementChangeDelegateSignature TorchElementChangeDelegate;
	KeyInputWeaponElementChangeDelegateSignature WeaponElementChangeDelegate;
	Call_WeaponChangeDelegateSignature Call_WeaponChangeDelegate;
	Return_WeaponChangeDelegateSignature Return_WeaponChangeDelegate;
	KeyInputAttackAnimationChangeDelegateSignature AttackAnimationChangeDelegate;
	
	TorchElementChangeDelegateSignature TorchElementChangeDelegate_;
	WeaponElementChangeDelegateSignature WeaponElementChangeDelegate_;
	AttackAnimationChangeDelegateSignature AttackAnimationChangeDelegate_;

	WeaponSynergyDelegateSignature WeaponSynergyDelegate;
	WeaponElementSynergyDelegateSignature WeaponElementSynergyDelegate;
	AttackFormSynergyDelegateSignature AttackFormSynergyDelegate;
	TorchStatusSynergyDelegateSignature TorchStatusSynergyDelegate;

	WeaponTotalDamegeSettingDelegateSignature WeaponTotalDamegeSettingDelegate;
	WeaponTotalDamegeDelegateSignature WeaponTotalDamegeDelegate;
	WeaponDoubleAttackAndAttackDirectionDelegateSignaure WeaponDoubleAttackAndAttackDirectionDelegate;
	WeaponAttackQueDelegateSignature WeaponAttackQueDelegate;
	TorchTotalDamegeDelegateSignature TorchTotalDamegeDelegate;
	TorchTotalDamgeSettingDelegateSignature TorchTotalDamgeSettingDelegate;

	WeaponSpeedSynergyDelegateSignature WeaponSpeedSynergyDelegate;
	TorchSpeedSynergyDelegateSignature TorchSpeedSynergyDelegate;

	EnemyRogueTakeWeaponDamegeDelegateSignature EnemyRogueTakeWeaponDamegeDelegate;
	EnemyRogueTakeTorchDamegeDelegateSignaturem EnemyRogueTakeTorchDamegeDelegate;

	RogueSetDataDelegateSignature RogueSetDataDelegate;
	Call_SetStaticDataChangeDelegateSignature Call_SetStaticDataChangeDelegate;
	RogueSetKarmaDelegateSignature RogueSetKarmaDelegate;

	RogueAttackVectorToEnemyRogueDelegateSignature RogueAttackVectorToEnemyRogueDelegate;
	RogueTorchLevelUpDelegateSignature RogueTorchLevelUpDelegate;
	RogueWeaponLevelUpDelegateSignature RogueWeaponLevelDelegate;

	RogueElementLevelToWeaponDelegateSignature RogueElementLevelToWeaponDelegate;
	RogueElementLevelToTorchDelegateSignature RogueElementLevelToTorchDelegate;
	TorchBurnAttacksHitValueDelegateSignature TorchBurnAttacksHitValueDelegate;
	WeaponHitKnockBackDelegateSignature WeaponHitKnockBackDelegate;
	RogueSpeedIncreaseDelegateSignature RogueSpeedIncreaseDelegate;
	Rogue_SpeedValueDelegateSignature Rogue_SpeedValueDelegate;
	RogueSuperArmorDelegateSignature RogueSuperArmorDelegate;
	WeaponAttackToEffectPercentIncreaseDelegateSignature WeaponAttackToEffectPercentIncreaseDelegate;
	WeaponAttackToEffectPercentIncreaseDelegateSignature_ WeaponAttackToEffectPercentIncreaseDelegate_;
	WeaponAttackToDmgIncreaseDelegateSignature WeaponAttackToDmgIncreaseDelegate;
	//RogueAttackTryToLowDataDecreaseDelegateSignature RogueAttackTryToLowDataDecreaseDelegate;

	RogueTorchAttackFinishDelegateSignature RogueTorchAttackFinishDelegate;
	EnemyRogueEffectStateCheckDelegateSignature EnemyRogueEffectStateCheckDelegate;
	RogueTakeAbilityDelegateSignature RogueTakeAbilityDelegate;

	Call_RogueHavingWeaponCheckDelegateSignature Call_RogueHavingWeaponCheckDelegate;
	Call_RogueHavingAttackFormCheckDelegateSignature Call_RogueHavingAttackFormCheckDelegate;
	Call_RogueHavingAbilityCheckDelegateSignature Call_RogueHavingAbilityCheckDelegate;
	Call_RogueHavingElementalCheckDelegateSignature Call_RogueHavingElementalCheckDelegate;

	Call_RogueTakeHaveWeaponDelegateSignature Call_RogueTakeHaveWeaponDelegate;
	Call_RogueTakeHaveAttackFormDelegateSignature Call_RogueTakeHaveAttackFormDelegate;
	Call_RogueTakeHaveAbilityDelegateSignature Call_RogueTakeHaveAbilityDelegate;
	Call_RogueTakeHaveElementalDelegateSignature Call_RogueTakeHaveElementalDelegate;
	
	Return_RogueTakeHaveWeaponDelegateSignature Return_RogueTakeHaveWeaponDelegate;
	Return_RogueTakeHaveAttackFormDelegateSignature Return_RogueTakeAttackFormDelegate;
	Return_RogueTakeHaveAbilityDelegateSignature Return_RogueTakeAbilityDelegate;
	Return_RogueTakeHaveElementalDelegateSignature Return_RogueTakeElementalDelegate;

	Call_RogueUseWeaponReferenceDelegateSignature Call_RogueUseWeaponReferenceDelegate;
	Return_RogueUseWeaponReferenceDelegateSignature Return_RogueUseWeaponReferenceDelegate;

	Widget_ChangedWidgetDelegateSignature Widget_ChangedWidgetDelegate;
	Widget_ChangedWidgetButtonDelegateSignature Widget_ChangedWidgetButtonDelegate;
	Widget_GetRogueHpDelegateSignature Widget_GetRogueHpDelegate;
	Rogue_GetHpDelegateSignature Rogue_GetHpDelegate;
	Widget_GetRogueDataDelegateSignature Widget_GetRogueDataDelegate;
	Widget_GetRogueKarmaDelegateSignature Widget_GetRogueKarmaDelegate;
	Widget_GetRogueEquipmentDelegateSignature Widget_GetRogueEquipmentDelegate;
	Widget_RogueUIValueInitDelegateSignature Widget_RogueUIValueInitDelegate;
	Widget_MouseCursorChangedDelegateSignature Widget_MouseCursorChangedDelegate;
	Widget_MouseCursorOnRogueNotInputDelegateSignature Widget_MouseCursorOnRogueNotInputDelegate;

	Widget_StatDataDelegateSignature Widget_StatDataDelegate;
	Widget_CallStatWidgetDelegateSignature Widget_CallStatWidgetDelegate;
	Widget_CallEquipmentWidgetDelegateSignature Widget_CallEquipmentWidgetDelegate;
	Widget_AbilityListDelegateSignature Widget_AbilityListDelegate;
	Widget_CallAbilityListDelegateSignature Widget_CallAbilityListDelegate;

	Call_TakeAttackFormDelegateSignature Call_TakeAttackFormDelegate;
	Call_GameStartWeaponNumberDelegateSignature Call_GameStartWeaponNumberDelegate;
	Call_GameStartTorchElementalNumberDelegateSignature Call_GameStartTorchElementalNumberDelegate;
	Return_GameStartWeaponNumberDelegateSignature Return_GameStartWeaponNumberDelegate;

	Call_GameStartAttackFormNumberDelegateSignature Call_GameStartAttackFormNumberDelegate;

	Call_TakeAttackFormRefDelegateSignature Call_TakeAttackFormRefDelegate;
	Call_RogueDamageDelegateSignature Call_RogueDamageDelegate;
	Call_GameSaveDelegateSignature Call_GameSaveDelegate;
	Call_StageIndexDelegateSignature Call_StageIndexDelegate;
	Call_RogueFOVDelegateSignature Call_RogueFOVDelegate;
	//Return_GameStartAttackFormNumberDelegateSignature Return_GameStartAttackFormNumberDelegate;

public:
	bool TitleWidgetState;
	bool MainWidgetState;
	bool ReSumeWidgetState;
	bool TabWidgetState;
	bool TabWidgetIn;
	bool StatWidgetState;
	bool EquipmentWidgetState;
	bool BurningTotemWidgetState;
	bool ChangedWeaponWidgetState;
	bool ChangedAttackFormWidgetState;
	bool ChangedElementalFormWidgetState;
	bool AddAbilityWidgetState;
	bool DialogueWidgetState;
	bool RevivalWidgetState;
	bool TitleInRevivalWidgetState;
	bool KeyWidgetState;

private:
	TSubclassOf<UUserWidget> PreViewWidgetClass;
	class UMyRogueWidget* PreViewWidget;

	TSubclassOf<UUserWidget> NowViewWidgetClass;
	class UMyRogueWidget* NowViewWidget;

	TSubclassOf<UUserWidget> TitleMenuWidgetClass;
	class UMyRogueWidget* TitleMenuWidget;

	TSubclassOf<UUserWidget> TitleInRevivalWidgetClass;
	class UMyRogueWidget* TitleInRevivalWidget;

	TSubclassOf<UUserWidget> RevivalWidgetClass;
	class UMyRogueWidget* RevivalWidget;

	TSubclassOf<UUserWidget> MainWidgetClass;
	class UMyRogueWidget* MainWidget;

	TSubclassOf<UUserWidget> ReSumeWidgetClass;
	class UMyRogueWidget* ReSumeWidget;

	TSubclassOf<UUserWidget> KeyWidgetClass;
	class UMyRogueWidget* KeyWidget;

	TSubclassOf<UUserWidget> TabWidgetClass;
	class UMyRogueWidget* TabWidget;

	TSubclassOf<UUserWidget> StatWidgetClass;
	class UMyRogueWidget* StatWidget;

	TSubclassOf<UUserWidget> EquipmentWidgetClass;
	class UMyRogueWidget* EquipmentWidget;

	TSubclassOf<UUserWidget> BurningTotemWidgetClass;
	class UMyRogueWidget* BurningTotemWidget;

	TSubclassOf<UUserWidget> ChangedWeaponWidgetClass;
	class UMyRogueWidget* ChangedWeaponWidget;

	TSubclassOf<UUserWidget> ChangedAttackFormWidgetClass;
	class UMyRogueWidget* ChangedAttackFormWidget;

	TSubclassOf<UUserWidget> ChangedElementalFormWidgetClass;
	class UMyRogueWidget* ChangedElementalFormWidget;

	TSubclassOf<UUserWidget> AddAbilityWidgetClass;
	class UMyRogueWidget* AddAbilityWidget;

	TSubclassOf<UUserWidget> DialogueWidgetClass;
	class UMyRogueWidget* DialogueWidget;

public:
	int32 WidgetPageNumber;
	int32 WidgetPrePageNumber;
	TSubclassOf<UUserWidget> WidgetStack[100];
	int32 WidgetStackNumber[100];
	int32 WidgetCount;
	void ChangedWidget(TSubclassOf<UUserWidget> NewWidgetclass);
	void GetWidgetNumber(int32 PageNumber);
	int32 GetPageNumber() { return WidgetPageNumber; }
	void WidgetPop();
	void WidgetPush(TSubclassOf<UUserWidget> WidgetPush);
	void MainUIUpdate();
	void RevivalUIUpdate();
	void TitleUIUpdate();
	//void StartSetting();
	void LevelLoading();
	void LevelFloorCheck();
	void RevivalTextAlphaPlus();
	void RevivalTextAlphaMinus();
	void TitleBorderAlphaPlus();
	void GetStageIndex(int32 Index, int32 SubIndex);
	void LoadGameData(URogueSaveGame* LoadData);
	void SaveSystemData();

public:
	UPROPERTY(EditAnywhere)
		int32 GameStartCheck;
	UPROPERTY(EditAnywhere)
		USoundClass* FXSoundClass;
	UPROPERTY(EditAnywhere)
		float FXSoundVolumeValue;
	ARogueLevel* RogueLevel;
	//ARogueLevel* StartLevel[15];
	FTransform LevelFloorPoint1[5][5];
	FTransform LevelFloorPoint2[5][5];
	FTimerHandle RevivalAlphaPlusTimeHandle;
	FTimerHandle RevivalAlphaMinusTimeHandle;
	FTimerHandle TitleBorderBlackTimeHandle;
	int32 StageCount = 0;
	int32 StageX = 0;
	int32 StageY = 0;
	int32 PreDirection = 0;
	int32 NextDirection = 0;
	int32 PreDirectionIndex = 0;
	int32 NextDirectionIndex = 0;
	int32 StageIndex;
	int32 StageSubIndex;
	bool NextStageDirection[4];
	bool FloorUp = false;
	bool LevelFloorCheck1[5][5];
	bool RevivalTextAlphaMax = false;
	bool TitleBorderAlphaMax = false;
	float RevivalTextAlphaValue = 0.00f;
	float TitleBorderAlphaValue = 0.0f;
	float FOVValue = 100.f;
	void RemoveView(int32);
	bool NewGameStart;
	FString SaveSlotName;

	int32 StoryProgress[3];
	int32 SpecialStoryProgress[3];
};
