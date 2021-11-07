// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Rogue.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Castle_in_DungeonGameModeBase.h"
#include "MyRogueController.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API AMyRogueController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void GameControll();
	void UIControll();
	void ControllIndex(int32 index);

public:
	UPROPERTY(EditAnywhere)
		ACastle_in_DungeonGameModeBase* MyGameMode;

public:
	void WorldGameModeInit();
	void GameUIController();
	void AxisMapping(UPlayerInput* PlayerInputControll);
	void BindAxis_func();
	void virtual SetupInputComponent() override;

public:
	void OnStatWidget();
	void OnReSumeWidget();
	void OnTabWidget();
	void NotControll();
	void TurnDialogueWindow();

public:
	APawn* myPawn;
	UPlayerInput* PlayerInputControlls;
	ARogue* myRogue;
	//UInputComponent* PlayerInputComponents;
};
