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
	
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrap::TrapInit() {
	TrapState = 0;
	TrapPlaceMesh = CreateDefaultSubobject<UStaticMeshComponent>("TrapPlaceMesh");
	TrapHitBox = CreateDefaultSubobject<UBoxComponent>("TrapHitBox");
	TrapTriggerMesh = CreateDefaultSubobject<UStaticMeshComponent> ("TrapTriggerMesh");
	TrapTriggerBox = CreateDefaultSubobject<UBoxComponent>("TrapTriggerBox");

	TrapPlaceMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TrapHitBox->AttachToComponent(TrapPlaceMesh, FAttachmentTransformRules::KeepRelativeTransform);

	TrapTriggerMesh->AttachToComponent(TrapPlaceMesh, FAttachmentTransformRules::KeepRelativeTransform);
	TrapTriggerBox->AttachToComponent(TrapTriggerMesh, FAttachmentTransformRules::KeepRelativeTransform);

	auto PlaceAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Level/TrapPlaceMesh.TrapPlaceMesh'"));
	if (PlaceAsset.Succeeded()) {
		TrapPlaceMesh->SetStaticMesh(PlaceAsset.Object);
	}

	auto TriggerAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Level/TrapTriggerMesh.TrapTriggerMesh'"));
	if (TriggerAsset.Succeeded()) {
		TrapTriggerMesh->SetStaticMesh(TriggerAsset.Object);
	}

	TrapTriggerBox->SetRelativeScale3D(FVector(0.8, 0.3, 1));
	
	TrapTriggerBox->SetCollisionProfileName(TEXT("TrapCollision"));
	TrapTriggerMesh->SetCollisionProfileName(TEXT("LevelDeco"));
	TrapHitBox->SetCollisionProfileName(TEXT("LevelDeco"));
	TrapPlaceMesh->SetCollisionProfileName(TEXT("LevelDeco"));
	//TrapPlaceMesh->SetCollisionProfileName(TEXT("LevelDeco"));
}

void ATrap::TrapDown() {
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("TrapDown")));
	TrapTriggerMesh->AddRelativeLocation(FVector(0, 0, -5));
	GetWorldTimerManager().SetTimer(TrapCountDown, this, &ATrap::TrapStart, 1.f, false, 1.f);
}

void ATrap::TrapStart() {
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("TrapStart")));
}

void ATrap::EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	ARogue* myRogue = Cast<ARogue>(OtherActor);
	if (myRogue && OverlappedComponent->GetCollisionProfileName() == TEXT("TrapCollision")) {
		TrapDown();
	}
}