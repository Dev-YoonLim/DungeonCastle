// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Vibration.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLE_IN_DUNGEON_API UVibration : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVibration();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
		float Radius;
	UPROPERTY()
		float Count;
	UPROPERTY()
		bool MoveReady;

public:
	void setMoveReady(bool Ready) { MoveReady = Ready; }
	bool getMoveReady() { return MoveReady; }

	void setRadius(float newRadius) { Radius = newRadius; }
	float getRadius() { return Radius; }

	UPROPERTY(EditAnywhere)
		FVector DefaultPostion;
		
};
