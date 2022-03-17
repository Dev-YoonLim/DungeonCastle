// Fill out your copyright notice in the Description page of Project Settings.


#include "humanoidEnemy.h"

// Sets default values
AhumanoidEnemy::AhumanoidEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyHp = 50.f;
	EnemyHpCoe = 1.f;
	EnemyActionState = 0;
	TakeHitState = 0;
	BodyInit();
	StatInit();
}

// Called when the game starts or when spawned
void AhumanoidEnemy::BeginPlay()
{
	Super::BeginPlay();
	PostInitializeComponents();
}

// Called every frame
void AhumanoidEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AhumanoidEnemy::PostInitializeComponents() {
	Super::PostInitializeComponents();
	//SetHumanoidAnim = GetMesh()->GetAnimInstance();
	//HumanoidAnim = Cast<UHumanoidEnemyAniminstance>(SetHumanoidAnim);
}

// Called to bind functionality to input
void AhumanoidEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AhumanoidEnemy::BodyInit() {
	auto BodyAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>
		(TEXT("SkeletalMesh'/Game/HumanoidEnemy/Zombie/Default/ybot.ybot'"));
	if (BodyAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(BodyAsset.Object);
	}
	GetMesh()->AddRelativeLocation(FVector(0, 0, -90));
	GetMesh()->AddRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetCollisionProfileName("Enemy");
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("EnemyInit")));
}
void AhumanoidEnemy::Walking() {

}
void AhumanoidEnemy::Attack() {

}
void AhumanoidEnemy::Dodge() {

}
void AhumanoidEnemy::Idle() {

}
void AhumanoidEnemy::Die() {

}
void AhumanoidEnemy::Hit() {
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("EnemyHitHitHit")));
	//HumanoidAnim->ZombieHitPlay();
}

void AhumanoidEnemy::NotifyActorBeginOverlap(AActor* OtherActor) {
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("EnemyHitHitHit")));
	//Hit();
}
void AhumanoidEnemy::StatInit() {
	TakeHitState = 0;
	EnemyHp *= EnemyHpCoe;
	FormNumber = 1;
}

