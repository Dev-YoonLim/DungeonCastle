// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieEnemy.h"

AZombieEnemy::AZombieEnemy() {
	BodyInit();
	StatInit();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AZombieEnemy::EnterBeginOverlap);
}

void AZombieEnemy::BeginPlay()
{
	Super::BeginPlay();
	PostInitializeComponents();
}

// Called every frame
void AZombieEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieEnemy::PostInitializeComponents() {
	Super::PostInitializeComponents();
	SetHumanoidAnim = GetMesh()->GetAnimInstance();
	HumanoidAnim = Cast<UHumanoidEnemyAniminstance>(SetHumanoidAnim);
}

void AZombieEnemy::Idle() {
	//HumanoidAnim->ZombieIdlePlay();
}

void AZombieEnemy::Walking() {
	//HumanoidAnim->ZombieWalkPlay();
}

void AZombieEnemy::Attack() {
	//HumanoidAnim->ZombieAttackPlay();
}

void AZombieEnemy::Die() {
	//HumanoidAnim->ZombieDiePlay();
}

/*void AZombieEnemy::Hit() {
	//Super::Hit();
	//if (TakeHitState == 0)
}*/


void AZombieEnemy::Dodge() {

}

void AZombieEnemy::BodyInit() {
	//Super::BodyInit();
	/*auto BodyAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>
		(TEXT("SkeletalMesh'/Game/HumanoidEnemy/Zombie/Default/ybot.ybot'"));
	if (BodyAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(BodyAsset.Object);
	}*/

}

void AZombieEnemy::StatInit() {
	//Super::StatInit();
	auto AnimAsset = ConstructorHelpers::FClassFinder<UAnimInstance>
		(TEXT("AnimBlueprint'/Game/HumanoidEnemy/Zombie/Default/AnimInstance/ZombieAnim.ZombieAnim_C'"));
	if (AnimAsset.Succeeded()) {
		GetMesh()->SetAnimClass(AnimAsset.Class);
	}
	/*else {
		auto AnimAsset = ConstructorHelpers::FClassFinder<UAnimInstance>
			(TEXT("AnimBlueprint'/Game/HumanoidEnemy/Zombie/Default/AnimInstance/ZobieAnimInstance_2.ZobieAnimInstance_2_C'"));
		if (AnimAsset.Succeeded()) {
			GetMesh()->SetAnimClass(AnimAsset.Class);
		}
	}*/
}

void AZombieEnemy::EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("EnemyHitHitHit")));
	//Hit();
}

void AZombieEnemy::NotifyActorBeginOverlap(AActor* OtherActor) {
	RogueTorch = Cast<ARogueTorch>(OtherActor);
	RogueWeapon = Cast<ARogueWeapon>(OtherActor);
	//WeaponOwner = Cast<ARogue>(RogueWeapon->GetOwner());
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("TorchAttackState %d"), RogueTorch->GetAttackState()));
	//TorchOwner = Cast<ARogue>(RogueTorch->GetOwner());
	/*if (RogueTorch) {
		HumanoidAnim->ZombieHitPlay();
		Hit();
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("TorchHit")));
	}
	if (RogueWeapon) {
		HumanoidAnim->ZombieHitPlay();
		Hit();
		GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("WeaponHit")));
	}*/
	//Hit();
	//Super::NotifyActorEndOverlap(OtherActor);
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("EnemyHitHitHit")));

}