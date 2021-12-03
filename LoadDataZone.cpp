// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadDataZone.h"

ALoadDataZone::ALoadDataZone() {
	EventBox->SetCollisionProfileName(TEXT("LoadData"));
}

void ALoadDataZone::BeginPlay() {
	Super::BeginPlay();
}

void ALoadDataZone::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}