// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Rogue.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoorInit();
	OpenInit();
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	MoveSoundComponent->Stop();
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
	URogueSaveGame* LoadGame = Cast<URogueSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (LoadGame == nullptr) {
		LoadGame = GetMutableDefault<URogueSaveGame>();
	}
	else {
		LoadGameData(LoadGame);
	}
}

void ADoor::LoadGameData(URogueSaveGame* LoadData) {
	URogueSaveGame* LoadGame = Cast<URogueSaveGame>(LoadData);
	if (LoadData->DoorOpenCheck[DoorNumbers] == 1 && DungeonKinds == 0)
		DoorOpen();

	//for(int i = 0; i < 3; i ++)
		//StoryProgress[i] = LoadGame->StoryProgress[i];
	//myRogue->SetActorLocation(LoadGame->LastLocation);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (DoorWork->getOpen() == true) {
		MoveSoundComponent->Stop();
	}*/


}

void ADoor::DoorInit() {
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	DoorOne = CreateDefaultSubobject<UStaticMeshComponent>("DoorOne");
	DoorSwitchOne = CreateDefaultSubobject<UBoxComponent>("DoorSwitchOne");
	DoorSwitchTwo = CreateDefaultSubobject<UBoxComponent>("DoorSwitchTwo");
	DoorWork = CreateDefaultSubobject<UEntranceMove>("DoorWork");
	Vibration = CreateDefaultSubobject<UVibration>("Vibration");
	MoveSoundComponent = CreateDefaultSubobject<UAudioComponent>("MoveSound");
	//DoorStateOne = CreateDefaultSubobject<UStaticMeshComponent>("DoorStateOne");
	//DoorStateTwo = CreateDefaultSubobject<UStaticMeshComponent>("DoorStateTwo");
	MoveSoundComponent->AttachToComponent(DoorOne, FAttachmentTransformRules::KeepRelativeTransform);
	auto DoorAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Door/DoorOne.DoorOne'"));
	auto DoorOpenSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Open/OpenDoor_Cue.OpenDoor_Cue'"));
	auto MoveSoundCompAsset = ConstructorHelpers::FObjectFinder<USoundBase>
		(TEXT("SoundWave'/Game/Sound/SoundSource/NewMuchine_Move.NewMuchine_Move'"));
	auto StartSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Elevator/Muchine_Cue.Muchine_Cue'"));
	if (DoorAsset.Succeeded()) {
		DoorOne->SetStaticMesh(DoorAsset.Object);
	}
	if (StartSoundAsset.Succeeded()) {
		OpenDoorSound = StartSoundAsset.Object;
	}
	if (MoveSoundCompAsset.Succeeded()) {
		MoveSoundComponent->SetSound(MoveSoundCompAsset.Object);
	}

	RootComponent = Root;
	DoorOne->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	DoorSwitchOne->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	DoorSwitchTwo->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void ADoor::OpenInit() {
	MaxValue = 2.5f;
	SaveSlotName = TEXT("SaveSlot");
}

void ADoor::NotifyActorBeginOverlap(AActor* OtherActor) {
	ARogue* Rogue = Cast<ARogue>(OtherActor);
	if (Rogue) {
		Rogue->MyRogueState->DoorStateCheck[DoorNumbers] = 1;
		if (Rogue->GameLoad == true)
			DoorLoad = true;
		DoorOpen();
	}
}

void ADoor::DoorOpen() {
	if (DoorWork->getOpen() == false) {
		DoorWork->setMaxMoveValue(MaxValue);
		DoorWork->setMoveType(SelectEntranceNumber);
		if (OpeningState == false) {
			if(DoorLoad == true)
				MoveSoundComponent->Play();
				//UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation());
			OpeningState = true;
			MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
		}
	}
}

void ADoor::SoundStop() {
	MoveSoundComponent->Stop();
	if (DoorLoad == true)
		UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation());
}

void ADoor::EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}

void ADoor::NotEnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("%f"), MaxValue));
}
