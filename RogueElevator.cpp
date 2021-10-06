// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueElevator.h"
#include "Rogue.h"

// Sets default values
ARogueElevator::ARogueElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Elevatorinit();
	SwitchBlockinit();
	Switchinit();
}

// Called when the game starts or when spawned
void ARogueElevator::BeginPlay()
{
	Super::BeginPlay();
	MoveSoundComponent->Stop();
	
}

// Called every frame
void ARogueElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ElevatorMove();
	SwitchMove();
}

void ARogueElevator::NotifyActorBeginOverlap(AActor* Rogue) {
	ARogue* myRogue = Cast<ARogue>(Rogue);
	if (myRogue) {
		SwitchAction = true;
		if (Move != true) {
			Vibrations->setMoveReady(true);
			Move = true;
			if (Upfloor == false) {
				setElevatorSpeed(0.1f);
				setElevatorAxel(0.005f);
			}
			else {
				setElevatorSpeed(-0.1f);
				setElevatorAxel(-0.005f);
			}
		}
	}
}

void ARogueElevator::NotifyActorEndOverlap(AActor* Rogue) {
	//SwitchAction = false;
}

bool ARogueElevator::ElevatorStopState() {
	if (Elevator->GetRelativeLocation().Z >= UpStopZone->GetRelativeLocation().Z) {
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, (TEXT("Stop")));
		Upfloor = true;
		Stop = true;
		UGameplayStatics::PlaySoundAtLocation(this, StartStopSound, GetActorLocation());
		MoveSoundComponent->Stop();
		//UGameplayStatics::
		MoveStart = true;
		//setElevatorSpeed(0.f);
	}
	else if (Elevator->GetRelativeLocation().Z <= DownStopZone->GetRelativeLocation().Z) {
		Upfloor = false;
		Stop = true;
		UGameplayStatics::PlaySoundAtLocation(this, StartStopSound, GetActorLocation());
		MoveSoundComponent->Stop();
		MoveStart = true;
		//setElevatorSpeed(0.f);
	}
	else
		Stop = false;
	return Stop;
}

void ARogueElevator::ElevatorMove() {
	if (Move == true) {
		if (MoveStart == true) {
			UGameplayStatics::PlaySoundAtLocation(this, StartStopSound, GetActorLocation());
			MoveSoundComponent->Play();
			//UGameplayStatics::PlaySoundAtLocation(this, MoveSoundComponent->Sound, GetActorLocation());
			MoveStart = false;
		}
		if (getElevatorSpeed() < 1.5f && getElevatorSpeed() > -1.5f) {
			setElevatorSpeed(getElevatorSpeed() + getElevatorAxel());
			Vibrations->setRadius(1.f);
		}
		else
			Vibrations->setRadius(0.5f);
		
		Elevator->AddRelativeLocation(FVector(0, 0, getElevatorSpeed()));
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("%f"), ElevatorSpeed));
		if (ElevatorStopState() == true) {
			Vibrations->setMoveReady(false);
			Move = false;
			SwitchAction = false;
			Elevator->AddRelativeLocation(FVector(0, 0, -5*getElevatorSpeed()));
		}
	}
}

void ARogueElevator::SwitchMove() {
	if (SwitchAction == true && Move == true) {
		if (SwitchLen > -4.f) {
			SwitchBlock->AddRelativeLocation(FVector(0, 0, -0.2));
			SwitchBlockUpfloor->AddRelativeLocation(FVector(0, 0, -0.2));
			SwitchBlockDownfloor->AddRelativeLocation(FVector(0, 0, -0.2));
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("%f"), SwitchLen));
			SwitchLen -= 0.05;
			//if(SwitchLen < -4.f)
		}
	}
	else if (SwitchAction == false && Stop == true) {
		if (SwitchLen < 0.f) {
			SwitchBlock->AddRelativeLocation(FVector(0, 0, 0.2));
			SwitchBlockUpfloor->AddRelativeLocation(FVector(0, 0, 0.2));
			SwitchBlockDownfloor->AddRelativeLocation(FVector(0, 0, 0.2));
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("%f"), SwitchLen));
			SwitchLen += 0.05;
		}
	}
}


void ARogueElevator::Elevatorinit() {
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Elevator = CreateDefaultSubobject<UStaticMeshComponent>("Elevator");
	UpStopZone = CreateDefaultSubobject<USceneComponent>("UpStopZone");
	DownStopZone = CreateDefaultSubobject<USceneComponent>("DownStopZone");
	Vibrations = CreateDefaultSubobject<UVibration>("Vibrations");
	MoveSoundComponent = CreateDefaultSubobject<UAudioComponent>("MoveSound");
	auto ElevatorAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/LevelVehicle/Elevator.Elevator'"));

	if (ElevatorAsset.Succeeded()) {
		Elevator->SetStaticMesh(ElevatorAsset.Object);
	}
	RootComponent = Root;
	UpStopZone->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	DownStopZone->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Elevator->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	MoveSoundComponent->AttachToComponent(Elevator, FAttachmentTransformRules::KeepRelativeTransform);
	Elevator->SetCollisionProfileName(TEXT("BlockAll"));

	auto StartSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Elevator/Muchine_Cue.Muchine_Cue'"));
	auto MoveSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Elevator/Muchine_Move_Cue.Muchine_Move_Cue'"));
	auto MoveSoundCompAsset = ConstructorHelpers::FObjectFinder<USoundBase>
		(TEXT("SoundWave'/Game/Sound/SoundSource/NewMuchine_Move.NewMuchine_Move'"));

	if (StartSoundAsset.Succeeded()) {
		StartStopSound = StartSoundAsset.Object;
	}
	if (MoveSoundAsset.Succeeded()) {
		MoveSound = MoveSoundAsset.Object;
	}
	if (MoveSoundCompAsset.Succeeded()) {
		MoveSoundComponent->SetSound(MoveSoundCompAsset.Object);
	}
	//MoveSound->GetSoundWavesWithCookedAnalysisData(MoveSoundComponent);
	//MoveSoundComponent->
	MoveStart = true;
}

void ARogueElevator::SwitchBlockinit() {
	SwitchBlock = CreateDefaultSubobject<UStaticMeshComponent>("SwitchBlock");
	SwitchBlockUpfloor = CreateDefaultSubobject<UStaticMeshComponent>("SwtichBlockUpfloor");
	SwitchBlockDownfloor = CreateDefaultSubobject<UStaticMeshComponent>("SwitchBlockDownfloor");
	SwitchHall = CreateDefaultSubobject<UStaticMeshComponent>("SwitchHall");

	auto SwitchBlockAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/LevelVehicle/Switch_Block.Switch_Block'"));

	auto SwitchHallAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/LevelVehicle/Switch_Block_2.Switch_Block_2'"));

	if (SwitchBlockAsset.Succeeded()) {
		SwitchBlock->SetStaticMesh(SwitchBlockAsset.Object);
		SwitchBlockUpfloor->SetStaticMesh(SwitchBlockAsset.Object);
		SwitchBlockDownfloor->SetStaticMesh(SwitchBlockAsset.Object);
	}
	if (SwitchHallAsset.Succeeded()) {
		SwitchHall->SetStaticMesh(SwitchHallAsset.Object);
	}
	SwitchBlock->AttachToComponent(Elevator, FAttachmentTransformRules::KeepRelativeTransform);
	SwitchBlockUpfloor->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	SwitchBlockDownfloor->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	SwitchBlock->AddRelativeLocation(FVector(0, 0, 10));
	SwitchHall->AttachToComponent(Elevator, FAttachmentTransformRules::KeepRelativeTransform);
}

void ARogueElevator::Switchinit() {
	Switch = CreateDefaultSubobject<UBoxComponent>("Switch");
	SwitchUpfloor = CreateDefaultSubobject<UBoxComponent>("SwitchUpfloor");
	SwitchDownfloor = CreateDefaultSubobject<UBoxComponent>("SwitchDownfloor");
	
	Switch->SetBoxExtent(FVector(20, 20, 10));
	SwitchUpfloor->SetBoxExtent(FVector(20, 20, 10));
	SwitchDownfloor->SetBoxExtent(FVector(20, 20, 10));
	
	Switch->AttachToComponent(SwitchBlock, FAttachmentTransformRules::KeepRelativeTransform);
	SwitchUpfloor->AttachToComponent(SwitchBlockUpfloor, FAttachmentTransformRules::KeepRelativeTransform);
	SwitchDownfloor->AttachToComponent(SwitchBlockDownfloor, FAttachmentTransformRules::KeepRelativeTransform);
}

void ARogueElevator::ElevatorStateinit() {
	Stop = true;
	Move = false;
	Upfloor = false;
	SwitchAction = false;
	SwitchLen = 0.f;
	setElevatorSpeed(0.f);
	setElevatorAxel(0.005f);
}
