// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "EntranceMove.h"
#include "RogueSaveGame.h"
#include "Vibration.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Door.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* Rogue) override;

private:
	UPROPERTY(EditAnywhere)
		float MaxValue;
	UPROPERTY(EditAnywhere)
		float SelectEntranceNumber;
	bool OpeningState = false;

public:
	void DoorInit();
	void OpenInit();
	void DoorOpen();
	void SoundStop();

	UFUNCTION()
		void LoadGameData(URogueSaveGame* LoadData);

	UFUNCTION(BlueprintCallable)
		void EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void NotEnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere)
		ACastle_in_DungeonGameModeBase* MyGameMode;
	
	UPROPERTY(EditAnywhere)
		int32 DungeonKinds;
	UPROPERTY(EditAnywhere)
		int32 DoorNumbers;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DoorStateOne;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DoorStateTwo;

	UPROPERTY(EditAnywhere)
		USceneComponent* Root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DoorOne;
	UPROPERTY(EditAnywhere)
		UBoxComponent* DoorSwitchOne;
	UPROPERTY(EditAnywhere)
		UBoxComponent* DoorSwitchTwo;
	
	UPROPERTY(EditAnywhere)
		UEntranceMove* DoorWork;

	UPROPERTY(EditAnywhere)
		UVibration* Vibration;

	UAudioComponent* MoveSoundComponent;
	USoundCue* OpenDoorSound;
	FString SaveSlotName;
	bool DoorLoad;
};
