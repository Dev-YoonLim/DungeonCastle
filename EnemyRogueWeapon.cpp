// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRogueWeapon.h"

// Sets default values
AEnemyRogueWeapon::AEnemyRogueWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyRogueWeaponInit();
	SetTakeHit(false);
}

// Called when the game starts or when spawned
void AEnemyRogueWeapon::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("EnemyWeaponOn")));
	//EnemyRogueWeaponInit();
	//EnemyRogueWeaponChange();
	//EnemyRgoueWeaponTransform();
}

// Called every frame
void AEnemyRogueWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyRogueWeapon::EnemyRogueWeaponInit() {
	EnemyRogueWeaponStatInit();
	EnemyRogueWeaponMeshInit();
}

void AEnemyRogueWeapon::EnemyRogueWeaponStatInit() {
	EnemyWeaponDamage = 1;
	EnemyWeaponSpeed = 1;
}

void AEnemyRogueWeapon::EnemyRogueWeaponMeshInit() {
	EnemyWeapons = CreateDefaultSubobject<UStaticMeshComponent>("EnemyWeapon");
	auto EnemyWeaponAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Weapons/Dagger.Dagger'"));
	if (EnemyWeaponAsset.Succeeded())
		EnemyWeapons->SetStaticMesh(EnemyWeaponAsset.Object);
	
	EnemyWeapons->SetCollisionProfileName("EnemyRogueWeaponCollision");
}

void AEnemyRogueWeapon::EnemyRogueWeaponChange(int32 SelectWeaponNumber) {
	//EnemyWeaponIndex = FMath::FRandRange(0, 8);
	EnemyWeaponIndex = SelectWeaponNumber;
	switch (EnemyWeaponIndex) {
	case 0:
		EnemyRogueWeaponRef
			= TEXT("StaticMesh'/Game/Weapons/Mace.Mace'");
		EnemyWeaponDamage = 2.f;
		EnemyWeaponSpeed = 1.1f;
		EnemyWeaponRange = 40.f / EnemyWeaponSpeed;
		break;
	case 1:
		EnemyRogueWeaponRef
			= TEXT("StaticMesh'/Game/Weapons/Mace.Mace'");
		EnemyWeaponDamage = 2.f;
		EnemyWeaponSpeed = 1.1f;
		EnemyWeaponRange = 40.f / EnemyWeaponSpeed;
		break;
	case 2:
		EnemyRogueWeaponRef
			= TEXT("StaticMesh'/Game/Weapons/G_Axe.G_Axe'");
		EnemyWeaponDamage = 3.f;
		EnemyWeaponSpeed = 0.8f;
		EnemyWeaponRange = 50.f / EnemyWeaponSpeed;
		break;
	case 3:
		EnemyRogueWeaponRef
			= TEXT("StaticMesh'/Game/Weapons/G_Hammer.G_Hammer'");
		EnemyWeaponDamage = 4.f;
		EnemyWeaponSpeed = 0.75f;
		EnemyWeaponRange = 50.f / EnemyWeaponSpeed;
		break;
	case 4:
		EnemyRogueWeaponRef
			= TEXT("StaticMesh'/Game/Weapons/G_Sword.G_Sword'");
		EnemyWeaponDamage = 2.5;
		EnemyWeaponSpeed = 0.85f;
		EnemyWeaponRange = 50.f / EnemyWeaponSpeed;
		break;
	case 5:
		EnemyRogueWeaponRef
			= TEXT("StaticMesh'/Game/Weapons/Axe.Axe'");
		EnemyWeaponDamage = 2.f;
		EnemyWeaponSpeed = 1.2;
		EnemyWeaponRange = 30.f / EnemyWeaponSpeed;
		break;
	case 6:
		EnemyRogueWeaponRef
			= TEXT("StaticMesh'/Game/Weapons/Axe.Axe'");
		EnemyWeaponDamage = 2.f;
		EnemyWeaponSpeed = 1.2;
		EnemyWeaponRange = 30.f / EnemyWeaponSpeed;
	case 7:
		EnemyRogueWeaponRef
			= TEXT("StaticMesh'/Game/Weapons/SM_Spear.SM_Spear'");
		EnemyWeaponDamage = 3.5f;
		EnemyWeaponSpeed = 0.75f;
		EnemyWeaponRange = 70.f / EnemyWeaponSpeed;
		break;
	case 8:
		EnemyRogueWeaponRef
			= TEXT("StaticMesh'/Game/Weapons/SM_Sickle.SM_Sickle'");
		EnemyWeaponDamage = 4.f;
		EnemyWeaponSpeed = 0.75f;
		EnemyWeaponRange = 70.f / EnemyWeaponSpeed;
		break;
	}
	UStaticMesh* NewWeapon = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, EnemyRogueWeaponRef));
	if (NewWeapon)
		EnemyWeapons->SetStaticMesh(NewWeapon);
	EnemyRgoueWeaponTransform();
}

void AEnemyRogueWeapon::EnemyRgoueWeaponTransform() {
	EnemyWeapons->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(1, 1, 1)));
	
	if (EnemyWeaponIndex == 2 || EnemyWeaponIndex == 6)
		EnemyWeapons->SetRelativeRotation(FRotator(0, 180, 0));
	if (EnemyWeaponIndex == 4) {
		EnemyWeapons->SetRelativeRotation(FRotator(180, 0, 0));
	}
	/*if (WeaponNumber == 9) {
		Weapon->SetRelativeRotation(FRotator(0, -20, 180));
		Weapon->SetRelativeLocation(FVector(3, -5, 0));
		Weapon->SetRelativeScale3D(FVector(0.5, 0.6, 0.5));
	}
	else
		Weapon->SetRelativeRotation(FRotator(0, 0, 0));
	*/

	if (EnemyWeaponIndex == 2 || EnemyWeaponIndex == 3)
		EnemyWeapons->SetRelativeScale3D(FVector(0.8, 0.8, 1));
	if (EnemyWeaponIndex == 4 || EnemyWeaponIndex == 7 || EnemyWeaponIndex == 8)
		EnemyWeapons->SetRelativeScale3D(FVector(1.1, 1.1, 1));
}

