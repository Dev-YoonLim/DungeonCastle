// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyRogueWeapon.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API AEnemyRogueWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyRogueWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void EnemyRogueWeaponInit();
	void EnemyRogueWeaponStatInit();
	void EnemyRogueWeaponMeshInit();

public:
	void EnemyRogueWeaponChange(int32 SelectWeaponNumber);
	void EnemyRgoueWeaponTransform();
	bool GetTakeHit() { return AttackCanHit; }
	void SetTakeHit(bool newTakeHitState) { AttackCanHit = newTakeHitState; }

public:
	float EnemyWeaponDamage;
	float EnemyWeaponSpeed;
	float EnemyWeaponRange;
	bool AttackCanHit;
	
public:
	UPROPERTY(EditAnywhere)
		int32 EnemyWeaponIndex;
	TCHAR* EnemyRogueWeaponRef;

public:
	UStaticMeshComponent* EnemyWeapons;

};
