// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rogue.h"
#include "Components/BoxComponent.h"
#include "SaveBox.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ASaveBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASaveBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* Rogue) override;


public:
	UPROPERTY(EditAnywhere)
		UBoxComponent* SaveCheckBox;
};
