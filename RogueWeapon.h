// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Rogue.h"
#include "RogueState.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "RogueWeapon.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ARogueWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EnterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	void DataTableInit();
	void WeaponInit();

	bool getHitCrash() { return HitCrash; }
	void setHitCrash(bool Crash) { HitCrash = Crash; }

	void AttackWallCrashDelegate();

	void WeaponNumberChange(int32 WeaponNumber);
	void WeaponDelegate();

	void WeaponAttackEffectInit();
	void WeaponAttackPlay(AActor*, UPrimitiveComponent*);

	void WorldRogueInit();
	void WorldGameModeInit();

	void WeaponChangeElement(int32, float ElementLevelValue);

	void WeaponSynergy(float, float, float);
	void GetWeaponTotalDamegeValue(float, float, float, float);
	void GetWeaponDoubleCheckAndAttackDirection(bool, bool, bool, int32, int32, int32, int32, int32, int32);

	void GetAttackQue(int32 NowQue);

	void CostData();

	void WeaponLevelUp();
	void ElementLevelUp(int32, float);

	void SpawnHitEffect();

private:
	class UDataTable* WeaponDataTable;
	bool HitCrash;
	float HitEffectScale;
	float HitElementEffectScale;

	float WeaponDamege;

	float EffectMinRange;
	float EffectMaxRange;

	float ElementDamege;
	float ElementSynergy;


	float StabSynergy;
	float SlashSynergy;
	float BreakSynergy;

	float WeaponAttackDefaultPhysicsElementDameges[3];
	bool DoubleAttackChecks[3];
	int32 AttackDirection[3][2];

	float WeaponLevelValue;
	int32 WeaponLevel;
	int32 ElementLevel;
	float ElementLevelValue;
	float WeaponSpeed;

	int32 WeaponAttackCostData;

	bool WeaponAttackCheck;
	bool WeaponKnockBack;

	FVector TackAttackVectorValue;

public:
	void AttackElementStateEffect(float, float);
	void SetStun(float InputDamege);
	void SetBurn(float InputDamege);
	void SetCold(float InputDamege);
	void SetPoison(float InputDamege);
	void SetElectricStack(float Per, float InputDamege);

private:
	bool StateEffect[5];
	float DamegeTaken;
	float DotDamege[5];
	float DotDamegeTime;
	float ElementPer;
	float ElementPlusValue;
	float DefaultElementPer;
	float TotalElementPer;

	float AttackDmgPlusValue;
	float AttackDmgValue;
	int32 ElementStack[5];

public:
	void SetDotDamege(int32 DotDamegeElement, float OriginDamege, float DotPer);
	void SetDamegeTaken(float NewDamege) { DamegeTaken = NewDamege; }
	void SetDotDamegeTime(float NewTime) { DotDamegeTime = NewTime; }
	void SetPlusElementPer(float PlusPer) { TotalElementPer = ElementPer + PlusPer; }
	void SetElementPer(float NewPer) { ElementPer = NewPer; }
	void SetTotalElementPer(float NewPer) { TotalElementPer = NewPer; }
	void SetHitPlusElement(float PlusValue) { ElementPlusValue = PlusValue;}
	void SetMultiplyElementPer(float MultiplyPer) { ElementPer *= MultiplyPer; }
	void SetAttackDmgValue(float NewValue) { AttackDmgValue = NewValue; }
	void SetAttackDmgPlusValue(float NewValue) { AttackDmgPlusValue += NewValue * 0.05; }
	void InitAttackDmgPlusValue() { AttackDmgPlusValue = 1.f; }
	void TakeKnockBackCheck(int32);
	
	float GetDotDamege(int32 DotDamegeElement) { return DotDamege[DotDamegeElement]; }
	float GetDamegeTaken() { return DamegeTaken; }
	float GetDotDamegeTime() { return DotDamegeTime; }
	float GetElementPer() { return ElementPer; }
	float GetDefaultElementPer() { return DefaultElementPer; }
	float GetTotalElementPer() { return TotalElementPer; }

	void TakeAttackVector(FVector);
	void WeaponTransformSetting(int32);

	void Receive_CallRogueUseWeapon();
	//void WeaponHitPlaceSetting(int32, UBoxComponent*);

public:
	FTimerHandle DotTimeHandle;

	int32 SelectWeaponElementNumber;
	int32 SelectWeaponNumber;
	int32 AttackQue;
	FVector ElementEffectSize;

	TCHAR* WeaponReference;
	TCHAR* ElementEffectReference;
	TCHAR* ElementHitEffectReference;
	
	FName HitPlaceName;
	FVector HitPlace;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Weapon;

	UPROPERTY(EditAnywhere)
		UParticleSystem* HitEffect;

	UPROPERTY(EditAnywhere)
		ARogue* MyRogue;

	UPROPERTY(EditAnywhere)
		ARogueState*	myRogueState;

	UPROPERTY(EditAnywhere)
		ACastle_in_DungeonGameModeBase* MyGameMode;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* WeaponElementEffect;

	UPROPERTY(EditAnywhere)
		UParticleSystem* WeaponElementHitEffect;
};