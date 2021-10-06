// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PollFireRamp.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API APollFireRamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APollFireRamp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UStaticMeshComponent* BigLamp;
	UParticleSystemComponent* Fire;
	USoundCue* SoundCue;

};
