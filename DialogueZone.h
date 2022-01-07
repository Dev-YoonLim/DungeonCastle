// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeathZone.h"
#include "DialogueZone.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API ADialogueZone : public ADeathZone
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADialogueZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
		int32 DialogueZoneNumber;
	
	UPROPERTY(EditAnywhere)
		int32 DialogueKindsNumber;
};
