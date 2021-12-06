// Fill out your copyright notice in the Description page of Project Settings.


#include "StartItem.h"

AStartItem::AStartItem() {
	ItemMeshInit();
	ParticleInit();
	CapsuleInit();
	SoundInit();
}

void AStartItem::BeginPlay() {
	Super::BeginPlay();
}

void AStartItem::GameStartSetting() {

}

void AStartItem::SoundInit() {
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

void AStartItem::NotifyActorBeginOverlap(AActor* OtherActor) {
	myRogue = Cast<ARogue>(OtherActor);
	if (myRogue) {
		UGameplayStatics::PlaySoundAtLocation(this, GetItemSound, GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TakeItem, GetActorTransform());
		Destroy();
	}
}

void AStartItem::CapsuleInit() {
	TakeItemRange1 = CreateDefaultSubobject<UCapsuleComponent>("ItemCapsule1");
	TakeItemRange1->SetCapsuleRadius(50);
	TakeItemRange1->SetCapsuleHalfHeight(70);
	TakeItemRange1->SetCollisionProfileName("EventZoneCollision");
	TakeItemRange1->AttachToComponent(ItemMesh1, FAttachmentTransformRules::KeepRelativeTransform);

	TakeItemRange2 = CreateDefaultSubobject<UCapsuleComponent>("ItemCapsule2");
	TakeItemRange2->SetCapsuleRadius(50);
	TakeItemRange2->SetCapsuleHalfHeight(70);
	TakeItemRange2->SetCollisionProfileName("EventZoneCollision");
	TakeItemRange2->AttachToComponent(ItemMesh2, FAttachmentTransformRules::KeepRelativeTransform);

	TakeItemRange3 = CreateDefaultSubobject<UCapsuleComponent>("ItemCapsule3");
	TakeItemRange3->SetCapsuleRadius(50);
	TakeItemRange3->SetCapsuleHalfHeight(70);
	TakeItemRange3->SetCollisionProfileName("EventZoneCollision");
	TakeItemRange3->AttachToComponent(ItemMesh3, FAttachmentTransformRules::KeepRelativeTransform);

	TakeItemRange4 = CreateDefaultSubobject<UCapsuleComponent>("ItemCapsule4");
	TakeItemRange4->SetCapsuleRadius(50);
	TakeItemRange4->SetCapsuleHalfHeight(70);
	TakeItemRange4->SetCollisionProfileName("EventZoneCollision");
	TakeItemRange4->AttachToComponent(ItemMesh4, FAttachmentTransformRules::KeepRelativeTransform);

	TakeItemRange5 = CreateDefaultSubobject<UCapsuleComponent>("ItemCapsule5");
	TakeItemRange5->SetCapsuleRadius(50);
	TakeItemRange5->SetCapsuleHalfHeight(70);
	TakeItemRange5->SetCollisionProfileName("EventZoneCollision");
	TakeItemRange5->AttachToComponent(ItemMesh5, FAttachmentTransformRules::KeepRelativeTransform);
}

void AStartItem::ParticleInit() {
	auto ItemParticleAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/Level/Fire_4.Fire_4'"));
	ItemParticle1 = CreateDefaultSubobject<UParticleSystemComponent>("ItemParticle1");
	if (ItemParticleAsset.Succeeded()) {
		ItemParticle1->SetTemplate(ItemParticleAsset.Object);
	}
	ItemParticle1->AttachToComponent(ItemMesh1, FAttachmentTransformRules::KeepRelativeTransform);
	ItemParticle1->SetRelativeLocation(FVector(0, 0, -20.f));

	ItemParticle2 = CreateDefaultSubobject<UParticleSystemComponent>("ItemParticle2");
	if (ItemParticleAsset.Succeeded()) {
		ItemParticle2->SetTemplate(ItemParticleAsset.Object);
	}
	ItemParticle2->AttachToComponent(ItemMesh2, FAttachmentTransformRules::KeepRelativeTransform);
	ItemParticle2->SetRelativeLocation(FVector(0, 0, -20.f));

	ItemParticle3 = CreateDefaultSubobject<UParticleSystemComponent>("ItemParticle3");
	if (ItemParticleAsset.Succeeded()) {
		ItemParticle3->SetTemplate(ItemParticleAsset.Object);
	}
	ItemParticle3->AttachToComponent(ItemMesh3, FAttachmentTransformRules::KeepRelativeTransform);
	ItemParticle3->SetRelativeLocation(FVector(0, 0, -20.f));

	ItemParticle4 = CreateDefaultSubobject<UParticleSystemComponent>("ItemParticle4");
	if (ItemParticleAsset.Succeeded()) {
		ItemParticle4->SetTemplate(ItemParticleAsset.Object);
	}
	ItemParticle4->AttachToComponent(ItemMesh4, FAttachmentTransformRules::KeepRelativeTransform);
	ItemParticle4->SetRelativeLocation(FVector(0, 0, -20.f));

	ItemParticle5 = CreateDefaultSubobject<UParticleSystemComponent>("ItemParticle5");
	if (ItemParticleAsset.Succeeded()) {
		ItemParticle5->SetTemplate(ItemParticleAsset.Object);
	}
	ItemParticle5->AttachToComponent(ItemMesh5, FAttachmentTransformRules::KeepRelativeTransform);
	ItemParticle5->SetRelativeLocation(FVector(0, 0, -20.f));
	auto TakeItemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/Level/Fire_Exp_00.Fire_Exp_00'"));
	if (TakeItemAsset.Succeeded())
		TakeItem = TakeItemAsset.Object;
}

void AStartItem::ItemMeshInit() {
	auto ItemMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Level/ItemMeshBall.ItemMeshBall'"));
	ItemMesh1 = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh1");
	if (ItemMeshAsset.Succeeded()) {
		ItemMesh1->SetStaticMesh(ItemMeshAsset.Object);
	}
	ItemMesh1->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	ItemMesh2 = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh2");
	if (ItemMeshAsset.Succeeded()) {
		ItemMesh2->SetStaticMesh(ItemMeshAsset.Object);
	}
	ItemMesh2->AttachToComponent(ItemMesh1, FAttachmentTransformRules::KeepRelativeTransform);
	
	ItemMesh3 = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh3");
	if (ItemMeshAsset.Succeeded()) {
		ItemMesh3->SetStaticMesh(ItemMeshAsset.Object);
	}
	ItemMesh3->AttachToComponent(ItemMesh1, FAttachmentTransformRules::KeepRelativeTransform);
	
	ItemMesh4 = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh4");
	if (ItemMeshAsset.Succeeded()) {
		ItemMesh4->SetStaticMesh(ItemMeshAsset.Object);
	}
	ItemMesh4->AttachToComponent(ItemMesh1, FAttachmentTransformRules::KeepRelativeTransform);
	
	ItemMesh5 = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh5");
	if (ItemMeshAsset.Succeeded()) {
		ItemMesh5->SetStaticMesh(ItemMeshAsset.Object);
	}
	ItemMesh5->AttachToComponent(ItemMesh1, FAttachmentTransformRules::KeepRelativeTransform);
}

void AStartItem::TakeRogueInit() {
	AActor* myPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	myRogue = Cast<ARogue>(myPawn);
}

void AStartItem::TakeWorldInit() {
	AGameModeBase* myGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(myGameModeBase);
}