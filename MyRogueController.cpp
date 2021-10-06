// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRogueController.h"

void AMyRogueController::WorldGameModeInit() {
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
	myPawn = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);
	myRogue = Cast<ARogue>(myPawn);
	MyGameMode->Widget_MouseCursorChangedDelegate.BindUObject(this, &AMyRogueController::ControllIndex);
}


void AMyRogueController::BeginPlay() {
	Super::BeginPlay();
	WorldGameModeInit();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("MyRogueControllerOk")));
	/*bEnableMouseOverEvents = true;
	bEnableClickEvents = false;*/
}

void AMyRogueController::SetupInputComponent() {
	Super::SetupInputComponent();
	GameUIController();
}

void AMyRogueController::GameControll() {
	bShowMouseCursor = false;
	MyGameMode->Widget_MouseCursorOnRogueNotInputDelegate.ExecuteIfBound(1);
	SetInputMode(FInputModeGameOnly());
}

void AMyRogueController::UIControll() {
	bShowMouseCursor = true;
	MyGameMode->Widget_MouseCursorOnRogueNotInputDelegate.ExecuteIfBound(0);
	SetInputMode(FInputModeGameAndUI());
}

void AMyRogueController::NotControll() {
	bShowMouseCursor = false;
	MyGameMode->Widget_MouseCursorOnRogueNotInputDelegate.ExecuteIfBound(0);
	SetInputMode(FInputModeUIOnly());
}

void AMyRogueController::ControllIndex(int32 index) {
	if (index == 0)
		GameControll();
	else if (index == 1)
		UIControll();
	else if (index == 2) {
		NotControll();
	}
}

void AMyRogueController::GameUIController() {
	PlayerInputControlls = GetWorld()->GetFirstPlayerController()->PlayerInput;
	AxisMapping(PlayerInputControlls);
	BindAxis_func();
}

void AMyRogueController::AxisMapping(UPlayerInput* PlayerInputControll) {
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Stat", EKeys::T));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("ESC", EKeys::Escape));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Tab", EKeys::Tab));

}

void AMyRogueController::BindAxis_func() {
	InputComponent->BindAction("Stat", IE_Pressed, this, &AMyRogueController::OnStatWidget);
	InputComponent->BindAction("ESC", IE_Pressed, this, &AMyRogueController::OnReSumeWidget);
	InputComponent->BindAction("Tab", IE_Pressed, this, &AMyRogueController::OnTabWidget);

}

void AMyRogueController::OnStatWidget() {
	if (MyGameMode->GetPageNumber() == 1) {
		MyGameMode->GetWidgetNumber(3);
		MyGameMode->GetWidgetNumber(4);
	}
	else if (MyGameMode->GetPageNumber() == 4) {
		MyGameMode->WidgetPop();
		MyGameMode->WidgetPop();
	}
}

void AMyRogueController::OnReSumeWidget() {
	if (MyGameMode->GetPageNumber() == 1)
		MyGameMode->GetWidgetNumber(2);
	else
		MyGameMode->WidgetPop();
}

void AMyRogueController::OnTabWidget() {
	if (MyGameMode->GetPageNumber() == 1)
		MyGameMode->GetWidgetNumber(3);
	else if (MyGameMode->GetPageNumber() == 3)
		MyGameMode->WidgetPop();
}