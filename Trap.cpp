// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TrapInit();
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	TrapTriggerSound->Stop();
	TrapStartSound->Stop();
	TrapTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATrap::EnterBeginOverlap);
	TrapHitBox->OnComponentBeginOverlap.AddDynamic(this, &ATrap::EnterBeginOverlap);
	TrapHitBox->OnComponentEndOverlap.AddDynamic(this, &ATrap::EnterEndOverlap);
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrap::TrapInit() {
	TrapState = -1;
	TrapCountLimit = 7;
	TrapLoopLimit = 9;
	TrapPlaceMesh = CreateDefaultSubobject<UStaticMeshComponent>("TrapPlaceMesh");
	TrapHitBox = CreateDefaultSubobject<UBoxComponent>("TrapHitBox");
	TrapTriggerMesh = CreateDefaultSubobject<UStaticMeshComponent> ("TrapTriggerMesh");
	TrapTriggerBox = CreateDefaultSubobject<UBoxComponent>("TrapTriggerBox");

	TrapTriggerSound = CreateDefaultSubobject<UAudioComponent>("TrapTriggerSound");
	TrapStartSound = CreateDefaultSubobject<UAudioComponent>("TrapStartSound");

	TrapPlaceMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TrapHitBox->AttachToComponent(TrapPlaceMesh, FAttachmentTransformRules::KeepRelativeTransform);

	TrapTriggerMesh->AttachToComponent(TrapPlaceMesh, FAttachmentTransformRules::KeepRelativeTransform);
	TrapTriggerBox->AttachToComponent(TrapTriggerMesh, FAttachmentTransformRules::KeepRelativeTransform);
	
	TrapTriggerSound->AttachToComponent(TrapTriggerMesh, FAttachmentTransformRules::KeepRelativeTransform);
	TrapStartSound->AttachToComponent(TrapPlaceMesh, FAttachmentTransformRules::KeepRelativeTransform);

	auto PlaceAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Level/TrapPlaceMesh.TrapPlaceMesh'"));
	if (PlaceAsset.Succeeded()) {
		TrapPlaceMesh->SetStaticMesh(PlaceAsset.Object);
	}

	auto TriggerAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Level/TrapTriggerMesh.TrapTriggerMesh'"));
	if (TriggerAsset.Succeeded()) {
		TrapTriggerMesh->SetStaticMesh(TriggerAsset.Object);
	}

	auto TrapEffectAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Level/Fire_5.Fire_5'"));
	if (TrapEffectAsset.Succeeded()) {
		TrapEffect = TrapEffectAsset.Object;
	}

	auto TriggerSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("SoundCue'/Game/Sound/SoundQue/Roll/TrapTrigger_Cue.TrapTrigger_Cue'"));
	if (TriggerSound.Succeeded()) {
		TrapTriggerSound->SetSound(TriggerSound.Object);
	}

	auto StartSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("SoundCue'/Game/Sound/SoundQue/Fire/TrapFire_Cue.TrapFire_Cue'"));
	if (StartSound.Succeeded()) {
		TrapStartSound->SetSound(StartSound.Object);
	}

	TrapTriggerBox->SetRelativeScale3D(FVector(0.8, 0.3, 1));
	TrapHitBox->SetRelativeScale3D(FVector(1.2, 1.2, 1.2));
	TrapTriggerBox->SetCollisionProfileName(TEXT("TrapCollision"));
	TrapTriggerMesh->SetCollisionProfileName(TEXT("LevelDeco"));
	TrapHitBox->SetCollisionProfileName(TEXT("TrapDamegeCollision"));
	TrapPlaceMesh->SetCollisionProfileName(TEXT("LevelDeco"));

	TrapTriggerBox->SetGenerateOverlapEvents(true);
	TrapHitBox->SetGenerateOverlapEvents(true);
	//TrapPlaceMesh->SetCollisionProfileName(TEXT("LevelDeco"));
}

void ATrap::TrapDown() {
	TrapTriggerSound->Play();
	TrapState = 0;
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("TrapDown")));
	TrapTriggerMesh->AddRelativeLocation(FVector(0, 0, -5));
	GetWorldTimerManager().SetTimer(TrapCountDown, this, &ATrap::TrapStart, 1.8f, true, 1.5f);
}

void ATrap::TrapStart() {
	TrapCount++;
	if (TrapState == 0) {
		if (TrapStartSound->IsPlaying() == false) {
			TrapStartSound->Play();
		}
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrapEffect, GetActorLocation(),
			FRotator(0, 0, 0), FVector(1.5f, 1.5f, 2.5f));
		if (HitOn == 1)
			TrapDamegeFunc();
		if(TrapCount >= TrapCountLimit)
			TrapState = 1;
	}
	else if (TrapState == 1) {
		TrapStartSound->Stop();
		if (HitOn == 1) {
			GetWorldTimerManager().ClearTimer(TrapDamegeCounter);
		}
		if (TrapCount >= TrapLoopLimit) {
			TrapCount = 0;
			TrapState = -1;
			TrapTriggerMesh->AddRelativeLocation(FVector(0, 0, 5));
			GetWorldTimerManager().ClearTimer(TrapCountDown);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("TrapStart")));
}

void ATrap::EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	myRogue = Cast<ARogue>(OtherActor);
	if (myRogue && OverlappedComponent->GetCollisionProfileName() == TEXT("TrapCollision") && TrapState == -1) {
		//myRogue->MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(50);
		TrapDown();
	}
	if (myRogue && OverlappedComponent->GetCollisionProfileName() == TEXT("TrapDamegeCollision")) {
		HitOn = 1;
		//GetWorldTimerManager().SetTimer(TrapDamegeCounter, this, &ATrap::TrapDamegeFunc, 1.f, true);
	}
}

void ATrap::EnterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	myRogue = Cast<ARogue>(OtherActor);
	if (myRogue && OverlappedComponent->GetCollisionProfileName() == TEXT("TrapDamegeCollision")) {
		HitOn = 0;
	}
}

void ATrap::TrapDamegeFunc() {
	myRogue->DeathZoneDamege();
	myRogue->MyGameMode->Call_SetStaticDataChangeDelegate.ExecuteIfBound(10);
}