// Fill out your copyright notice in the Description page of Project Settings.


#include "GuideFire.h"

// Sets default values
AGuideFire::AGuideFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LampInit();
	CapsuleInit();
}

void AGuideFire::LampInit() {
	GuideLamp = CreateDefaultSubobject<UStaticMeshComponent>("Lamp");
	Fire = CreateDefaultSubobject<UParticleSystemComponent>("Fire");
	LampPost = CreateDefaultSubobject<UStaticMeshComponent>("Post");

	auto GuideLampAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Level/FireRamp.FireRamp'"));
	if (GuideLampAsset.Succeeded())
		GuideLamp->SetStaticMesh(GuideLampAsset.Object);
	auto LampPostAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Level/SM_Forge_Armor_Rack.SM_Forge_Armor_Rack'"));
	if (LampPostAsset.Succeeded())
		LampPost->SetStaticMesh(LampPostAsset.Object);
	auto FireAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/Level/Fire_03.Fire_03'"));
	if (FireAsset.Succeeded())
		Fire->SetTemplate(FireAsset.Object);
	auto TakeItemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/Level/Fire_Exp_00.Fire_Exp_00'"));
	if (TakeItemAsset.Succeeded())
		TakeItem = TakeItemAsset.Object;
	auto FireSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Fire/Guide_Cue.Guide_Cue'"));
	if (FireSoundAsset.Succeeded()) {
		SoundCue = FireSoundAsset.Object;
	}
	auto GetItemSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Fire/GetGuideLamp_Cue.GetGuideLamp_Cue'"));
	if (GetItemSoundAsset.Succeeded()) {
		GetGuideLampSound = GetItemSoundAsset.Object;
	}

	LampPost->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	GuideLamp->AttachToComponent(LampPost, FAttachmentTransformRules::KeepRelativeTransform);
	Fire->AttachToComponent(GuideLamp, FAttachmentTransformRules::KeepRelativeTransform);

	LampPost->SetRelativeScale3D(FVector(2.f, 2.f, 2.5f));

	GuideLamp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	GuideLamp->AddRelativeLocation(FVector(0, 40.f, 125.f));

	Fire->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	Fire->AddRelativeLocation(FVector(0, 0, -100.f));
}

void AGuideFire::CapsuleInit(){
	TouchLampCapsule = CreateDefaultSubobject<UCapsuleComponent>("LampCapsule");
	TouchLampCapsule->AttachToComponent(GuideLamp, FAttachmentTransformRules::KeepRelativeTransform);
	TouchLampCapsule->SetCapsuleHalfHeight(80);
	TouchLampCapsule->SetCapsuleRadius(250);
	TouchLampCapsule->SetCollisionProfileName("EventZoneCollision");
}

// Called when the game starts or when spawned
void AGuideFire::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this, SoundCue, GetActorLocation());
}

// Called every frame
void AGuideFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGuideFire::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap(OtherActor);
	myRogue = Cast<ARogue>(OtherActor);
	if (myRogue && Check == false) {
		Check = true;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TakeItem, Fire->GetComponentTransform());
		UGameplayStatics::PlaySoundAtLocation(this, GetGuideLampSound, GetActorLocation());
		Fire->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
		SoundCue->VolumeMultiplier = 0.75;
	/*	UParticleSystem* FireOn = Cast<UParticleSystem>
			(StaticLoadObject(UParticleSystem::StaticClass(), NULL, TEXT("ParticleSystem'/Game/Level/Fire_03.Fire_03'")));
		if (FireOn)
			Fire->SetTemplate(FireOn);*/
	}
}

void AGuideFire::NotifyActorEndOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap(OtherActor);
	myRogue = Cast<ARogue>(OtherActor);
	if (myRogue) {
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("BonFireouttttttttt")));
	}
}

void AGuideFire::WorldRogueInit() {
	UWorld* TheWorld = GetWorld();
	AActor* myPawn = UGameplayStatics::GetPlayerPawn(TheWorld, 0);
	myRogue = Cast<ARogue>(myPawn);
}

void AGuideFire::GetWorldGameMode() {
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
}

