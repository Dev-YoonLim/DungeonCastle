// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SystemValueSave.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API USystemValueSave : public USaveGame
{
	GENERATED_BODY()

public:
	USystemValueSave();

	UPROPERTY()
		float FXSoundVolume;
	
};
