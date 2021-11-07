// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Candle.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ACandle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACandle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CandleSetRefInit();
	void CandleMeshInit();
	void CandleLightInit();

public:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CandleMesh;
	
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* LightParticle;

public:
	UPROPERTY(EditAnywhere)
		int32 CandleSetIndex;
	TCHAR* CandleSetRef;

};
