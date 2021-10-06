// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rogue.h"
#include "Components/BoxComponent.h"
#include "OpenLevelBox.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API AOpenLevelBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenLevelBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		virtual void NotifyActorBeginOverlap(AActor* Rogue) override;
	UFUNCTION()
		void OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* OpenLevelZone;

public:
	UPROPERTY(EditAnywhere)
		FName LevelToLoad;
	UPROPERTY(EditAnywhere)
		int32 LevelIndex;
	int32 SubLevelIndex;

public:
	void MoveLevel();

};
