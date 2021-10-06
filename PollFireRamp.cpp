// Fill out your copyright notice in the Description page of Project Settings.


#include "PollFireRamp.h"

// Sets default values
APollFireRamp::APollFireRamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BigLamp = CreateDefaultSubobject<UStaticMeshComponent>("BigLamp");
	Fire = CreateDefaultSubobject<UParticleSystemComponent>("Fire");

	auto BigLampAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Level/FireRamp.FireRamp'"));
	auto FireAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/Level/Fire_03.Fire_03'"));
	if (BigLampAsset.Succeeded())
		BigLamp->SetStaticMesh(BigLampAsset.Object);
	if (FireAsset.Succeeded())
		Fire->SetTemplate(FireAsset.Object);
	auto FireSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Fire/Lamp1_Cue.Lamp1_Cue'"));
	if (FireSoundAsset.Succeeded()) {
		SoundCue = FireSoundAsset.Object;
	}

	BigLamp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Fire->AttachToComponent(BigLamp, FAttachmentTransformRules::KeepRelativeTransform);
	Fire->SetRelativeScale3D(FVector(3.5, 3.5, 3.5));
	Fire->AddRelativeLocation(FVector(0, 0, -100.f));
}

// Called when the game starts or when spawned
void APollFireRamp::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this, SoundCue, GetActorLocation());
}

// Called every frame
void APollFireRamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

