// Fill out your copyright notice in the Description page of Project Settings.


#include "Vibration.h"

// Sets default values for this component's properties
UVibration::UVibration()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Radius = 2;
	Count = 0.f;
	MoveReady = false;
	// ...
}


// Called when the game starts
void UVibration::BeginPlay()
{
	Super::BeginPlay();
	AActor* Parent = GetOwner();
	DefaultPostion = Parent->GetActorLocation();
	// ...
	
}


// Called every frame
void UVibration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* Parent = GetOwner();
	if (Parent) {
		if (getMoveReady() == true) {
			Count = FMath::FRandRange(-1, 1);
			if(Count>-0.2 && Count < 0.2)
				Parent->SetActorLocation(DefaultPostion);
			else {
				auto newPostion = Parent->GetActorLocation() + FVector(FMath::FRandRange(-1, 1) * Radius,
					FMath::FRandRange(-1, 1) * Radius, FMath::FRandRange(-0.3, 0.3) * Radius);
				Parent->SetActorLocation(newPostion);
				//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("%f"), Count));
			}
		}
	}
}

