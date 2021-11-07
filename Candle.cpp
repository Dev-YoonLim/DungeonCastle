// Fill out your copyright notice in the Description page of Project Settings.


#include "Candle.h"

// Sets default values
ACandle::ACandle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CandleSetRefInit();
	CandleLightInit();
	CandleMeshInit();
}

void ACandle::CandleSetRefInit() {
	CandleSetIndex = FMath::RandRange(0, 5);
	switch (CandleSetIndex) {
	case 0:
		CandleSetRef = TEXT("StaticMesh'/Game/Candle/Candle_0.Candle_0'");
		break;
	case 1:
		CandleSetRef = TEXT("StaticMesh'/Game/Candle/Candle_1.Candle_1'");
		break;
	case 2:
		CandleSetRef = TEXT("StaticMesh'/Game/Candle/Candle_2.Candle_2'");
		break;
	case 3:
		CandleSetRef = TEXT("StaticMesh'/Game/Candle/Candle_3.Candle_3'");
		break;
	case 4:
		CandleSetRef = TEXT("StaticMesh'/Game/Candle/Candle_4.Candle_4'");
		break;
	case 5:
		CandleSetRef = TEXT("StaticMesh'/Game/Candle/Candle_5.Candle_5'");
		break;
	}
}

void ACandle::CandleMeshInit() {
	CandleMesh = CreateDefaultSubobject<UStaticMeshComponent>("CandleMesh");
	auto CandleMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(CandleSetRef);
	if (CandleMeshAsset.Succeeded()) {
		CandleMesh->SetStaticMesh(CandleMeshAsset.Object);
	}
	CandleMesh->AttachToComponent(LightParticle, FAttachmentTransformRules::KeepRelativeTransform);
	CandleMesh->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));
	if (CandleSetIndex == 0 || CandleSetIndex == 3 || CandleSetIndex == 4) {
		CandleMesh->AddRelativeLocation(FVector(-35.f, 0, 0));
	}
	else {
		CandleMesh->AddRelativeLocation(FVector(35.f, 0, 0));
	}
}

void ACandle::CandleLightInit() {
	LightParticle = CreateDefaultSubobject<UParticleSystemComponent>("LightParticle");
	auto LightParticleAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/Candle/UpLight_5.UpLight_5'"));
	if (LightParticleAsset.Succeeded()) {
		LightParticle->SetTemplate(LightParticleAsset.Object);
	}
	LightParticle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LightParticle->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
}

// Called when the game starts or when spawned
void ACandle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

