// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenLevelBox.h"

// Sets default values
AOpenLevelBox::AOpenLevelBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OpenLevelZone = CreateDefaultSubobject<UBoxComponent>("OpenLevelZone");
	RootComponent = OpenLevelZone;
	//OpenLevelZone->OnComponentBeginOverlap.AddUniqueDynamic(this, &AOpenLevelBox::OverlapBegins);

}

// Called when the game starts or when spawned
void AOpenLevelBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOpenLevelBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOpenLevelBox::OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	ARogue* myRogue = Cast<ARogue>(OtherActor);
	if (myRogue) {
		//MoveLevel();
	}
}

void AOpenLevelBox::NotifyActorBeginOverlap(AActor* OtherActor) {
	ARogue* myRogue = Cast<ARogue>(OtherActor);
	if (myRogue) {
		MoveLevel();
	}
}

void AOpenLevelBox::MoveLevel() {
	FLatentActionInfo LatentInfo;
	//LevelToLoad = TEXT("Stage1");
	//UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);
	AGameModeBase* GameModeBase = Cast<AGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	ACastle_in_DungeonGameModeBase* MyGameMode = Cast< ACastle_in_DungeonGameModeBase>(GameModeBase);
	SubLevelIndex = FMath::FRandRange(0, 2);
	MyGameMode->GetStageIndex(LevelIndex, SubLevelIndex);
	MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
	MyGameMode->GetWidgetNumber(-2);
	/*switch (LevelIndex){
	case 0:
		UGameplayStatics::OpenLevel(this, FName(TEXT("Stage0")), false);
		break;
	case 1:
		MyGameMode->GetStageIndex(LevelIndex);
		MyGameMode->GetWidgetNumber(-2);
		//UGameplayStatics::OpenLevel(this, FName(TEXT("Stage1")), false);
		break;
	case 2:

		break;
	}*/
}

