// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "RandomItem.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API ARandomItem : public AItem
{
	GENERATED_BODY()

protected:
	ARandomItem();

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
