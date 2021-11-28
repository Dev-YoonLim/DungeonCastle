// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Castle_in_DungeonGameModeBase.h"
#include "Rogue.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	virtual void CapsuleInit();
	virtual void TakeRogueInit();
	virtual void TakeWorldInit();
	virtual void ItemMeshInit();
	virtual void ParticleInit();
	virtual void SoundInit();


public:
	virtual ARogue* GetRogue();
	virtual ACastle_in_DungeonGameModeBase* GetGameMode();
	virtual UCapsuleComponent* GetCapsuleComponent();
	virtual UStaticMeshComponent* GetItemMesh();
	virtual UParticleSystemComponent* GetParticle();


private:
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* TakeItemRange;
	UPROPERTY(EditAnywhere)
		ARogue* myRogue;
	UPROPERTY(EditAnywhere)
		ACastle_in_DungeonGameModeBase* MyGameMode;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ItemParticle;
	UPROPERTY(EditAnywhere)
		UParticleSystem* TakeItem;
	UPROPERTY(EditAnywhere)
		ARogueState* MyRogueState;

public:
	int32 ItemIndex;
	int32 ItemCount;
	USoundCue* GetItemSound;
	USoundCue* ItemIdleSound;
};
