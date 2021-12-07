// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Castle_in_DungeonGameModeBase.h"
#include "Components/PrimitiveComponent.h"
#include "Rogue.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "StartItem.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API AStartItem : public AActor
{
	GENERATED_BODY()
	
protected:
	AStartItem();

public:
	// Called every frame
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UFUNCTION()
		void FireOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void CapsuleInit();
	virtual void TakeRogueInit();
	virtual void TakeWorldInit();
	virtual void ItemMeshInit();
	virtual void ParticleInit();
	virtual void SoundInit();


/*public:
	virtual ARogue* GetRogue();
	virtual ACastle_in_DungeonGameModeBase* GetGameMode();
	virtual UCapsuleComponent* GetCapsuleComponent();
	virtual UStaticMeshComponent* GetItemMesh();
	virtual UParticleSystemComponent* GetParticle();*/
public:
	void GameStartSetting();
	void ParticleSetting();


protected:
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* TakeItemRange1;
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* TakeItemRange2;
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* TakeItemRange3;
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* TakeItemRange4;
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* TakeItemRange5;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemMesh1;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ItemParticle1;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemMesh2;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ItemParticle2;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemMesh3;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ItemParticle3;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemMesh4;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ItemParticle4;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemMesh5;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ItemParticle5;

	UPROPERTY(EditAnywhere)
		ARogue* myRogue;
	UPROPERTY(EditAnywhere)
		ACastle_in_DungeonGameModeBase* MyGameMode;

	UPROPERTY(EditAnywhere)
		UParticleSystem* TakeItem;
	UPROPERTY(EditAnywhere)
		ARogueState* MyRogueState;
	UPROPERTY(EditAnywhere)
		int32 ItemIndex;

public:
	int32 ItemCount[5];
	USoundCue* GetItemSound;
	USoundCue* ItemIdleSound;
};
