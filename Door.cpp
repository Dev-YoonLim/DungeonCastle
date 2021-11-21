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
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::DoorInit() {
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	DoorOne = CreateDefaultSubobject<UStaticMeshComponent>("DoorOne");
	DoorSwitchOne = CreateDefaultSubobject<UBoxComponent>("DoorSwitchOne");
	DoorSwitchTwo = CreateDefaultSubobject<UBoxComponent>("DoorSwitchTwo");
	DoorWork = CreateDefaultSubobject<UEntranceMove>("DoorWork");
	Vibration = CreateDefaultSubobject<UVibration>("Vibration");

	auto DoorAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Door/DoorOne.DoorOne'"));
	auto DoorOpenSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Open/OpenDoor_Cue.OpenDoor_Cue'"));
	if (DoorAsset.Succeeded()) {
		DoorOne->SetStaticMesh(DoorAsset.Object);
	}
	if (DoorOpenSoundAsset.Succeeded()) {
		OpenDoorSound = DoorOpenSoundAsset.Object;
	}

	RootComponent = Root;
	DoorOne->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	DoorSwitchOne->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	DoorSwitchTwo->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void ADoor::OpenInit() {
	MaxValue = 2.5f;
}

void ADoor::NotifyActorBeginOverlap(AActor* OtherActor) {
	ARogue* Rogue = Cast<ARogue>(OtherActor);
	if (Rogue) {
		if (DoorWork->getOpen() == false) {
			DoorWork->setMaxMoveValue(MaxValue);
			DoorWork->setMoveType(SelectEntranceNumber);
			if (OpeningState == false) {
				UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation());
				OpeningState = true;
			}
		}
	}
}

void ADoor::EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}

void ADoor::NotEnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("%f"), MaxValue));
}
