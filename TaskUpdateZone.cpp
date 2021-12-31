// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskUpdateZone.h"

// Sets default values
ATaskUpdateZone::ATaskUpdateZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TaskUpdateBox = CreateDefaultSubobject<UBoxComponent>("TaskUpdateBox");
	TaskUpdateBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TaskUpdateNumber = 0;
}

// Called when the game starts or when spawned
void ATaskUpdateZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATaskUpdateZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATaskUpdateZone::NotifyActorBeginOverlap(AActor* myRogue) {
	ARogue* Rogue = Cast<ARogue>(myRogue);
	if (Rogue) {
		Rogue->MyRogueState->TaskLevel = TaskUpdateNumber;
		Rogue->MyGameMode->MainUIUpdate();
	}
}

