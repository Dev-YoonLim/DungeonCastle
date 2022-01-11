// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAnimInstance.h"
#include "Kismet/GameplayStatics.h"

URogueAnimInstance::URogueAnimInstance() {
	AnimationAllCheck = false;
	AnimationInit();
	AttackAnimationInit();
	AnimationWeaponTorchSpeedInit();
	EnemyRogueAnimationInit();
	RogueHitAnimationInit();
	AnimationAllCheck = true;
	
}

void URogueAnimInstance::NativeBeginPlay() {
	Super::NativeBeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("RogueAnimOn")));
	GetWorldGameModeBase();
	AttackAnimationDelegateInit();
	//AttackFormInit(); 
	EnemyRogueAttackFormIndex();
	//EnemyRogueAttackFormIndex();
	//EnemyRogueAttackFormSetting();
}

void URogueAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void URogueAnimInstance::GetWorldGameModeBase() {
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
}

void URogueAnimInstance::AttackAnimationDelegateInit() {
	MyGameMode->AttackAnimationChangeDelegate_.BindUObject(this, &URogueAnimInstance::AttackFormToChangeAnimReferens);
	MyGameMode->WeaponSpeedSynergyDelegate.BindUObject(this, &URogueAnimInstance::AnimationWeaponSpeedSetting);
	MyGameMode->TorchSpeedSynergyDelegate.BindUObject(this, &URogueAnimInstance::AnimationTorchSpeedSetting);
	//MyGameMode->Call_TakeAttackFormRefDelegate.BindUObject(this, &URogueAnimInstance::AttackFormToChangeAnimReferens);
}

void URogueAnimInstance::AnimationInit() {
	MovementAnimationInit();
	DaggerAttackAnimationInit();
	TorchAttackAnimationInit();
}

void URogueAnimInstance::AttackAnimationInit() { //여기에 각종 애니메이션 넣어야 함.

	//Montage_JumpToSection
	AttackFormList[0][0] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DefaultSlashMontage.DefaultSlashMontage'");
	SlashFormSynergy[0][0] = 0.5f;
	BreakFormSynergy[0][0] = 0.3f;
	StabFormSynergy[0][0] = 0.2f;
	AttackDirection[0][0][0] = 0;
	DoubleAttackForm[0][0] = false;

	AttackFormList[0][1] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DefaultSlashMontage_2.DefaultSlashMontage_2'");
	SlashFormSynergy[0][1] = 0.5f;
	BreakFormSynergy[0][1] = 0.3f;
	StabFormSynergy[0][1] = 0.2f;
	AttackDirection[0][1][0] = 0;
	DoubleAttackForm[0][1] = false;

	AttackFormList[0][2] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/BashSlashMontage.BashSlashMontage'");
	SlashFormSynergy[0][2] = 0.6f;
	BreakFormSynergy[0][2] = 0.5f;
	StabFormSynergy[0][2] = 0.2f;
	AttackDirection[0][2][0] = 0;
	DoubleAttackForm[0][2] = false;

	AttackFormList[0][3] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/UpperSlashMontage.UpperSlashMontage'");
	SlashFormSynergy[0][3] = 0.5f;
	BreakFormSynergy[0][3] = 0.4f;
	StabFormSynergy[0][3] = 0.2f;
	AttackDirection[0][3][0] = 1;
	DoubleAttackForm[0][3] = false;

	AttackFormList[0][4] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/XComboSlashMontage.XComboSlashMontage'");
	SlashFormSynergy[0][4] = 0.4f;
	BreakFormSynergy[0][4] = 0.2f;
	StabFormSynergy[0][4] = 0.1f;
	AttackDirection[0][4][0] = 0;
	AttackDirection[0][4][1] = 0;
	DoubleAttackForm[0][4] = true;

	AttackFormList[0][5] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DownAndUpperMontage.DownAndUpperMontage'");
	SlashFormSynergy[0][5] = 0.5f;
	BreakFormSynergy[0][5] = 0.4f;
	StabFormSynergy[0][5] = 0.2f;
	AttackDirection[0][5][0] = 0;
	AttackDirection[0][5][1] = 1;
	DoubleAttackForm[0][5] = true;

	AttackFormList[0][6] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/UpperAndBashMontage.UpperAndBashMontage'");
	SlashFormSynergy[0][6] = 0.6f;
	BreakFormSynergy[0][6] = 0.4f;
	StabFormSynergy[0][6] = 0.2f;
	AttackDirection[0][6][0] = 0;
	AttackDirection[0][6][1] = 1;
	DoubleAttackForm[0][6] = true;
	//--------------------------------------------------------

	AttackFormList[1][0] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Break/DefaultBreakMontage.DefaultBreakMontage'");
	SlashFormSynergy[1][0] = 0.4f;
	BreakFormSynergy[1][0] = 0.6f;
	StabFormSynergy[1][0] = 0.1f;
	AttackDirection[1][0][0] = 0;
	DoubleAttackForm[1][0] = false;

	AttackFormList[1][1] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Break/DefaultPowerBreakMontage.DefaultPowerBreakMontage'");
	SlashFormSynergy[1][1] = 0.5f;
	BreakFormSynergy[1][1] = 0.7f;
	StabFormSynergy[1][1] = 0.1f;
	AttackDirection[1][1][0] = 0;
	DoubleAttackForm[1][1] = false;

	AttackFormList[1][2] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Break/MiddleBreakMontage.MiddleBreakMontage'");
	SlashFormSynergy[1][2] = 0.3f;
	BreakFormSynergy[1][2] = 0.7f;
	StabFormSynergy[1][2] = 0.1f;
	AttackDirection[1][2][0] = 1;
	DoubleAttackForm[1][2] = false;

	AttackFormList[1][3] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Break/PowerMiddleBreakMontage.PowerMiddleBreakMontage'");
	SlashFormSynergy[1][3] = 0.3f;
	BreakFormSynergy[1][3] = 0.8f;
	StabFormSynergy[1][3] = 0.1f;
	AttackDirection[1][3][0] = 1;
	DoubleAttackForm[1][3] = false;

	/*AttackFormList[1][4] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Break/FastGroundBreakMontage.FastGroundBreakMontage'");
	SlashFormSynergy[1][4] = 0.1f;
	BreakFormSynergy[1][4] = 0.8f;
	StabFormSynergy[1][4] = 0.1f;
	AttackDirection[1][4][0] = 0;
	DoubleAttackForm[1][4] = false;*/

	AttackFormList[1][4] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Break/GroundBreakMontage.GroundBreakMontage'");
	SlashFormSynergy[1][4] = 0.2f;
	BreakFormSynergy[1][4] = 0.9f;
	StabFormSynergy[1][4] = 0.2f;
	AttackDirection[1][4][0] = 0;
	DoubleAttackForm[1][4] = false;

	AttackFormList[1][5] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Break/LeftMiddleBreakMontage.LeftMiddleBreakMontage'");
	SlashFormSynergy[1][5] = 0.4f;
	BreakFormSynergy[1][5] = 0.5f;
	StabFormSynergy[1][5] = 0.2f;
	AttackDirection[1][5][0] = 2;
	DoubleAttackForm[1][5] = false;

	AttackFormList[1][6] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Break/DefaultAndLeftBreakMontage.DefaultAndLeftBreakMontage'");
	SlashFormSynergy[1][6] = 0.4f;
	BreakFormSynergy[1][6] = 0.6f;
	StabFormSynergy[1][6] = 0.2f;
	AttackDirection[1][6][0] = 0;
	AttackDirection[1][6][1] = 2;
	DoubleAttackForm[1][0] = true;

	AttackFormList[1][7] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Break/RightLeftBreakMontage.RightLeftBreakMontage'");
	SlashFormSynergy[1][7] = 0.4f;
	BreakFormSynergy[1][7] = 0.6f;
	StabFormSynergy[1][7] = 0.3f;
	AttackDirection[1][7][0] = 2;
	AttackDirection[1][7][1] = 1;
	DoubleAttackForm[1][0] = true;

	//-----------------------------------------------

	AttackFormList[2][0] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/DefaultStabMontage.DefaultStabMontage'");
	SlashFormSynergy[2][0] = 0.2f;
	BreakFormSynergy[2][0] = 0.1f;
	StabFormSynergy[2][0] = 0.6f;
	AttackDirection[2][0][0] = 1;
	DoubleAttackForm[2][0] = false;

	AttackFormList[2][1] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/DefaultQuickStabMontage.DefaultQuickStabMontage'");
	SlashFormSynergy[2][1] = 0.2f;
	BreakFormSynergy[2][1] = 0.1f;
	StabFormSynergy[2][1] = 0.6f;
	AttackDirection[2][1][0] = 1;
	DoubleAttackForm[2][1] = false;

	AttackFormList[2][2] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/DeepStabMontage.DeepStabMontage'");
	SlashFormSynergy[2][2] = 0.2f;
	BreakFormSynergy[2][2] = 0.1f;
	StabFormSynergy[2][2] = 0.9f;
	AttackDirection[2][2][0] = 0;
	DoubleAttackForm[2][2] = false;

	AttackFormList[2][3] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/SideHookStabMontage.SideHookStabMontage'");
	SlashFormSynergy[2][3] = 0.3f;
	BreakFormSynergy[2][3] = 0.2f;
	StabFormSynergy[2][3] = 0.6f;
	AttackDirection[2][3][0] = 2;
	DoubleAttackForm[2][3] = false;

	AttackFormList[2][4] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/UpperStabMontage.UpperStabMontage'");
	SlashFormSynergy[2][4] = 0.3f;
	BreakFormSynergy[2][4] = 0.2f;
	StabFormSynergy[2][4] = 0.6f;
	AttackDirection[2][4][0] = 1;
	DoubleAttackForm[2][4] = false;

	AttackFormList[2][5] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/OneInchStabMontage.OneInchStabMontage'");
	SlashFormSynergy[2][5] = 0.4f;
	BreakFormSynergy[2][5] = 0.4f;
	StabFormSynergy[2][5] = 0.9f;
	AttackDirection[2][5][0] = 0;
	DoubleAttackForm[2][5] = false;

	AttackFormList[2][6] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/DoubleStabMontage.DoubleStabMontage'");
	SlashFormSynergy[2][6] = 0.1f;
	BreakFormSynergy[2][6] = 0.1f;
	StabFormSynergy[2][6] = 0.6f;
	AttackDirection[2][6][0] = 1;
	AttackDirection[2][6][1] = 1;
	DoubleAttackForm[2][2] = true;

	AttackFormList[2][7] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/StabAndHookMontage.StabAndHookMontage'");
	SlashFormSynergy[2][7] = 0.3f;
	BreakFormSynergy[2][7] = 0.2f;
	StabFormSynergy[2][7] = 0.6f;
	AttackDirection[2][7][0] = 1;
	AttackDirection[2][7][1] = 2;
	DoubleAttackForm[2][7] = true;

	AttackFormList[2][8] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/StabAndUpperMontage.StabAndUpperMontage'");
	SlashFormSynergy[2][8] = 0.2f;
	BreakFormSynergy[2][8] = 0.3f;
	StabFormSynergy[2][8] = 0.6f;
	AttackDirection[2][8][0] = 1;
	AttackDirection[2][8][1] = 1;
	DoubleAttackForm[2][8] = true;

	AttackFormList[2][9] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Stab/HookAndUpperMontage.HookAndUpperMontage'");
	SlashFormSynergy[2][9] = 0.3f;
	BreakFormSynergy[2][9] = 0.3f;
	StabFormSynergy[2][9] = 0.5f;
	AttackDirection[2][9][0] = 2;
	AttackDirection[2][9][1] = 1;
	DoubleAttackForm[2][9] = true;

	//--------------------------------

	AttackFormList[3][0] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/SAndB/AirTrackSAndBMontage.AirTrackSAndBMontage'");
	SlashFormSynergy[3][0] = 0.6f;
	BreakFormSynergy[3][0] = 0.8f;
	StabFormSynergy[3][0] = 0.3f;
	AttackDirection[3][0][0] = 0;
	DoubleAttackForm[3][0] = false;

	AttackFormList[3][1] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/SAndB/TurnLowSAndBMontage.TurnLowSAndBMontage'");
	SlashFormSynergy[3][1] = 0.6f;
	BreakFormSynergy[3][1] = 0.7f;
	StabFormSynergy[3][1] = 0.2f;
	AttackDirection[3][1][0] = 2;
	DoubleAttackForm[3][1] = false;

	AttackFormList[3][2] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/SAndB/TurnSlashSAndBMontage.TurnSlashSAndBMontage'");
	SlashFormSynergy[3][2] = 0.7f;
	BreakFormSynergy[3][2] = 0.6f;
	StabFormSynergy[3][2] = 0.2f;
	AttackDirection[3][2][0] = 2;
	DoubleAttackForm[3][2] = false;

}

void URogueAnimInstance::RogueHitAnimationInit() {
	RogueUpHit1 = EnemyUpHit1;
	RogueUpHit2 = EnemyUpHit2;
	RogueSideHit1 = EnemySideHit1;
	RogueSideAndDownHit1 = EnemySideAndDownHit1;
	RogueDownHit1 = EnemyDownHit1;
	RogueSideAndUpHit1 = EnemySideAndUpHit1;
}

void URogueAnimInstance::MovementAnimationInit() {
	auto WalkMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/BP_WalkMontage.BP_WalkMontage'"));
	auto IdleMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/BP_IdleMontage.BP_IdleMontage'"));
	auto WalkRightMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/BP_WalkRight.BP_WalkRight'"));
	auto WalkLeftMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/BP_WalkLeft.BP_WalkLeft'"));
	auto DeshMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/BP_DeshMontage.BP_DeshMontage'"));
	auto DeshRightMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/BP_DeshRight.BP_DeshRight'"));
	auto DeshLeftMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/BP_DeshLeft.BP_DeshLeft'"));
	auto WalkBackMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/BP_WalkBackMontage.BP_WalkBackMontage'"));
	auto DeshBackMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/BP_DeshBackMontage.BP_DeshBackMontage'"));
	auto Roll_DodgeAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/Animation/Roll/FrontStep.FrontStep'"));
	auto Roll_BackDodgetAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/Animation/Roll/BackStep.BackStep'"));
	auto DodgeStep_RightAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/Animation/Roll/RStep.RStep'"));
	auto DodgeStep_LeftAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/Animation/Roll/LStep.LStep'"));
	
	
	if (WalkMontageAsset.Succeeded())
		WalkMontage = WalkMontageAsset.Object;
	if (DeshMontageAsset.Succeeded()) 
		DeshMontage = DeshMontageAsset.Object;
	if (IdleMontageAsset.Succeeded()) 
		IdleMontage = IdleMontageAsset.Object;
	if (WalkRightMontageAsset.Succeeded()) 
		WalkRightMontage = WalkRightMontageAsset.Object;
	if (WalkLeftMontageAsset.Succeeded()) 
		WalkLeftMontage = WalkLeftMontageAsset.Object;
	if (DeshRightMontageAsset.Succeeded()) 
		DeshRightMontage = DeshRightMontageAsset.Object;
	if (DeshLeftMontageAsset.Succeeded()) 
		DeshLeftMontage = DeshLeftMontageAsset.Object;
	if (WalkBackMontageAsset.Succeeded()) 
		WalkBackMontage = WalkBackMontageAsset.Object;
	if (DeshBackMontageAsset.Succeeded()) 
		DeshBackMontage = DeshBackMontageAsset.Object;
	if (Roll_DodgeAsset.Succeeded()) 
		Roll_Montage = Roll_DodgeAsset.Object;
	if (Roll_BackDodgetAsset.Succeeded()) 
		Roll_BackMontage = Roll_BackDodgetAsset.Object;
	if (DodgeStep_RightAsset.Succeeded())
		Dodge_Right = DodgeStep_RightAsset.Object;
	if (DodgeStep_LeftAsset.Succeeded())
		Dodge_Left = DodgeStep_LeftAsset.Object;
}

void URogueAnimInstance::DaggerAttackAnimationInit() {
	auto AttackOneMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DefaultSlashMontage.DefaultSlashMontage'"));
	auto AttackTwoMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DefaultSlashMontage.DefaultSlashMontage'"));
	auto AttackThreeMontageAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DefaultSlashMontage.DefaultSlashMontage'"));

	if (AttackOneMontageAsset.Succeeded()) 
		AttackOneMontage = AttackOneMontageAsset.Object;
	if (AttackTwoMontageAsset.Succeeded()) 
		AttackTwoMontage = AttackTwoMontageAsset.Object;
	if (AttackThreeMontageAsset.Succeeded()) 
		AttackThreeMontage = AttackThreeMontageAsset.Object;

	SelectAttackForm[0] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DefaultSlashMontage.DefaultSlashMontage'");
	SelectAttackForm[1] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DefaultSlashMontage.DefaultSlashMontage'");
	SelectAttackForm[2] = TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DefaultSlashMontage.DefaultSlashMontage'");
}

void URogueAnimInstance::TorchAttackAnimationInit() {
	auto TorchAttackAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/Animation/Attack/Torch/Torch_Stab.Torch_Stab'"));

	if (TorchAttackAsset.Succeeded())
		TorchAttackMontage = TorchAttackAsset.Object;

	auto TestAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/Character/Animation/Attack/ThreeForm/Slash/DefaultSlashMontage.DefaultSlashMontage'"));
	if (TestAsset.Succeeded()) {
		AttackTestMontage = TestAsset.Object;
	}
}

void URogueAnimInstance::AttackFormSetting() {
	ChangeAttackThreeMontage = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, SelectAttackForm[2]));
	if (ChangeAttackThreeMontage)
		AttackThreeMontage = ChangeAttackThreeMontage;
	ChangeAttackTwoMontage = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, SelectAttackForm[1]));
	if (ChangeAttackTwoMontage)
		AttackTwoMontage = ChangeAttackTwoMontage;
	ChangeAttackOneMontage = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, SelectAttackForm[0]));
	if (ChangeAttackOneMontage) {
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Blue, FString::Printf(TEXT("AttackFormSetting")));
		AttackOneMontage = ChangeAttackOneMontage; // 동적으로 오브젝트 바꾸는 코드
	}
}

void URogueAnimInstance::AnimationWeaponTorchSpeedInit() {
	AttackOneMontage->RateScale = 1.f;
	AttackTwoMontage->RateScale = 1.f;
	AttackThreeMontage->RateScale = 1.f;
	TorchAttackMontage->RateScale = 1.0f;
	AttackTestMontage->RateScale = 1.0f;
}

void URogueAnimInstance::AttackFormToChangeAnimReferens(int32 AttackFormZero, int32 AttackFormIndexZero,
	int32 AttackFormOne, int32 AttackFormIndexOne, int32 AttackFormTwo, int32 AttackFormIndexTwo) {

		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Green, FString::Printf(TEXT("%d___%d"), AttackFormZero, AttackFormIndexZero));
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Green, FString::Printf(TEXT("%d___%d"), AttackFormOne, AttackFormIndexOne));
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Green, FString::Printf(TEXT("%d___%d"), AttackFormTwo, AttackFormIndexTwo));

		SelectAttackForm[2] = AttackFormList[AttackFormTwo][AttackFormIndexTwo];
		SelectFormSynergy[2][0] = SlashFormSynergy[AttackFormTwo][AttackFormIndexTwo];
		SelectFormSynergy[2][1] = BreakFormSynergy[AttackFormTwo][AttackFormIndexTwo];
		SelectFormSynergy[2][2] = StabFormSynergy[AttackFormTwo][AttackFormIndexTwo];
		CheckDoubleForm[2] = DoubleAttackForm[AttackFormTwo][AttackFormIndexTwo];
		if (CheckDoubleForm[2] == true) {
			CheckAttackDirection[2][0] = AttackDirection[AttackFormTwo][AttackFormIndexTwo][0];
			CheckAttackDirection[2][1] = AttackDirection[AttackFormTwo][AttackFormIndexTwo][1];
		}
		else {
			CheckAttackDirection[2][0] = AttackDirection[AttackFormTwo][AttackFormIndexTwo][0];
			CheckAttackDirection[2][1] = AttackDirection[AttackFormTwo][AttackFormIndexTwo][0];
		}
		SelectAttackForm[1] = AttackFormList[AttackFormOne][AttackFormIndexOne];
		SelectFormSynergy[1][0] = SlashFormSynergy[AttackFormOne][AttackFormIndexOne];
		SelectFormSynergy[1][1] = BreakFormSynergy[AttackFormOne][AttackFormIndexOne];
		SelectFormSynergy[1][2] = StabFormSynergy[AttackFormOne][AttackFormIndexOne];
		CheckDoubleForm[1] = DoubleAttackForm[AttackFormOne][AttackFormIndexOne];
		if (CheckDoubleForm[1] == true) {
			CheckAttackDirection[1][0] = AttackDirection[AttackFormOne][AttackFormIndexOne][0];
			CheckAttackDirection[1][1] = AttackDirection[AttackFormOne][AttackFormIndexOne][1];
		}
		else {
			CheckAttackDirection[1][0] = AttackDirection[AttackFormOne][AttackFormIndexOne][0];
			CheckAttackDirection[1][1] = AttackDirection[AttackFormOne][AttackFormIndexOne][0];
		}
		SelectAttackForm[0] = AttackFormList[AttackFormZero][AttackFormIndexZero];
		SelectFormSynergy[0][0] = SlashFormSynergy[AttackFormZero][AttackFormIndexZero];
		SelectFormSynergy[0][1] = BreakFormSynergy[AttackFormZero][AttackFormIndexZero];
		SelectFormSynergy[0][2] = StabFormSynergy[AttackFormZero][AttackFormIndexZero];
		CheckDoubleForm[0] = DoubleAttackForm[AttackFormZero][AttackFormIndexZero];
		if (CheckDoubleForm[2] == true) {
			CheckAttackDirection[0][0] = AttackDirection[AttackFormZero][AttackFormIndexZero][0];
			CheckAttackDirection[0][1] = AttackDirection[AttackFormZero][AttackFormIndexZero][1];
		}
		else {
			CheckAttackDirection[0][0] = AttackDirection[AttackFormZero][AttackFormIndexZero][0];
			CheckAttackDirection[0][1] = AttackDirection[AttackFormZero][AttackFormIndexZero][0];
		}
	float* ConvertSelectFormSynergy;
	bool* ConvertCheckDoubleAttack;
	int32* ConvertCheckAttackDirection;
	ConvertSelectFormSynergy = (float*)SelectFormSynergy;
	ConvertCheckDoubleAttack = (bool*)CheckDoubleForm;
	ConvertCheckAttackDirection = (int32*)CheckAttackDirection;
	MyGameMode->Call_TakeAttackFormRefDelegate.ExecuteIfBound(SelectAttackForm);
	MyGameMode->AttackFormSynergyDelegate.ExecuteIfBound(ConvertSelectFormSynergy, ConvertCheckDoubleAttack, CheckAttackDirection);
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Purple, FString::Printf(TEXT("AttackFormChange")));
	AttackFormSetting();
	//AnimationWeaponSpeedSetting(WeaponSpeedSynergys, WeaponLevelValue);
}



void URogueAnimInstance::AnimationWeaponSpeedSetting(float WeaponSpeed, float WeaponSpeedValue, float WeaponLevelValue) {
	float AttackRate = 1.f * (WeaponSpeed * WeaponSpeedValue * WeaponLevelValue);
	AttackOneMontage->RateScale = AttackRate;
	//Montage_SetPlayRate(AttackOneMontage, AttackRate);
	
	AttackTwoMontage->RateScale = AttackRate;
	//Montage_SetPlayRate(AttackTwoMontage, AttackRate);
	
	AttackThreeMontage->RateScale = AttackRate;
	//Montage_SetPlayRate(AttackThreeMontage, AttackRate);
	
	float TakeHitRate = 1.f * WeaponSpeed - 0.15;
	EnemyUpHit1->RateScale = TakeHitRate;
	//Montage_SetPlayRate(EnemyUpHit1, TakeHitRate);
	
	EnemyUpHit2->RateScale = TakeHitRate;
	//Montage_SetPlayRate(EnemyUpHit2, TakeHitRate);
	
	EnemySideHit1->RateScale = TakeHitRate;
	//Montage_SetPlayRate(EnemySideHit1, TakeHitRate);
	
	EnemySideAndDownHit1->RateScale = TakeHitRate;
	//Montage_SetPlayRate(EnemySideAndDownHit1, TakeHitRate);
	
	EnemyDownHit1->RateScale = TakeHitRate;
	//Montage_SetPlayRate(EnemyDownHit1, TakeHitRate);
	
	EnemySideAndUpHit1->RateScale = TakeHitRate;
	//Montage_SetPlayRate(EnemySideAndUpHit1, TakeHitRate);

	EnemyTorchUpHit1->RateScale = TorchAttackMontage->RateScale;
	EnemyTorchUpHit2->RateScale = TorchAttackMontage->RateScale;
	EnemyTorchSideAndDownHit1->RateScale = TorchAttackMontage->RateScale;
	EnemyTorchDownHit1->RateScale = TorchAttackMontage->RateScale;
	EnemyTorchSideAndUpHit1->RateScale = TorchAttackMontage->RateScale;
}

void URogueAnimInstance::AnimationTorchSpeedSetting(float TorchLevelValue) {
	TorchAttackMontage->RateScale = 1.f * TorchLevelValue;
}

void URogueAnimInstance::Attack(int AttackQue) {
	
	AttackFormSetting();
	switch (AttackQue) {
	case 0:
		Montage_Play(AttackOneMontage);
		break;
	case 1:
		Montage_Play(AttackTwoMontage);
		break;
	case 2:
		Montage_Play(AttackThreeMontage);
		break;
	case 4:
		Montage_Play(TorchAttackMontage);
		break;
	}

	
}

void URogueAnimInstance::Idle() {
	if (Montage_IsPlaying(IdleMontage) == false) {
		Montage_Play(IdleMontage);
	}
}

void URogueAnimInstance::Walking(bool right, bool left, bool forward, bool back, bool roll) {
	if (right == false && left == false && roll == false) {
		if (back == false && forward == true) {
			if (Montage_IsPlaying(WalkMontage) == false) {
				
				Montage_Play(WalkMontage);
			}
		}
		else if(back == true && forward == false){
			if (Montage_IsPlaying(WalkBackMontage) == false) {
				Montage_Play(WalkBackMontage);
			}
		}
	}
	else if (right == true && left == false && roll == false) {
		if (Montage_IsPlaying(WalkRightMontage) == false) {
			
			Montage_Play(WalkRightMontage);
		}
	}
	else if (right == false && left == true && roll == false) {
		if (Montage_IsPlaying(WalkLeftMontage) == false) {
			Montage_Play(WalkLeftMontage);
		}
	}
}

void URogueAnimInstance::Desh(bool right, bool left, bool forward, bool back, bool roll) {
	if (right == false && left == false && roll == false) {
		if (back == false) {
			if (Montage_IsPlaying(DeshMontage) == false) {
				Montage_Play(DeshMontage);
			}
		}
		else {
			if (Montage_IsPlaying(DeshBackMontage) == false) {
				Montage_Play(DeshBackMontage);
			}
		}
	}
	else if (right == true && left == false && roll == false) {
		if (Montage_IsPlaying(DeshRightMontage) == false) {
			
			Montage_Play(DeshRightMontage);
		}
	}
	else if (right == false && left == true && roll == false) {
		if (Montage_IsPlaying(DeshLeftMontage) == false) {
			Montage_Play(DeshLeftMontage);
		}
	}
}

void URogueAnimInstance::Roll() {
	MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(10);
	Montage_Play(Roll_Montage);
}

void URogueAnimInstance::BackStep() {
	MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(10);
	Montage_Play(Roll_BackMontage);
}

void URogueAnimInstance::RightStep() {
	MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(10);
	Montage_Play(Dodge_Right);
}

void URogueAnimInstance::LeftStep() {
	MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(10);
	Montage_Play(Dodge_Left);
}

void URogueAnimInstance::AttackFormInit() {
	MyGameMode->Call_GameStartAttackFormNumberDelegate.ExecuteIfBound();
}




void URogueAnimInstance::EnemyRogueAnimationInit() {
	EnemyRoguePlayHitAnimationInit();
	EnemyRoguePlayMovementAnimationInit();
	EnemyRoguePlayIdleAnimationInit();
	EnemyRoguePlayDeathAnimation();
	EnemyRogueAttackRefInit();
}

void URogueAnimInstance::EnemyRoguePlayHitAnimationInit(){

	auto EnemyUpHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Weapon/UpHitMontage.UpHitMontage'"));
	auto EnemyUpHit2Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Weapon/UpHitMontage2.UpHitMontage2'"));
	auto EnemySideHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Weapon/SideHitMontage.SideHitMontage'"));
	auto EnemySideAndDownHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Weapon/SideRightDownHitMontage.SideRightDownHitMontage'"));
	auto EnemyDownHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Weapon/DownHitMontage.DownHitMontage'"));
	auto EnemySideAndUpHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Weapon/UpSIdeHitMontage.UpSIdeHitMontage'"));
	if (EnemyUpHit1Asset.Succeeded())
		EnemyUpHit1 = EnemyUpHit1Asset.Object;
	if (EnemyUpHit2Asset.Succeeded())
		EnemyUpHit2 = EnemyUpHit2Asset.Object;
	if (EnemySideHit1Asset.Succeeded())
		EnemySideHit1 = EnemySideHit1Asset.Object;
	if (EnemySideAndDownHit1Asset.Succeeded())
		EnemySideAndDownHit1 = EnemySideAndDownHit1Asset.Object;
	if (EnemyDownHit1Asset.Succeeded())
		EnemyDownHit1 = EnemyDownHit1Asset.Object;
	if (EnemySideAndUpHit1Asset.Succeeded())
		EnemySideAndUpHit1 = EnemySideAndUpHit1Asset.Object;

	auto EnemyTorchUpHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Torch/UpHitMontage.UpHitMontage'"));
	auto EnemyTorchUpHit2Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Torch/UpHitMontage2.UpHitMontage2'"));
	auto EnemyTorchSideAndDownHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Torch/SideRightDownHitMontage.SideRightDownHitMontage'"));
	auto EnemyTorchDownHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Torch/DownHitMontage.DownHitMontage'"));
	auto EnemyTorchSideAndUpHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/TakeHit/Torch/UpSIdeHitMontage.UpSIdeHitMontage'"));
	if (EnemyTorchUpHit1Asset.Succeeded())
		EnemyTorchUpHit1 = EnemyTorchUpHit1Asset.Object;
	if (EnemyTorchUpHit2Asset.Succeeded())
		EnemyTorchUpHit2 = EnemyTorchUpHit2Asset.Object;
	if (EnemyTorchSideAndDownHit1Asset.Succeeded())
		EnemyTorchSideAndDownHit1 = EnemyTorchSideAndDownHit1Asset.Object;
	if (EnemyTorchDownHit1Asset.Succeeded())
		EnemyTorchDownHit1 = EnemyTorchDownHit1Asset.Object;
	if (EnemyTorchSideAndUpHit1Asset.Succeeded())
		EnemyTorchSideAndUpHit1 = EnemyTorchSideAndUpHit1Asset.Object;
}

void URogueAnimInstance::EnemyRoguePlayIdleAnimationInit() {
	auto EnemyNormalIdleAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Idle/EnemyRogueIdle01.EnemyRogueIdle01'"));
	auto EnemyCombatIdleAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Idle/EnemyRogueCombatIdle02.EnemyRogueCombatIdle02'"));
	auto EnemySadIdleAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Idle/EnemyRogueSadIdle01.EnemyRogueSadIdle01'"));
	auto EnemyConfusedAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Idle/EnemyRogueConfused.EnemyRogueConfused'"));
	
	if (EnemyNormalIdleAsset.Succeeded())
		EnemyNormalIdle = EnemyNormalIdleAsset.Object;
	if (EnemyCombatIdleAsset.Succeeded())
		EnemyCombatIdle = EnemyCombatIdleAsset.Object;
	if (EnemySadIdleAsset.Succeeded())
		EnemySadIdle = EnemySadIdleAsset.Object;
	if (EnemyConfusedAsset.Succeeded()) {
		EnemyConfused = EnemyConfusedAsset.Object;
	}
}

void URogueAnimInstance::EnemyRoguePlayMovementAnimationInit() {
	auto EnemyForwardWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Normal/EnemyRogueNormalWalk01.EnemyRogueNormalWalk01'"));
	auto EnemyBackWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Normal/EnemyRogueNormalBackWalk01.EnemyRogueNormalBackWalk01'"));
	auto EnemyRightWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Normal/EnemyRogueNormalRightWalk01.EnemyRogueNormalRightWalk01'"));
	auto EnemyLeftWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Normal/EnemyRogueNormalLeftWalk01.EnemyRogueNormalLeftWalk01'"));
	if (EnemyForwardWalkAsset.Succeeded())
		EnemyForwardWalk = EnemyForwardWalkAsset.Object;
	if (EnemyBackWalkAsset.Succeeded())
		EnemyBackWalk = EnemyBackWalkAsset.Object;
	if (EnemyRightWalkAsset.Succeeded())
		EnemyRightWalk = EnemyRightWalkAsset.Object;
	if (EnemyLeftWalkAsset.Succeeded())
		EnemyLeftWalk = EnemyLeftWalkAsset.Object;

	auto EnemyCombatForwardWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Combat/EnemyRogueCombatWalk01.EnemyRogueCombatWalk01'"));
	auto EnemyCombatBackWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Combat/EnemyRogueCombatBackWalk01.EnemyRogueCombatBackWalk01'"));
	auto EnemyCombatRightWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Combat/EnemyRogueCombatRightWalk01.EnemyRogueCombatRightWalk01'"));
	auto EnemyCombatLeftWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Combat/EnemyRogueCombatLeftWalk01.EnemyRogueCombatLeftWalk01'"));
	if (EnemyCombatForwardWalkAsset.Succeeded())
		EnemyCombatForwardWalk = EnemyCombatForwardWalkAsset.Object;
	if (EnemyCombatBackWalkAsset.Succeeded())
		EnemyCombatBackWalk = EnemyCombatBackWalkAsset.Object;
	if (EnemyCombatRightWalkAsset.Succeeded())
		EnemyCombatRightWalk = EnemyCombatRightWalkAsset.Object;
	if (EnemyCombatLeftWalkAsset.Succeeded())
		EnemyCombatLeftWalk = EnemyCombatLeftWalkAsset.Object;

	auto EnemySadForwardWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Sad/EnemyRogueSadWalk01.EnemyRogueSadWalk01'"));
	auto EnemySadBackWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Sad/EnemyRogueSadBackWalk01.EnemyRogueSadBackWalk01'"));
	auto EnemySadRightWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Sad/EnemyRogueSadRightWalk01.EnemyRogueSadRightWalk01'"));
	auto EnemySadLeftWalkAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Walk/Sad/EnemyRogueSadLeftWalk01.EnemyRogueSadLeftWalk01'"));
	if (EnemySadForwardWalkAsset.Succeeded())
		EnemySadForwardWalk = EnemySadForwardWalkAsset.Object;
	if (EnemySadBackWalkAsset.Succeeded())
		EnemySadBackWalk = EnemySadBackWalkAsset.Object;
	if (EnemySadRightWalkAsset.Succeeded())
		EnemySadRightWalk = EnemySadRightWalkAsset.Object;
	if (EnemySadLeftWalkAsset.Succeeded())
		EnemySadLeftWalk = EnemySadLeftWalkAsset.Object;

	auto EnemyRollAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Roll/EnemyRolling.EnemyRolling'"));
	if(EnemyRollAsset.Succeeded())
		EnemyRoll = EnemyRollAsset.Object;
	auto EnemyBackRollAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Roll/EnemyRolling_2.EnemyRolling_2'"));
	if (EnemyBackRollAsset.Succeeded())
		EnemyBackRoll = EnemyBackRollAsset.Object;
}

void URogueAnimInstance::EnemyRoguePlayDeathAnimation() {
	auto EnemyDownDeath1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/EnemyRogueDeathDown01_Death02.EnemyRogueDeathDown01_Death02'"));
	auto EnemyDownDeath2Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/EnemyRogueDeathDown02_Death04.EnemyRogueDeathDown02_Death04'"));
	auto EnemyDownDeath3Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/EnemyRogueDeathDown03_Death06.EnemyRogueDeathDown03_Death06'"));
	auto EnemyUpDeath1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/EnemyRogueDeathUp01_Death01.EnemyRogueDeathUp01_Death01'"));
	auto EnemyUpDeath2Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/EnemyRogueDeathUp02_Death03.EnemyRogueDeathUp02_Death03'"));
	auto EnemyUpDeath3Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/EnemyRogueDeathUpSide03_Death07.EnemyRogueDeathUpSide03_Death07'"));
	if (EnemyDownDeath1Asset.Succeeded())
		EnemyDownDeath1[0] = EnemyDownDeath1Asset.Object;
	if (EnemyDownDeath2Asset.Succeeded())
		EnemyDownDeath2[0] = EnemyDownDeath2Asset.Object;
	if (EnemyDownDeath3Asset.Succeeded())
		EnemyDownDeath3[0] = EnemyDownDeath3Asset.Object;
	if (EnemyUpDeath1Asset.Succeeded())
		EnemyUpDeath1[0] = EnemyUpDeath1Asset.Object;
	if (EnemyUpDeath2Asset.Succeeded())
		EnemyUpDeath2[0] = EnemyUpDeath2Asset.Object;
	if (EnemyUpDeath3Asset.Succeeded())
		EnemyUpDeath3[0] = EnemyUpDeath3Asset.Object;

	auto EnemyDownDeath1IdleAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/DeathIdle/EnemyRogueDeathDown01_Idle.EnemyRogueDeathDown01_Idle'"));
	auto EnemyDownDeath2IdleAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/DeathIdle/EnemyRogueDeathDown02Idle.EnemyRogueDeathDown02Idle'"));
	auto EnemyDownDeath3IdleAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/DeathIdle/EnemyRogueDeathDown03Idle.EnemyRogueDeathDown03Idle'"));
	auto EnemyUpDeath1IdleAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/DeathIdle/EnemyRogueDeathUp01Idle.EnemyRogueDeathUp01Idle'"));
	auto EnemyUpDeath2IdleAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/DeathIdle/EnemyRogueDeathUp02Idle.EnemyRogueDeathUp02Idle'"));
	auto EnemyUpDeath3IdleAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Death/DeathIdle/EnemyRogueDeathUpSide03Idle.EnemyRogueDeathUpSide03Idle'"));
	if (EnemyDownDeath1IdleAsset.Succeeded())
		EnemyDownDeath1[1] = EnemyDownDeath1IdleAsset.Object;
	if (EnemyDownDeath2IdleAsset.Succeeded())
		EnemyDownDeath2[1] = EnemyDownDeath2IdleAsset.Object;
	if (EnemyDownDeath3IdleAsset.Succeeded())
		EnemyDownDeath3[1] = EnemyDownDeath3IdleAsset.Object;
	if (EnemyUpDeath1IdleAsset.Succeeded())
		EnemyUpDeath1[1] = EnemyUpDeath1IdleAsset.Object;
	if (EnemyUpDeath2IdleAsset.Succeeded())
		EnemyUpDeath2[1] = EnemyUpDeath2IdleAsset.Object;
	if (EnemyUpDeath3IdleAsset.Succeeded())
		EnemyUpDeath3[1] = EnemyUpDeath3IdleAsset.Object;
}

void URogueAnimInstance::EnemyRogueAttackRefInit() {
	EnemyAttackFormRef[0] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Slash/Slash1.Slash1'"));
	EnemyAttackFormRef[1] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Slash/Slash1_2.Slash1_2'"));
	EnemyAttackFormRef[2] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Slash/Slash1_3.Slash1_3'"));
	EnemyAttackFormRef[3] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Slash/Slash1_4.Slash1_4'"));
	EnemyAttackFormRef[4] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Slash/Slash1_5.Slash1_5'"));

	EnemyAttackFormRef[5] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Smash/Smash1.Smash1'"));
	EnemyAttackFormRef[6] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Smash/Smash1_2.Smash1_2'"));
	EnemyAttackFormRef[7] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Smash/Smash1_3.Smash1_3'"));
	EnemyAttackFormRef[8] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Smash/Smash1_4.Smash1_4'"));
	//EnemyAttackFormRef[9] =
		//(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Smash/Smash1_5.Smash1_5'"));
	EnemyAttackFormRef[9] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Smash/Smash1_6.Smash1_6'"));

	/*EnemyAttackFormRef[2][0] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Stab/Stab1.Stab1'"));
	EnemyAttackFormRef[2][1] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Stab/Stab1_2.Stab1_2'"));
	EnemyAttackFormRef[2][2] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Stab/Stab1_3.Stab1_3'"));
	EnemyAttackFormRef[2][3] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Stab/Stab1_4.Stab1_4'"));
	EnemyAttackFormRef[2][4] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/Stab/Stab1_5.Stab1_5'"));*/

	/*EnemyAttackFormRef[2][0] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/SpecialArts/SpecialArts.SpecialArts'"));*/
	EnemyAttackFormRef[10] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/SpecialArts/SpecialArts_2.SpecialArts_2'"));
	EnemyAttackFormRef[11] =
		(TEXT("AnimMontage'/Game/EnemyRogue/Animation/Attack/SpecialArts/SpecialArts_3.SpecialArts_3'"));
	for (int i = 0; i < 12; i++) {
		auto EnemyAttackAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
			(EnemyAttackFormRef[i]);
		if (EnemyAttackAsset.Succeeded()) {
			EnemyAttackForm[i] = EnemyAttackAsset.Object;
		}
	}
}

void URogueAnimInstance::EnemyRogueAttackFormIndex() {
	int32 AttackFormIndex = FMath::RandRange(0, 11);
	FinalEnemyAttackForm = EnemyAttackForm[AttackFormIndex];
	/*//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Blue, FString::Printf(TEXT("EnemyAttackFormIndex")));
	for (int i = 0; i < 3; i++) {
		EnemyAttackFormRand[i] = FMath::RandRange(0, 2);
		switch (EnemyAttackFormRand[i]) {
		case 0:
			EnemyAttackFormIndexRand[i] = FMath::RandRange(0, 4);
			break;
		case 1:
			EnemyAttackFormIndexRand[i] = FMath::RandRange(0, 5);
			break;
		case 2:
			EnemyAttackFormIndexRand[i] = FMath::RandRange(0, 1);
			break;
		}
	}
	EnemyRogueAttackFormSetting();*/
}

void URogueAnimInstance::EnemyRogueAttackFormSetting() {
	/*for (int i = 0; i < 3; i++) {
		EnemyAttackForm[i] = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(),
			NULL, EnemyAttackFormRef[EnemyAttackFormRand]);
	}
	//EnemyAttackFormRef[EnemyAttackFormRand[i]][EnemyAttackFormIndexRand[i]]
	int32 SelectAttackFormIndex = FMath::RandRange(0, 2);
	FinalEnemyAttackForm = EnemyAttackForm[SelectAttackFormIndex];
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Blue, FString::Printf(TEXT("EnemyAttackFormSetting")));*/
}