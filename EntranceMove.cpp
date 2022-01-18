// Fill out your copyright notice in the Description page of Project Settings.


#include "EntranceMove.h"
#include "Door.h"

// Sets default values for this component's properties
UEntranceMove::UEntranceMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Parents = GetOwner();
	MoveType = 0.f;
	MoveLenValue = 0.f;
	MaxMoveValue = 0.f;
	Open = false;
	//ParentDoor = Cast<ADoor>(Parent);
	// ...
}


// Called when the game starts
void UEntranceMove::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEntranceMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if (getMoveNumber() == 0.f)
		//setMoveLen(0.f);
	// ...
	if (getOpen() == false) {
		if (getMoveType() == 1.f) {
			Parents->AddActorLocalRotation(FRotator(0, getMoveLenValue(), 0));
			setMoveLenValue(getMoveLenValue() + 0.001f);
			
		}
		else if (getMoveType() == 2.f) {

			Parents->AddActorLocalTransform(FTransform(FRotator(0, 0, 0), 
				FVector(FMath::FRandRange(-0.6, 0.6), FMath::FRandRange(-0.6, 0.6), getMoveLenValue()), Parents->GetActorScale3D()));
			
			setMoveLenValue(getMoveLenValue() + 0.007f);
		}
		if (getMoveLenValue() > getMaxMoveValue()) {
			setMoveType(0.f);
			/*ADoor* Doors = Cast<ADoor>(Parents);
			Doors->MoveSoundComponent->Stop();
			//Parents->MoveSoundComponent->Stop();*/
			setOpen(true);
			ADoor* Doors = Cast<ADoor>(GetOwner());
			Doors->SoundStop();
		}
	}
}

