// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueZone.h"

ADialogueZone::ADialogueZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EventBox->SetCollisionProfileName(TEXT("DialogueEvent"));
	DeathZoneNumber = -1;
}

// Called when the game starts or when spawned
void ADialogueZone::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADialogueZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}