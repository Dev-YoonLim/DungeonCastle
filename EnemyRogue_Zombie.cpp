// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyRogue_Zombie.h"

AEnemyRogue_Zombie::AEnemyRogue_Zombie() {
	EnemyRogueBodyInit();
	AnimBlendInit();
}

void AEnemyRogue_Zombie::EnemyRogueBodyInit() {
	auto MeshAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>
		(TEXT("SkeletalMesh'/Game/HumanoidEnemy/Zombie/Default/ybot.ybot'"));
	GetMesh()->SetSkeletalMesh(MeshAsset.Object);
}

void AEnemyRogue_Zombie::AnimBlendInit() {
	auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
		(TEXT("AnimBlueprint'/Game/HumanoidEnemy/Zombie/Default/AnimInstance/ZombieAnim.ZombieAnim_C'"));
	if (BlandAnim.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
		GetCharacterMovement()->MaxWalkSpeed = 75.f;
		HitCountLimite = 10;
		HitSuperArmorCount = 0;
		HitSuperArmorCountLimit = 1;
	}
}