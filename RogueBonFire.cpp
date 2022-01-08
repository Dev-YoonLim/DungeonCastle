// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBonFire.h"

// Sets default values
ARogueBonFire::ARogueBonFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshInit();
}

// Called when the game starts or when spawned
void ARogueBonFire::BeginPlay()
{
	Super::BeginPlay();
	GetWorldGameMode();
	WorldRogueInit();
	
}

// Called every frame
void ARogueBonFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogueBonFire::WorldRogueInit() {
	UWorld* TheWorld = GetWorld();
	AActor* myPawn = UGameplayStatics::GetPlayerPawn(TheWorld, 0);
	myRogue = Cast<ARogue>(myPawn);
}

void ARogueBonFire::GetWorldGameMode() {
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
}

void ARogueBonFire::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap(OtherActor);
	myRogue = Cast<ARogue>(OtherActor);
	if (myRogue && myRogue->GetDialogueSequence() == false) {
		MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(-(myRogue->MyRogueState->GetCurrentKarma() / 5));
		//myRogue->MyRogueState->SetCurrentKarma(100);
		MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(7);
		myRogue->myAnimInst->Idle();
	}
}

void ARogueBonFire::NotifyActorEndOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap(OtherActor);
	myRogue = Cast<ARogue>(OtherActor);
	if (myRogue) {
		
	}
}

void ARogueBonFire::MeshInit() {
	BonFireSword = CreateDefaultSubobject<UStaticMeshComponent>("BonFireSword");
	auto BonFireSwordAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/DataBornFire/Fire_Crucible_Frame_1.Fire_Crucible_Frame_1'"));

	if (BonFireSwordAsset.Succeeded()) {
		BonFireSword->SetStaticMesh(BonFireSwordAsset.Object);
	}
	
	BonFireFlame = CreateDefaultSubobject<UParticleSystemComponent>("BonFireFlame");
	auto BonFireFlameAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/DataBornFire/Fire_3.Fire_3'"));

	if (BonFireFlameAsset.Succeeded()) {
		BonFireFlame->SetTemplate(BonFireFlameAsset.Object);
	}

	BonFireCapsule = CreateDefaultSubobject<UCapsuleComponent>("BonFireCapsule");
	BonFireFlame->AttachToComponent(BonFireSword, FAttachmentTransformRules::KeepRelativeTransform);
	BonFireCapsule->AttachToComponent(BonFireSword, FAttachmentTransformRules::KeepRelativeTransform);
	BonFireCapsule->AddRelativeLocation(FVector(0, 0, 0));
	BonFireCapsule->SetCapsuleHalfHeight(80);
	BonFireCapsule->SetCapsuleRadius(180);
	BonFireCapsule->SetCollisionProfileName("BonFire");
	BonFireFlame->AddRelativeLocation(FVector(0, 0, -20));
	BonFireFlame->SetRelativeScale3D(FVector(0.6, 0.6, 0));
	BonFireSword->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	BonFireSword->AddRelativeLocation(FVector(0.f, 0.f, 10.f));
	BonFireSword->SetCollisionProfileName("BlockAll");
}
void ARogueBonFire::FireOn() {
	 
}
void ARogueBonFire::WidgetOn() {

}
