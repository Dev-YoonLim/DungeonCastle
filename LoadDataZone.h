// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeathZone.h"
#include "LoadDataZone.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API ALoadDataZone : public ADeathZone
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALoadDataZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
