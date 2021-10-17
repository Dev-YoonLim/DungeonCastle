// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueLevel.h"
#include "DungeonEnd.h"

// Sets default values
ARogueLevel::ARogueLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LevelFloorInit();
	DoorGuardPositionInit();
}

// Called when the game starts or when spawned
void ARogueLevel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogueLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogueLevel::DoorGuardPositionInit() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if(i == 0)
				DoorGuardFosition[i][j] = GetActorLocation() + FVector(-2700 + j*3000, -3900, 150);
			else if(i == 1)
				DoorGuardFosition[i][j] = GetActorLocation() + FVector(3900, -2700 + j*3000, 150);
			else if (i == 2)
				DoorGuardFosition[i][j] = GetActorLocation() + FVector(-3300 + j*3000, 3900, 150);
			else if (i == 3)
				DoorGuardFosition[i][j] = GetActorLocation() + FVector(-3900, -3300 + j*3000, 150);
		}
	}
}

void ARogueLevel::DoorGuard(int32 NextDirection, int32 DirectionIndex, int32 PreDirection, int32 PreDirectionIndex, bool Start) {
	int32 GuardCount = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (Start == true) {

			}
			if ((i != NextDirection || j != DirectionIndex) && (i != PreDirection || j != PreDirectionIndex)) {
				//GEngine->AddOnScreenDebugMessage(-1, 600, FColor::Orange, FString::Printf(TEXT("NextDoorCheck")));
				FloorDoorGuard[GuardCount]->SetRelativeLocation(DoorGuardFosition[i][j]);
				if (i == 1)
					FloorDoorGuard[GuardCount]->SetRelativeRotation(FRotator(0, 90, 0));
				else if (i == 2)
					FloorDoorGuard[GuardCount]->SetRelativeRotation(FRotator(0, 180, 0));
				else if (i == 3)
					FloorDoorGuard[GuardCount]->SetRelativeRotation(FRotator(0, 270, 0));
				if (GuardCount < 9)
					GuardCount++;
			}
			else if((i == NextDirection && j == DirectionIndex) && (i != PreDirection || j != PreDirectionIndex)){
				if (i == 0) {
					EndPointActor->SetRelativeLocation(GetActorLocation() + FVector(-2400 + j * 3000, -3900, 150));
				}
				//DoorGuardFosition[i][j] = GetActorLocation() + FVector(-2700 + j * 3000, -3900, 150);
				else if (i == 1) {
					EndPointActor->SetRelativeLocation(GetActorLocation() + FVector(3900, -2400 + j * 3000, 150));
					EndPointActor->SetRelativeRotation(FRotator(0, 90, 0));
				}
				else if (i == 2) {
					EndPointActor->SetRelativeLocation(GetActorLocation() + FVector(-3000 + j * 3000, 3900, 150));
				}
				else if (i == 3) {
					EndPointActor->SetRelativeLocation(GetActorLocation() + FVector(-3900, -3000 + j * 3000, 150));
					EndPointActor->SetRelativeRotation(FRotator(0, 90, 0));
				}
			}
		}
	}
}

void ARogueLevel::PreDoorGuard(int32 PreDirection, int32 DirectionIndex) {
	int32 GuardCount = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (i != PreDirection || j != DirectionIndex) {
				FloorDoorGuard[GuardCount]->SetRelativeLocation(DoorGuardFosition[i][j]);
			}
		}
	}
}

void ARogueLevel::LevelFloorInit() {
	LevelFloorStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("FloorMesh");
	for (int i = 0; i < 10; i++) {
		FloorDoorGuard[i] = CreateDefaultSubobject<UStaticMeshComponent>
			(FName(*FString::Printf(TEXT("FloorDoorGuard %d"), i)));
	}	
	auto FloorAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Level/LevelStageFloor.LevelStageFloor'"));
	if (FloorAsset.Succeeded()) {
		LevelFloorStaticMeshComp->SetStaticMesh(FloorAsset.Object);
	}

	auto DoorGuard = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Level/DoorGuard.DoorGuard'"));
	if (DoorGuard.Succeeded()) {
		for (int i = 0; i < 10; i++) {
			FloorDoorGuard[i]->SetStaticMesh(DoorGuard.Object);
			FloorDoorGuard[i]->AttachToComponent(LevelFloorStaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}

	EndPointActor = CreateDefaultSubobject<UChildActorComponent>("EndPoint");
	auto EndPointAsset = ConstructorHelpers::FClassFinder<ADungeonEnd>
		(TEXT("Class'/Script/Castle_in_Dungeon.DungeonEnd'"));
	if (EndPointAsset.Succeeded()) {
		EndPointActor->SetChildActorClass(EndPointAsset.Class);
	}
	//NaviMeshComp = CreateDefaultSubobject<ANavMeshBoundsVolume>("NavMesh");
	//NaviMeshComp->SetActorScale3D()
}