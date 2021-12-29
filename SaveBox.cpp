// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveBox.h"

// Sets default values
ASaveBox::ASaveBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SaveCheckBox = CreateDefaultSubobject<UBoxComponent>("SaveBox");
	SaveCheckBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASaveBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASaveBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASaveBox::NotifyActorBeginOverlap(AActor* myRogue) {
	ARogue* Rogue = Cast<ARogue>(myRogue);
	if (myRogue) {
		Rogue->MyRogueState->SetSaveState(true);
	}
}

