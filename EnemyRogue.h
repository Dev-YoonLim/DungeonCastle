// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Rogue.h"
#include "Sound/SoundCue.h"
#include "EnemyRogueWeapon.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/SphereComponent.h"
#include "Castle_in_DungeonGameModeBase.h"
#include "EnemyRogue.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API AEnemyRogue : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyRogue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void PostInitializeComponents() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//USkeletalMeshComponent* EnemyRogueBody;

private:

	UPROPERTY(EditAnyWhere)
	float Hp;

	float AttackDamegeValue;
	float DefenceValue;
	float MoveSpeedValue;
	float MoveAccerValue;
	float TakeWeaponDamege;
	bool TakeWeaponEffect;
	float TakeDotDamege;
	float TakeTorchStabDamege;
	float TakeTorchBurnAttacksDamege;
	float TakeTorchSpecialDamege;
	float TakeWeaponTempDamege;
	float KnockBigBackValue;
	float KnockBackValue;
	float ChangeKnockBackValue;
	float RogueWeaponSpeed;
	bool TakeCheckDoubleAttack;
	int32 TakeCheckAttackDirection[2];

	int32 TakeTorchEffectStack;
	int32 TakeWeaponAttackStack;
	int32 TakeWeaponElementNumbers;
	int32 TakeTorchElementNumbers;
	int32 StunDotTick;
	int32 BurningDotTick;
	int32 ColdDotTick;
	int32 PoisonDotTick;
	int32 ElectriFicationDotTick;

	int32 AllStack;

	int32 DeathData;
	int32 Karma;

	FVector TakeAttackVectorValue;

	int32 WeaponAttackRandHitIndex;
	int32 TorchAttackRandHitIndex;
	int32 LastAttackDirection;

public:
	UPROPERTY(EditAnywhere)
		int32 TakeDamageLimit;
	int32 TakeDamageCount;
	int32 BurnExplosionStack;
	int32 ColdSlowStack;
	int32 PoisonStack;
	int32 VenomStack;
	int32 ElectricHitStack;
	int32 HitDirectionIndex;
	UPROPERTY(EditAnywhere)
		int32 EnemyForm;

	bool EnemyDownFinish;
	bool Hit;
	bool Walk;
	bool Idle;
	bool Attack;
	bool WeaponKnockBack;
	bool EnemyDead;
	bool Stun;
	bool Poison;
	bool Burn;
	bool Burning;
	bool Venom;
	bool ColdSlow;
	bool FreezSlow;
	bool ElectriFicationDPlusReady;
	bool ElectriFication;
	bool ElectriFicationPlus;
	bool ElectriFicationDPlus;
	float ElectriFicationValue;
	bool TakeStabAttackOn;
	bool TakeDefaultEffect;
	bool ExplosionBody = false;
	bool TakeTorchSpecial;
	
	bool AttackCanHit;
	bool TakeHitState;
	int32 HitKinds;

	float EffectScale;
	float GiftAbilityPer;
	float ExplosionDamage;
	float EnemyRogueWeaponDamage;
	float EnemyRogueWeaponSpeed;
	float EnemyRogueWeaponRange;
	float SlowValue;
	UAnimMontage* DeathForm;
	
	int32 GiftAbilityIndex;
	int32 HitCount;
	int32 HitSuperArmorCount;

public:
	void GetWorldGameMode();

	void SetHp(float NewHp);
	
	UFUNCTION()
	float GetHp() { return Hp; }

	void SetFicationValue(float NewValue) { ElectriFicationValue = NewValue; }
	float GetFicationValue() { return ElectriFicationValue; }
	float GetSpeedValue() { return MoveSpeedValue; }

public:
	void EnemyWeaponInit();
	void EnemyRogueBodyInit();
	void EnemyRogueCollisionInit();
	void EnemyRogueStateInit();
	void EnemyRogueTakeDamegeDelegateInit();
	void TakeStackInit();
	void AllStateInit();
	void AllDotTickInit();
	void StateEffectInit();

	void EnemyRogueBodySetting();
	void EnemyRogueStateSetting();
	//void EnemyRogueAnimationInit();

public:
	void EnemyRogueTakeWeaponDamege(float DefaultTotalDamege, float EffectTotalDamege, float DotDamege, 
		int32 WeaponElementNumber, int32 WeaponAttackStack, bool* WeaponEffect, bool, int32, int32, float);
	
	void EnemyRogueTakeTorchDamege(float StabDamege, float BurnAttacksDamege, float SpecialDamege, 
		int32* TorchElementStack, bool StabAttackOn, bool* DefaultEffect, bool* SpecialEffect, 
		int32 TorchElementNumber);
	
	void EnemyRogueTakeStunDotTimer();
	void EnemyRogueTakeBurningDotDamege();
	void EnemyRogueTakeColdSlowDotTimer();
	void EnemyRogueTakePoisonDotDamege();
	void EnemyRogueTakeElectriFicationDotTimer();
	void EnemyRogueSlow(int32, bool);
	void EnemyRogueDie();
	//void EnemyRogueTakeHitAnimation();

public:
	void TakeWeaponKnockBackCheck(bool);
	void TakeAttackVector(FVector);

	void TakeStun();
	void TakeBurn();
	void TakeCold();
	void TakePoison();


	void TakeKnockBack();
	void TakeKnockBackExplosion();
	void TakeBurnExplosion();
	void TakeBurnExplosionStack();
	void TakeFreez();
	void TakeFreezExplosion();
	void TakeVenom();
	void TakeVenomExplosion();
	void TakeElectiFication();
	void TakeElectiFicationExplosion();

	void TakeAllStack();
	void AllClearTimer();
	
	void StateEffectPlay();

	void WorldRogueInit();
	FVector DirectionVector();

	void WeaponHitAnimationPlay();
	void TorchHitAnimationPlay();

	void SetEnemyDownFinish(bool StartCheck);
	void EnemyRogueWeaponInfo();

	bool GetTakeHit();
	void SetTakeHit(bool newTakeHitState);
	

public:
	//bool DoOrbitingWalk(int32 OrbitingDir);
	bool DoAttack();
	bool DoWalk(int32 WalkIndex);
	bool DoConfused();
	bool DoAnyThing();
	bool CheckHit();
	bool CheckAttack();
	bool DoIdle(int32 IdleIndex);
	bool DoRoll(int32 RollDirection);

	void LoadGameData(URogueSaveGame* LoadData);


public:
	UPROPERTY(EditAnywhere)
		int32 HitCountLimite;
	UPROPERTY(EditAnywhere)
		int32 HitSuperArmorCountLimit;

	UPROPERTY(EditAnywhere)
		ARogue* myRogue;
	UPROPERTY(EditAnywhere)
		AEnemyRogue* OtherEnemy;
	UPROPERTY(EditAnywhere)
		UChildActorComponent* EnemyWeapon;
	UPROPERTY(EditAnyWhere)
		USpringArmComponent* ViewArm;
	UPROPERTY(EditAnywhere)
		AEnemyRogueWeapon* EnemyRogueWeapon;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* EnemyBehaviorTree;

	FString SaveSlotName;
	UAnimInstance* SetEnemyRogueAnimInstance;
	URogueAnimInstance* EnemyAnimInst;

	USoundCue* TakeHitSoundCue;

	ACastle_in_DungeonGameModeBase* MyGameMode;
	UParticleSystem* BurningEffect;
	UParticleSystem* BurnExplosionEffect;
	UParticleSystem* ColdSlowEffect;
	UParticleSystem* FreezSlowEffect;
	UParticleSystem* PoisonEffect;
	UParticleSystem* VenomEffect;
	UParticleSystem* ElectriFicationEffect1;
	UParticleSystem* ElectriFicationEffect2;
	UParticleSystem* ElectriFicationEffect3;
	//UParticleSystem* HitEffect;
	FTimerHandle StunDotTimeHandle;
	FTimerHandle BurnDotTimeHandle;
	FTimerHandle ColdDotTimeHandle;
	FTimerHandle PoisonDotTimeHandle;
	FTimerHandle ElectriFicationTimeHandle;
	FTimerHandle KnockBackTimeHandle;
	FTimerHandle StateEffectTimeHandle;

	TCHAR* BurningRef;
	TCHAR* BurnExplosionRef;
	TCHAR* ColdRef;
	TCHAR* FreezRef;
	TCHAR* PoisonRef;
	TCHAR* VenomRef;
	TCHAR* ElectriFicationRef1;
	TCHAR* ElectriFicationRef2;
	TCHAR* ElectriFicationRef3;

	FVector EnemyRogueVectors;

	UPROPERTY(EditAnywhere)
		int32 StartWeaponNumber;
};
