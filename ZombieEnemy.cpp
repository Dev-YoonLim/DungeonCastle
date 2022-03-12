// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieEnemy.h"

AZombieEnemy::AZombieEnemy() {
	BodyInit();
	StatInit();
}

void AZombieEnemy::PostInitializeComponents() {
	Super::PostInitializeComponents();
	SetHumanoidAnim = GetMesh()->GetAnimInstance();
	HumanoidAnim = Cast<UHumanoidEnemyAniminstance>(SetHumanoidAnim);
}

void AZombieEnemy::Idle() {

}

void AZombieEnemy::Working() {

}

void AZombieEnemy::Attack() {

}

void AZombieEnemy::Dodge() {

}

void AZombieEnemy::BodyInit() {
	auto BodyAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>
		(TEXT("SkeletalMesh'/Game/HumanoidEnemy/Zombie/Default/ybot.ybot'"));
	if (BodyAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(BodyAsset.Object);
	}
	GetMesh()->AddRelativeLocation(FVector(0, 0, -90));
	GetMesh()->AddRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetCollisionProfileName("EnemyRogueCollision");
}

void AZombieEnemy::StatInit() {
	EnemyHp *= EnemyHpCoe;
	FormNumber = 1;
	if (FormNumber == 0) {
		auto AnimAsset = ConstructorHelpers::FClassFinder<UAnimInstance>
			(TEXT("AnimBlueprint'/Game/HumanoidEnemy/Zombie/Default/AnimInstance/ZobieAnimInstance.ZobieAnimInstance_C'"));
		if (AnimAsset.Succeeded()) {
			GetMesh()->SetAnimClass(AnimAsset.Class);
		}
	}
	else {
		auto AnimAsset = ConstructorHelpers::FClassFinder<UAnimInstance>
			(TEXT("AnimBlueprint'/Game/HumanoidEnemy/Zombie/Default/AnimInstance/ZobieAnimInstance_2.ZobieAnimInstance_2_C'"));
		if (AnimAsset.Succeeded()) {
			GetMesh()->SetAnimClass(AnimAsset.Class);
		}
	}
}