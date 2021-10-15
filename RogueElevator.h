// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Vibration.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "RogueElevator.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ARogueElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARogueElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* Rogue) override;
	virtual void NotifyActorEndOverlap(AActor* Rogue) override;

private:
	bool Stop;
	bool Move;
	bool Upfloor;
	bool SwitchAction;
	bool MoveStart;
	float ElevatorSpeed;
	float ElevatorAxel;
	float SwitchLen;

public:
	void Elevatorinit();
	void SwitchBlockinit();
	void Switchinit();
	void ElevatorStateinit();
	void ElevatorMove();
	void SwitchMove();
	bool ElevatorStopState();


public:
	void setElevatorSpeed(float newSpeed) { ElevatorSpeed = newSpeed; }
	float getElevatorSpeed() { return ElevatorSpeed; }

	void setElevatorAxel(float newAxel) { ElevatorAxel = newAxel; }
	float getElevatorAxel() { return ElevatorAxel; }

public:
	USoundCue* StartStopSound;
	USoundCue* MoveSound;
	UAudioComponent* MoveSoundComponent;
	//UAudioComponent* StartStopSoundComponent;

	UPROPERTY(EditAnywhere)
		USceneComponent* Root;
	UPROPERTY(EditAnywhere)
		USceneComponent* UpStopZone;
	UPROPERTY(EditAnywhere)
		USceneComponent* DownStopZone;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Elevator;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SwitchBlock;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SwitchBlockUpfloor;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SwitchBlockDownfloor;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SwitchHall;
	UPROPERTY(EditAnywhere)
		UBoxComponent* Switch;
	UPROPERTY(EditAnywhere)
		UBoxComponent* SwitchUpfloor;
	UPROPERTY(EditAnywhere)
		UBoxComponent* SwitchDownfloor;

	UPROPERTY(EditAnywhere)
		UVibration* Vibrations;

};
