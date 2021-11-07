// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonEnd.h"
#include "Rogue.h"

// Sets default values
ADungeonEnd::ADungeonEnd()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EndingBox = CreateDefaultSubobject<UBoxComponent>("EndingBox");
	EndingBox->SetCollisionProfileName("DungeonEnd");
	EndingBox->SetRelativeScale3D(FVector(8.f, 8.f, 8.f));
	EndingBox->AddRelativeLocation(FVector(0.f, 0.f, 430.f));
	DungeonFinishMesh = CreateDefaultSubobject<UStaticMeshComponent>("DungeonFinishMesh");
	auto DungeonFinishMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Level/DecoLamp/SM_Env_Fire_OddsnEnds_Pillar4.SM_Env_Fire_OddsnEnds_Pillar4'"));
	if (DungeonFinishMeshAsset.Succeeded()) {
		DungeonFinishMesh->SetStaticMesh(DungeonFinishMeshAsset.Object);
	}
	DungeonFinishMesh->AddRelativeRotation(FRotator(0.f, 90.f, 0.f));

	EndItem = CreateDefaultSubobject<UChildActorComponent>("EndItem");
	auto EndItemAsset = ConstructorHelpers::FClassFinder<AItem>
		(TEXT("Class'/Script/Castle_in_Dungeon.Item'"));
	if (EndItemAsset.Succeeded()) {
		EndItem->SetChildActorClass(EndItemAsset.Class);
	}
	DungeonFinishMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	EndingBox->AttachToComponent(DungeonFinishMesh, FAttachmentTransformRules::KeepRelativeTransform);
	EndItem->AttachToComponent(DungeonFinishMesh, FAttachmentTransformRules::KeepRelativeTransform);
	EndItem->AddRelativeLocation(FVector(0.f, 0.f, 430.f));
	EndItem->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

}

// Called when the game starts or when spawned
void ADungeonEnd::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonEnd::NotifyActorBeginOverlap(AActor* OtherActor) {
	ARogue* Rogue = Cast<ARogue>(OtherActor);
	AItem* Item = Cast<AItem>(EndItem);
	if (Rogue && Item) {
		Item->NotifyActorBeginOverlap(OtherActor);
	}
}

