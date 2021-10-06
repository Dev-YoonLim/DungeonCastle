// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PollFireRamp.h"
#include "Rogue.h"
#include "Castle_in_DungeonGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GuideFire.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API AGuideFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGuideFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	void WorldRogueInit();
	void GetWorldGameMode();
	void LampInit();
	void CapsuleInit();

public:
	UStaticMeshComponent* GuideLamp;
	UStaticMeshComponent* LampPost;
	UParticleSystemComponent* Fire;
	UCapsuleComponent* TouchLampCapsule;
	UParticleSystem* TakeItem;

public:
	ARogue* myRogue;
	ACastle_in_DungeonGameModeBase* MyGameMode;
	USoundCue* SoundCue;
	USoundCue* GetGuideLampSound;
	
public:
	bool Check = false;
};
