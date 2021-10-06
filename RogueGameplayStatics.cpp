// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueGameplayStatics.h"

void URogueGameplayStatics::PlusGameStartCounter() {
	GameStartCounter++;
}

int32 URogueGameplayStatics::GetGameStartCounter() {
	return GameStartCounter;
}

void URogueGameplayStatics::SetGameStartCounter(int32 newCounter) {
	GameStartCounter = newCounter;
}