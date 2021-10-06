// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Rogue.h"
#include "Kismet/GameplayStatics.h"
#include "RogueBonFire.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ARogueBonFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARogueBonFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	void MeshInit();
	void FireOn();
	void WidgetOn();
	void WorldRogueInit();
	void GetWorldGameMode();

public:
	UPROPERTY()
		UStaticMeshComponent* BonFireSword;
	UPROPERTY()
		UParticleSystemComponent* BonFireFlame;
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* BonFireCapsule;
	/*UPROPERTY()
		FCapsuleShape*/

public:
	ARogue* myRogue;
	ACastle_in_DungeonGameModeBase* MyGameMode;

};
