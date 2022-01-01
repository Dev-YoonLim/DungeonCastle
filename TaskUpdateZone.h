// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rogue.h"
#include "Components/BoxComponent.h"
#include "TaskUpdateZone.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ATaskUpdateZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskUpdateZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* myRogue) override;

public:
	UPROPERTY(EditAnywhere)
		UBoxComponent* TaskUpdateBox;
	UPROPERTY(EditAnywhere)
		int32 TaskUpdateNumber;
};
