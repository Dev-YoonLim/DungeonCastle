// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "RogueGameSetting.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API URogueGameSetting : public UGameUserSettings
{
	GENERATED_BODY()

public:
	URogueGameSetting();
	void ChangeVSync(bool VSync);
	
};
