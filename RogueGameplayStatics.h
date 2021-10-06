// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "RogueGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API URogueGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()

private:
	int32 GameStartCounter = 0;

public:
	void PlusGameStartCounter();
	void SetGameStartCounter(int32 newCounter);
	int32 GetGameStartCounter();
};
