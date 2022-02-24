// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieEnemy.h"

AZombieEnemy::AZombieEnemy() {
	BodyInit();
	StatInit();
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
		(TEXT("SkeletalMesh'/Game/EnemyRogue/Animation/ybot.ybot'"));
	if (BodyAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(BodyAsset.Object);
	}
	GetMesh()->AddRelativeLocation(FVector(0, 0, -90));
	GetMesh()->AddRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetCollisionProfileName("EnemyRogueCollision");
}

void AZombieEnemy::StatInit() {
	EnemyHp *= EnemyHpCoe;
}