// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Castle_in_DungeonGameModeBase.h"
#include "RogueAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API URogueAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	URogueAnimInstance();


protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable)
		void Walking(bool right, bool left, bool forward, bool back, bool roll);
	
	UFUNCTION(BlueprintCallable)
		void Idle();

	UFUNCTION(BlueprintCallable)
		void Attack(int AttackQue);

	UFUNCTION(BlueprintCallable)
		void Desh(bool right, bool left, bool forward, bool back, bool roll);

	UFUNCTION(BlueprintCallable)
		void Roll();

	UFUNCTION(BlueprintCallable)
		void BackStep();

public:
	void AnimationInit();
	void DaggerAttackAnimationInit();
	void AttackFormSetting();
	void MovementAnimationInit();
	void AnimationWeaponTorchSpeedInit();
	void AnimationWeaponSpeedSetting(float WeaponSpeed, float WeaponSpeedValue, float WeaponLevelValue);
	void AnimationTorchSpeedSetting(float TorchLevelValue);
	void TorchAttackAnimationInit();
	void RogueHitAnimationInit();
	void GetWorldGameModeBase();
	void AttackAnimationDelegateInit();
	void AttackAnimationInit();

//	void setAttackFormforAnim(int NewForm) { AttackFormforAnim = NewForm; }
//	int getAttackFormforAnim() { return AttackFormforAnim; }

	void AttackFormToChangeAnimReferens( int32 AttackFormOne, int32 AttackFormIndexOne, 
		int32 AttackFormTwo, int32 AttackFormIndexTwo, int32 AttackFormThree, int32 AttackFormIndexThree);

	void AttackFormInit();

public:
	void EnemyRogueAnimationInit();
	void EnemyRoguePlayHitAnimationInit();
	void EnemyRoguePlayMovementAnimationInit();
	void EnemyRoguePlayIdleAnimationInit();
	void EnemyRoguePlayDeathAnimation();
	void EnemyRoguePlayAttackAnimation();
	void EnemyRogueAttackFormSetting();

public:
	int32 AttackFormSlot;
	bool DoubleAttackForm[4][10];
	int32 AttackDirection[4][10][2];
	float SlashFormSynergy[4][10];
	float BreakFormSynergy[4][10];
	float StabFormSynergy[4][10];
	float SelectFormSynergy[3][3];

	bool CheckDoubleForm[3];
	int32 CheckAttackDirection[3][2];

	int32 EnemyAttackFormRand[3];
	int32 EnemyAttackFormIndexRand[3];

	bool AnimationAllCheck;

public:
	UAnimMontage* RogueUpHit1;
	UAnimMontage* RogueUpHit2;
	UAnimMontage* RogueSideHit1;
	UAnimMontage* RogueSideAndDownHit1;
	UAnimMontage* RogueDownHit1;
	UAnimMontage* RogueSideAndUpHit1;
	
	UAnimMontage* AttackTestMontage;
	UAnimMontage* Roll_Montage;
	UAnimMontage* Roll_BackMontage;
	UAnimMontage* IdleMontage;
	
	UAnimMontage* WalkMontage;
	UAnimMontage* WalkBackMontage;
	UAnimMontage* WalkRightMontage;
	UAnimMontage* WalkLeftMontage;
	
	UAnimMontage* DeshMontage;
	UAnimMontage* DeshRightMontage;
	UAnimMontage* DeshLeftMontage;
	UAnimMontage* DeshBackMontage;

	UAnimMontage* AttackOneMontage;
	UAnimMontage* AttackTwoMontage;
	UAnimMontage* AttackThreeMontage;

	UAnimMontage* TorchAttackMontage;

	UAnimMontage* ChangeAttackThreeMontage;
	UAnimMontage* ChangeAttackTwoMontage;
	UAnimMontage* ChangeAttackOneMontage;
	
	TCHAR* AttackFormList[4][10];
	TCHAR* SelectAttackForm[3];

	UPROPERTY(EditAnywhere)
		ACastle_in_DungeonGameModeBase* MyGameMode;

public:
	UAnimMontage* EnemyAttackForm[3];
	UAnimMontage* FinalEnemyAttackForm;
	

	UAnimMontage* EenmyNowIdle;
	UAnimMontage* EnemyNormalIdle;
	UAnimMontage* EnemyCombatIdle;
	UAnimMontage* EnemySadIdle;
	UAnimMontage* EnemyConfused;

	UAnimMontage* EnemyDownDeath1[2];
	UAnimMontage* EnemyDownDeath2[2];
	UAnimMontage* EnemyDownDeath3[2];
	UAnimMontage* EnemyUpDeath1[2];
	UAnimMontage* EnemyUpDeath2[2];
	UAnimMontage* EnemyUpDeath3[2];

	UAnimMontage* EnemyUpHit1;
	UAnimMontage* EnemyUpHit2;
	UAnimMontage* EnemySideHit1;
	UAnimMontage* EnemySideAndDownHit1;
	UAnimMontage* EnemyDownHit1;
	UAnimMontage* EnemySideAndUpHit1;

	UAnimMontage* EnemyTorchUpHit1;
	UAnimMontage* EnemyTorchUpHit2;
	UAnimMontage* EnemyTorchSideAndDownHit1;
	UAnimMontage* EnemyTorchDownHit1;
	UAnimMontage* EnemyTorchSideAndUpHit1;

	UAnimMontage* EnemyForwardWalk;
	UAnimMontage* EnemyBackWalk;
	UAnimMontage* EnemyRightWalk;
	UAnimMontage* EnemyLeftWalk;
	
	UAnimMontage* EnemyCombatForwardWalk;
	UAnimMontage* EnemyCombatBackWalk;
	UAnimMontage* EnemyCombatRightWalk;
	UAnimMontage* EnemyCombatLeftWalk;
	
	UAnimMontage* EnemySadForwardWalk;
	UAnimMontage* EnemySadBackWalk;
	UAnimMontage* EnemySadRightWalk;
	UAnimMontage* EnemySadLeftWalk;

	UAnimMontage* EnemyRoll;
	UAnimMontage* EnemyBackRoll;


	TCHAR* EnemyAttackFormRef[4][6];
	TCHAR* SelectAttackFormRef[3];
//private:
//	int AttackFormforAnim;

};
