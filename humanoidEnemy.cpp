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
}

// Called when the game starts or when spawned
void AhumanoidEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AhumanoidEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AhumanoidEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AhumanoidEnemy::BodyInit() {

}
void AhumanoidEnemy::Working() {

}
void AhumanoidEnemy::Attack() {

}
void AhumanoidEnemy::Dodge() {

}
void AhumanoidEnemy::Idle() {

}
void AhumanoidEnemy::StatInit() {

}

