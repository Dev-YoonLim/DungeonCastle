// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMeshInit();
	CapsuleInit();
	ParticleInit();
	SoundInit();
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	TakeWorldInit();
	TakeRogueInit();
	ItemIndex = FMath::FRandRange(0, 99);
	UGameplayStatics::PlaySoundAtLocation(this, ItemIdleSound, GetActorLocation());
	APawn* myPawn = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//MyRogueState = Cast<ARogueState>(myPawn->GetPlayerState());
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap(OtherActor);
	myRogue = Cast<ARogue>(OtherActor);
	if (myRogue) {
		myRogue->MyRogueState->ItemCount++;
		if (myRogue->MyRogueState->ItemCount == 3) {
			myRogue->SetDialogueIndex(1);
			myRogue->MyRogueState->DialogueState[1] = 1;
			myRogue->DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL, myRogue->MyRogueState->FirstDialogueSourceRef[myRogue->GetDialogueIndex()]));
			myRogue->BeepCall();
		}
		UGameplayStatics::PlaySoundAtLocation(this, GetItemSound, GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TakeItem, GetActorTransform());
		Destroy();
	}
}

void AItem::NotifyActorEndOverlap(AActor* OtherActor) {
	Super::NotifyActorEndOverlap(OtherActor);
}

void AItem::CapsuleInit() {
	TakeItemRange = CreateDefaultSubobject<UCapsuleComponent>("ItemCapsule");
	TakeItemRange->SetCapsuleRadius(150);
	TakeItemRange->SetCapsuleHalfHeight(70);
	TakeItemRange->SetCollisionProfileName("EventZoneCollision");
	TakeItemRange->AttachToComponent(ItemMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

void AItem::SoundInit() {
	auto ItemIdleSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Fire/ItemIdle_Cue.ItemIdle_Cue'"));
	auto GetItemSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Fire/GetItemGuideLamp_Cue.GetItemGuideLamp_Cue'"));

	if (ItemIdleSoundAsset.Succeeded()) {
		ItemIdleSound = ItemIdleSoundAsset.Object;
	}
	if (GetItemSoundAsset.Succeeded()) {
		GetItemSound = GetItemSoundAsset.Object;
	}
}

void AItem::TakeRogueInit() {
	AActor* myPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	myRogue = Cast<ARogue>(myPawn);
}

void AItem::TakeWorldInit() {
	AGameModeBase* myGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(myGameModeBase);
}

void AItem::ItemMeshInit() {
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	auto ItemMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Level/ItemMeshBall.ItemMeshBall'"));
	if (ItemMeshAsset.Succeeded()) {
		ItemMesh->SetStaticMesh(ItemMeshAsset.Object);
	}
	ItemMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AItem::ParticleInit() {
	ItemParticle = CreateDefaultSubobject<UParticleSystemComponent>("ItemParticle");
	auto ItemParticleAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/Level/Fire_4.Fire_4'"));
	if (ItemParticleAsset.Succeeded()) {
		ItemParticle->SetTemplate(ItemParticleAsset.Object);
	}
	ItemParticle->AttachToComponent(ItemMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ItemParticle->SetRelativeLocation(FVector(0, 0, -20.f));

	auto TakeItemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/Level/Fire_Exp_00.Fire_Exp_00'"));
	if (TakeItemAsset.Succeeded())
		TakeItem = TakeItemAsset.Object;
}


ARogue* AItem::GetRogue() {
	if (myRogue)
		return myRogue;
	else
		return 0;
}

ACastle_in_DungeonGameModeBase* AItem::GetGameMode() {
	if (MyGameMode)
		return MyGameMode;
	else
		return 0;
}

UCapsuleComponent* AItem::GetCapsuleComponent() {
	if (TakeItemRange)
		return TakeItemRange;
	else
		return 0;
}

UStaticMeshComponent* AItem::GetItemMesh() {
	if (ItemMesh)
		return ItemMesh;
	else
		return 0;
}

UParticleSystemComponent* AItem::GetParticle() {
	if (ItemParticle)
		return ItemParticle;
	else
		return 0;
}
