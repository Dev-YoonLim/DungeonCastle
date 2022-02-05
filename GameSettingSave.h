// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSettingSave.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API UGameSettingSave : public USaveGame
{
	GENERATED_BODY()
public:
	UGameSettingSave();
	
	UPROPERTY()
		int32 LanguageType;
	
	UPROPERTY()
		float FXSoundVolume;

	UPROPERTY()
		float FOVValue;

	UPROPERTY()
		bool HeadTracking;
};
