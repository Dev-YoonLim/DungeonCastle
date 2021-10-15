// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "RogueLevel.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ARogueLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARogueLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void LevelFloorInit();
	void DoorGuardPositionInit();
	void DoorGuard(int32 NextDirection, int32 NextDirectionIndex, int32 PreDirection, int32 PreDirectionIndex, bool Start);
	void PreDoorGuard(int32 PreDirection, int32 DirectionIndex);

public:
	UStaticMeshComponent* LevelFloorStaticMeshComp;
	UStaticMeshComponent* FloorDoorGuard[10];
	FVector DoorGuardFosition[4][3];
	UChildActorComponent* EndPointActor;
	//ANavMeshBoundsVolume* NaviMeshComp;
};
