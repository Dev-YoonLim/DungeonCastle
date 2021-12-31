// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/Overlay.h"
#include "Components/CircularThrobber.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"
#include "Sound/SoundCue.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSource.h"
#include "RogueWeapon.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "Fonts/SlateFontInfo.h"
#include "Engine/Font.h"
#include "Castle_in_DungeonGameModeBase.h"
#include "MyRogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API UMyRogueWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* FOVValues;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SoundVolumeValues;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USlider* FOVSlider;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USlider* SoundSlider;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ControllBack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* Revival;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UBorder* RevivalOutLine;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCheckBox* CheckBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCheckBox* CheckBox2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* NewGameButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ExitGameButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UBorder* TitleBorder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* Option_Buttons;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* TaskBoxs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* TaskValues;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueHPValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueDataValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueKarmaValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* PressKeyText;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatMaxHPValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatTotalDataValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatTotalKillValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatMoveSpeedValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatSuperArmorValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatWeaponPhysicsDamegeValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatWeaponElementDamegeValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatWeaponEffectPercentageValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatTorchStabDamegeValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatTorchElementDamegeValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatTorchEffectDamegeValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatTorchEffectPercentageValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatWeaponSpeedValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatWeaponLevelValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatTorchLevelValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* RogueStatElementLevelValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* RogueStatBackButton;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ReSumeButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ReStartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* TitleMenuButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* GameExitButton;;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ViewStatButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ViewEquipButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ViewGameStateButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* TabBackButton;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* EquipWeaponValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* WeaponElementValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* TorchElementValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* AttackFormIValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* AttackFormIIValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* AttackFormIIIValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UScrollBox* RogueAbilityList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* RogueEquipmentBackButton;

	UPROPERTY()
		class UTextBlock* AbilityListValue[100];
	/*UPROPERTY()
		class UTextBlock* AbilityListOverlapValue[24];*/

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ChangedWeaponButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ChangedAttackFormButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ChangedElementalButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* AddAbilityButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* BurningTotemBackButtons;
	

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SelectWeaponButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ChangedWeaponBackButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UScrollBox* ChangedWeaponList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* WeaponAttributes1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* WeaponAttributes2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* WeaponAttributes3;
	UPROPERTY()
		class UButton* ViewWeaponListButton[10];
	UPROPERTY()
		class UTextBlock* ViewWeaponListText[10];
	UPROPERTY()
		class UImage* WeaponImages;
	UPROPERTY()
		class UImage* WeaponIcons1;
	UPROPERTY()
		class UImage* WeaponIcons2;
	


public:
	UPROPERTY()
		class UTextBlock* ViewAttackFormListText[40];
	UPROPERTY()
		class UButton* ViewAttackFormListButton[40];

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SelectAttackFormButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ChangedAttackFormBackButtons;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SlashListButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SmashListButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* StabListButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SpecialListButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SelectedAttackFormSlotButtons1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SelectedAttackFormSlotButtons2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SelectedAttackFormSlotButtons3;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UScrollBox* ChangedAttackFromList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectedAttackForm1s;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectedAttackForm2s;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectedAttackForm3s;

	UPROPERTY()
		class UOverlay* SelectedAttackFormSlotOverlay1;
	UPROPERTY()
		class UOverlay* SelectedAttackFormSlotOverlay2;
	UPROPERTY()
		class UOverlay* SelectedAttackFormSlotOverlay3;

	UPROPERTY()
		class UCircularThrobber* SelectedSlotState;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* StrenghtIcons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* HeatIcons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* ColdIcons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* PoisonIcons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* ElectricIcons;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* StrenghtIcons2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* HeatIcons2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* ColdIcons2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* PoisonIcons2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* ElectricIcons2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* SelectWeaponElementalIcons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* SelectTorchElementalIcons;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UButton* WeaponElementalButton[5];
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UButton* TorchElementalButton[5];
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* WeaponElementalText[5];
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* TorchElementalText[5];
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ChangedElementalSelectButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ChangedElementalBackButtons;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* ElementalText[6];
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* ElementPhase[2];

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SelectAbilityButton1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SelectAbilityButton2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SelectAbilityButton3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SelectAbilityButton4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* AddAbilityBackButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectClasses1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectClasses2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectClasses3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectClasses4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectAbilityName1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectAbilityName2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectAbilityName3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* SelectAbilityName4;
	UPROPERTY()
		class UImage* AbilityIcon1;
	UPROPERTY()
		class UImage* AbilityIcon2;
	UPROPERTY()
		class UImage* AbilityIcon3;
	UPROPERTY()
		class UImage* AbilityIcon4;
	UPROPERTY()
		class UTextBlock* NowDatas;



public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* Dialogue;
public:
	UFUNCTION(BlueprintCallable) void GetKeyMenu();
	UFUNCTION(BlueprintCallable) void GetNewGame();
	UFUNCTION(BlueprintCallable) void GetExitGame();
	UFUNCTION(BlueprintCallable) void GetRogueMain();
	UFUNCTION(BlueprintCallable) void GetTitleMenu();
	UFUNCTION(BlueprintCallable) void GetBackButton();
	
	UFUNCTION(BlueprintCallable) void GetTabMenu();
	UFUNCTION(BlueprintCallable) void GetRogueStat();
	UFUNCTION(BlueprintCallable) void GetRogueEquip();
	UFUNCTION(BlueprintCallable) void GetGameState();
	
	UFUNCTION(BlueprintCallable) void GetBurningTotemMenu();
	UFUNCTION(BlueprintCallable) void GetChangedWeaponMenu();
	UFUNCTION(BlueprintCallable) void GetChangedAttackFormMenu();
	UFUNCTION(BlueprintCallable) void GetChangedElementalMenu();
	UFUNCTION(BlueprintCallable) void GetAddAbilityMenu();
	UFUNCTION(BlueprintCallable) void GetSelectRogueAbilityOne();
	UFUNCTION(BlueprintCallable) void GetSelectRogueAbilityTwo();
	UFUNCTION(BlueprintCallable) void GetSelectRogueAbilityThree();
	UFUNCTION(BlueprintCallable) void GetSelectRogueAbilityFour();
	UFUNCTION(BlueprintCallable) void GetDialogue();
	UFUNCTION(BlueprintCallable) void GetRevival();

	UFUNCTION(BlueprintCallable)	void GetDaggerImage();
	UFUNCTION(BlueprintCallable)	void GetMaceImage();
	UFUNCTION(BlueprintCallable) void GetGAxeImage();
	UFUNCTION(BlueprintCallable) void GetGHammerImage();
	UFUNCTION(BlueprintCallable) void GetGSwordImage();
	UFUNCTION(BlueprintCallable) void GetSSwordImage();
	UFUNCTION(BlueprintCallable) void GetAxeImage();
	UFUNCTION(BlueprintCallable) void GetSpearImage();
	UFUNCTION(BlueprintCallable) void GetScytheImage();
	UFUNCTION(BlueprintCallable) void GetKnifeImage();
	UFUNCTION(BlueprintCallable) void SelectWeaponButtonFuntion();

	UFUNCTION(BlueprintCallable) void GetSlashList();
	UFUNCTION(BlueprintCallable) void GetSmashList();
	UFUNCTION(BlueprintCallable) void GetStabList();
	UFUNCTION(BlueprintCallable) void GetSpecialList();
	UFUNCTION(BlueprintCallable) void SelectedAttackFormSlotOne();
	UFUNCTION(BlueprintCallable) void SelectedAttackFormSlotTwo();
	UFUNCTION(BlueprintCallable) void SelectedAttackFormSlotThree();
	
	UFUNCTION(BlueprintCallable) void AttackSlotInSlash();
	UFUNCTION(BlueprintCallable) void AttackSlotInReverseSlash();
	UFUNCTION(BlueprintCallable) void AttackSlotInBashSlash();
	UFUNCTION(BlueprintCallable) void AttackSlotInUpperSlash();
	UFUNCTION(BlueprintCallable) void AttackSlotInXSlash();
	UFUNCTION(BlueprintCallable) void AttackSlotInDownUpper();
	UFUNCTION(BlueprintCallable) void AttackSlotInWhiteFang();

	UFUNCTION(BlueprintCallable) void AttackSlotInSmash();
	UFUNCTION(BlueprintCallable) void AttackSlotInBreaker();
	UFUNCTION(BlueprintCallable) void AttackSlotInSideSmash();
	UFUNCTION(BlueprintCallable) void AttackSlotInSideBreaker();
	UFUNCTION(BlueprintCallable) void AttackSlotInShortPick();
	UFUNCTION(BlueprintCallable) void AttackSlotInGroundBreaker();
	UFUNCTION(BlueprintCallable) void AttackSlotInReverseSideSmash();
	UFUNCTION(BlueprintCallable) void AttackSlotInHeadDancer();
	UFUNCTION(BlueprintCallable) void AttackSlotInCranker();
	
	UFUNCTION(BlueprintCallable) void AttackSlotInStab();
	UFUNCTION(BlueprintCallable) void AttackSlotInQuickStab();
	UFUNCTION(BlueprintCallable) void AttackSlotInDeepStab();
	UFUNCTION(BlueprintCallable) void AttackSlotInHooks();
	UFUNCTION(BlueprintCallable) void AttackSlotInUpperStab();
	UFUNCTION(BlueprintCallable) void AttackSlotInOneInchStab();
	UFUNCTION(BlueprintCallable) void AttackSlotInDoubleStab();
	UFUNCTION(BlueprintCallable) void AttackSlotInTwoFace();
	UFUNCTION(BlueprintCallable) void AttackSlotInPitFinish();
	UFUNCTION(BlueprintCallable) void AttackSlotInWindHole();
	
	UFUNCTION(BlueprintCallable) void AttackSlotInAirTrack();
	UFUNCTION(BlueprintCallable) void AttackSlotInDeleteRow();
	UFUNCTION(BlueprintCallable) void AttackSlotInTurnEnd();
	UFUNCTION(BlueprintCallable) void SelectAttackFormButtonFuntion();

	UFUNCTION(BlueprintCallable) void WeaponElementStrenght();
	UFUNCTION(BlueprintCallable) void WeaponElementHeat();
	UFUNCTION(BlueprintCallable) void WeaponElementCold();
	UFUNCTION(BlueprintCallable) void WeaponElementPoison();
	UFUNCTION(BlueprintCallable) void WeaponElementElectric();
	UFUNCTION(BlueprintCallable) void TorchElementStrenght();
	UFUNCTION(BlueprintCallable) void TorchElementHeat();
	UFUNCTION(BlueprintCallable) void TorchElementCold();
	UFUNCTION(BlueprintCallable) void TorchElementPoison();
	UFUNCTION(BlueprintCallable) void TorchElementElectric();
	UFUNCTION(BlueprintCallable) void SelectElementalButton();

	UFUNCTION(BlueprintCallable) void GetControllOptionMenu();
	UFUNCTION(BlueprintCallable) void SetSoundVolume(float Value);
	UFUNCTION(BlueprintCallable) void SetFOVVolume(float Value);
	UFUNCTION(BlueprintCallable) void ChangeHeadShake(bool Check);
	UFUNCTION(BlueprintCallable) void ChangeTrdCamera(bool Check);

		/*UFUNCTION(BlueprintCallable)	   X-Slash");
			void SlashButtonsFuntion();		   DownUpperCombo"
		UFUNCTION(BlueprintCallable)		White Fang");
		void SmashButtonsFuntion();
	UFUNCTION(BlueprintCallable)
		void StabButtonsFuntion();
	UFUNCTION(BlueprintCallable)
		void SpecialButtonsFuntion();*/

	

	UPROPERTY(EditAnywhere)
		ACastle_in_DungeonGameModeBase* MyGameMode;

	UPROPERTY(EditAnywhere)
		ARogueWeapon* RogueWeapon;

	UPROPERTY(EditAnywhere)
		ARogueState* MyRogueState;

	UPROPERTY(EditAnywhere)
		ARogue* MyRogue;
public:
	void WorldGameModeInit();
	void GetRogueHpValue(int32 SetHp);
	void GetRogueDataValue(int32 SetData);
	void GetRogueKarmaValue(int32 SetKarma);
	void GetRogueStatValue(float* SetData);
	void GetRogueEquipmentValue(FString* EquipmentValues, TCHAR** EquipmentAttackFormString, 
		TCHAR** EquipmentAttackFormRef, int32* EquipmentAttackForm, int32* EquipmentAttackFormIndex, 
		int32* EquipNumberData, float*OverlapData, float**TotalOverlapData);
	void GetRogueAbilityList(int32 AbilityListIndex, FString AbilityName);
	void GetRogueAbilityIndexAndString(int32 LastIndex, FString* AbilityName);
	void GetDialogue(FString*, int32);
	void AbilityListString();
	void WeaponListString();
	void AttackFormString();
	void ElementString();
	void Call_HaveWeaponList();
	void Call_HaveAttackFormList();
	void Call_HaveAbilityList();
	void Call_HaveElementalList();
	void Return_HaveWeaponList(bool*, float*);
	void Return_HaveAttackFormList(bool AttckForm[4][10], float AttackFormOverlap[4][10]);
	void Return_HaveAbilityList(bool*, float*);
	void Return_HaveElementalList(bool ElementalNumber[10], float ElementalOverlap[10]);
	void Receive_ReturnRogueUseWeaponRef(int32 UseWeaponNumber);

public:
	void ControllUIInit();
	void RevivalMenuInit();
	void TitleInRevivalMenuInit();
	void TitleMenuInit();
	void MainMenuInit();
	void ReSumeMenuInit();
	void TabMenuInit();
	void StatMenuInit();
	void EquipMenuInit();
	void BurningTotemMenuInit();
	void AddAbilityMenuInit();
	void ChangedWeaponMenuInit();
	void ChangedAttackMotionInit();
	void ChangedElementalInit();
	void DialogueMenuInit();
	void ButtonStyleInit();
	void WeaponImagesRefInit();
	void RogueUseWeaponRefCheck();
	void SetEquipmentStringsInit();
	void SetAttackForm(int32 Form, int32 FormIndex);
	void ToolTipInit();
	void ElementIconInit();
	void PageInit();
	void ElementalPhaseCheck();
	void DelegateInit();
	void TaskSetting();

public:
	int32 RogueHp;
	int32 RogueData;
	int32 RogueKarma;
	float RogueStatData[16];
	float AbilityCost = 1.f;

public:
	FString RogueHpString;
	FString RogueDataString;
	FString RogueKarmaString;
	FString RogueStat[22];
	FString RogueStatDataString[16];
	FString RogueEquipmentString[6];
	TCHAR* RogueEquipmentAttackFormString[3];
	TCHAR* RogueEquipmentAttackFormRef[3];
	FString RogueAbilityListString[24];
	FString RogueSelectAbilityString[4];
	FString RogueSelectClassesString[4];
	FString RogueHaveWeaponListString[10];
	FString RogueAttackFormListString[4][10];
	TCHAR* RogueAttackFormVideoString[4][10];
	FString RogueElementString[30];
	FSlateFontInfo Font;

public:
	bool PageTitle;
	bool PageMain;
	bool PageStat;
	bool PageEquip;
	bool TabMenuIn;
	bool GamePageOn;
	bool HaveWeaponList[10];
	bool HaveAttackFormList[4][10];
	float HaveAttackFormOverlap[4][10];
	bool HaveAbilityList[24];
	bool HaveElementalList[10];
	bool BonFireMenuIn;
	int32 HaveAbilityOverlap[24];

public:
	UFont* UseCinzelFont;
	UFont* UseNanumMyeonjo;
	UFont* UseCardo;
	TCHAR* CinzelDir;

	int32 AbilityLastIndex;
	int32 PreIndex;
	int32 SelectAbilityIndex[4];
	int32 WeaponNumberIndex;
	int32 UsedWeaponNumber;
	int32 AttackForm;
	int32 AttackFormIndex;
	int32 AttackFormMaxIndex;
	int32 SelectedAttackFormNumber[3];
	int32 SelectedAttackFormIndex[3];
	int32 SelectedAttackFormSlotNumber;
	int32 RogueEquipmentAttackForm[3];
	int32 RogueEquipmentAttackFormIndex[3];
	int32 AbilityRandIndex[4];
	int32 RogueEquipNumberData[3];
	int32 RogueWeaponElementalNumber;
	int32 RogueTorchElementalNumber;
	int32 WeaponElementalPhase;
	int32 TorchElementalPhase;
	float RogueOverlapData[6];
	float* TotalRogueOverlapData[6];
	UPROPERTY()
		float VolumeValue;
	
	FString* AbilityNames;
	FButtonStyle NewWeaponAndSkillButton;
	TCHAR* RogueUsedWeaponRef;
	TCHAR* WeaponImagesRef[10];
	UTexture2D* DefaultWeaponImage;
	UTexture2D* AbilityClassIcon[4];
	UTexture2D* ElementIcon[15];
	UTexture2D* SelectElementIcon[2][5];
	FString SelectElementString[2][5];
	FText IconToolTip[5];
	UMediaSource* AttackSource[3];
	UMediaPlayer* AttackFormPlayer[3];
	UMediaTexture* AttackFormTexture[3];
	UMediaSource* TestSource;
	UMediaPlayer* TestPlayer;
	
	USoundCue* SelectSound;
	//UTexture2D WeaponTexture;

};
