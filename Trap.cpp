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
	TrapPlaceMesh = CreateDefaultSubobject<UStaticMeshComponent>("TrapPlaceMesh");
	TrapHitBox = CreateDefaultSubobject<UBoxComponent>("TrapHitBox");
	TrapTriggerMesh = CreateDefaultSubobject<UStaticMeshComponent> ("TrapTriggerMesh");
	TrapTriggerBox = CreateDefaultSubobject<UBoxComponent>("TrapTriggerBox");

	TrapPlaceMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TrapHitBox->AttachToComponent(TrapPlaceMesh, FAttachmentTransformRules::KeepRelativeTransform);

	TrapTriggerMesh->AttachToComponent(TrapPlaceMesh, FAttachmentTransformRules::KeepRelativeTransform);
	TrapTriggerBox->AttachToComponent(TrapTriggerMesh, FAttachmentTransformRules::KeepRelativeTransform);

	
}

void ATrap::TrapDown() {
	//TrapTriggerMesh->AddRelativeLocation(FVector(0, 0, -5));
	//GetWorldTimerManager().SetTimer(TrapCountDown, this, ATrap::TrapStart, 1.f, false, 1.f);
}

void ATrap::TrapStart() {
	
}

void ATrap::EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

}