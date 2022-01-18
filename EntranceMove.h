// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntranceMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLE_IN_DUNGEON_API UEntranceMove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEntranceMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float MoveType;
	float MoveLenValue;
	float MaxMoveValue;
	bool Open;

public:
	void setMoveType(float newType) { MoveType = newType; }
	float getMoveType() { return MoveType; }

	void setMoveLenValue(float newMoveLenValue) { MoveLenValue = newMoveLenValue; }
	float getMoveLenValue() { return MoveLenValue; }

	void setMaxMoveValue(float newMaxMoveValue) { MaxMoveValue = newMaxMoveValue; }
	float getMaxMoveValue() { return MaxMoveValue; }

	void setOpen(bool OpenState) { Open = OpenState; }
	bool getOpen() { return Open; }
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		AActor* Parents;
		
};
