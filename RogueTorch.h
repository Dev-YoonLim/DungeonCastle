// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "EnemyRogue.h"
#include "Rogue.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "RogueTorch.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ARogueTorch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARogueTorch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
		void EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void EnterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void TorchStick();
	void TorchFire();
	void TorchLight();
	void TorchCrashDelegate();
	void TorchLeaveDelegate();
	void TorchRightLeftCapsuleInit();
	void TorchWallCrashDelegateInit();
	void TorchSideCrashDelegate(bool RightSideValue);
	void TorchSideLeaveDelegate(bool RightSideValue);

	void TorchAttackEffectPlay();
	void TorchAttackEffectInit();

	void WorldRogueInit();
	void WorldGameModeInit();

	void TorchChangeElementDelegateInit();
	void TorchChangeElement(int32, float ElementLevelValue);

	void BurnAttacksSpecial(float);

	void TorchStateDefaultEffect();
	//void TorchStateSpecialEffect(float, float);

	void ConstData();
	void ElementLevelUp(int32, float);

	void TorchStatusInit();

	void CheckTorchAttackFinish() { TorchAttackFinsh = false; }

public:
	TCHAR* FireEffectReference;
	TCHAR* FireEffectElementReference;
	TCHAR* FireBurnAttacksEffectReference;
	TCHAR* FireBurnAttacksCriEffectReference;

	UStaticMeshComponent* FireStick;
	UParticleSystemComponent* FireEffect;
	UParticleSystemComponent* FireEffectElement;

	FName HitPlaceName;
	FVector HitPlace;
	FVector ElementLevelValueSize;

	UPROPERTY(EditAnywhere)
		USphereComponent* ExplosionSphere;

	UPROPERTY(EditAnywhere)
		UParticleSystem* TorchHitEffect;

	UPROPERTY(EditAnywhere)
		UParticleSystem* TorchHitBurnAttacksCriEffect;

	UPROPERTY(EditAnywhere)
		UPointLightComponent* FireLight;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* RightCapsule;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* LeftCapsule;

	UPROPERTY(EditAnywhere)
		ARogue* myRogue;

	UPROPERTY(EditAnywhere)
		ACastle_in_DungeonGameModeBase* MyGameMode;

	UPROPERTY()
		AActor* OtherActors;

	FTimerHandle HitTimeHandle;

	USoundCue* IdleFireSound;

public:
	bool TorchArrive;
	bool RightSide;
	bool TorchHitOn;
	bool BurnAttacksSpecialOn;

	float StabDamege;
	float BurnAttacksDamege;

	float BurnAttacksCriPer;
	int32 TorchLevel;
	float TorchLevelValue;
	FVector TorchLevelValueSize;
	int32 ElementLevel;
	float ElementLevelValue;
	
	int32 TorchElementNumber;
	int32 TorchHitLimit;
	int32 TorchLimitPlus;
	int32 TorchHitCounter;

	float ElementSynergy;
	float StabSpeedPlus;
	float ElementSpecialDamegeDamege;

	float TorchStabDamegeValue;
	float TorchBurnAttacksDamegeValue;
	//float TorchBurnAttacksHitValue;
	float TorchSpecialDamegeValue;
	float TorchTempDamegeValue;

	int32 TorchEffectsStack[5];
	bool TorchStateDefaultEffects[5];
	bool TorchStateSpecialEffects[5];
	//float TorchStateSpecialEffects[5];
	float TorchDotDamege;
	float EffectDamege;
	bool CanStabAttack;
	bool TorchAttackFinsh;

	int32 TorchAttackCostData;

	FVector TackAttackVectorValue;
	TArray<AActor*>EnemyArray;
	//TSubclassOf <AActor> EnemyClass;
	//AEnemyRogue* EnemyRogus;

public:
	int32 GetTorchEffectsStack(int32 TorchElementNums) { return TorchEffectsStack[TorchElementNums];}
	void SetTorchEffectsStack(int32 NewStacks, int32 TorchElementNums) { TorchEffectsStack[TorchElementNums] = NewStacks; }

	bool getTorchArrive() { return TorchArrive; }
	void setTorchArrive(bool Arrive) { TorchArrive = Arrive; }

	bool getRightSide() { return RightSide; }
	void setRightSide(bool Right) { RightSide = Right; }

	float getStabDamege() { return StabDamege; }
	void setStabDamege(float newDamege) { StabDamege = newDamege; }

	float GetFireDamege() { return TorchBurnAttacksDamegeValue; }
	void SetPlusFireDamege(float newDamege) { TorchBurnAttacksDamegeValue += newDamege; }
	void SetMultiplyFireDamege(float newDamege) { TorchBurnAttacksDamegeValue *= newDamege; }

	void GetTorchTotalDamege(float, float, float, float);

	//float GetEffectDamege() { return EffectDamege; }
	//void SetEffectDamege(float NewDamege) { EffectDamege = NewDamege; }

	int32 GetBurnAttacksHit() { return TorchHitLimit; }
	void SetBurnAttacksHit(int32 BurnHit) { TorchHitLimit = BurnHit; }
	void SetBurnAttackHitIncrease(int32 PlusBurnHit) { TorchLimitPlus = PlusBurnHit; }

	//float GetElementSpecialDamegeDamege

	float GetBurnAttacksCriPer() { return BurnAttacksCriPer; }
	void SetPlusBurnAttacksCriPer(float IncreasePercent) { BurnAttacksCriPer *= IncreasePercent; }
	void SetMultiplyBurnAttacksCriPer(float IncreasePercent) { BurnAttacksCriPer *= IncreasePercent; }

	void StateEffectSpecialExplosionCheck();
	void TakeAttackVector(FVector);
};
