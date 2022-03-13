// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanoidEnemyAniminstance.h"


UHumanoidEnemyAniminstance::UHumanoidEnemyAniminstance() {

}

void UHumanoidEnemyAniminstance::NativeBeginPlay() {

}

void UHumanoidEnemyAniminstance::NativeUpdateAnimation(float DeltaSec) {

}

void UHumanoidEnemyAniminstance::ZombieAnimationInit() {
	auto ZombieIdle1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Idle/ZombieIdle1_Montage.ZombieIdle1_Montage'"));
	auto ZombieIdle2Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Idle/ZombieIdle2_Montage.ZombieIdle2_Montage'"));
	auto ZombieDie1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Die/ZombieDie_Montage.ZombieDie_Montage'"));
	auto ZombieDie2Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Die/ZombieDie_Montage_2.ZombieDie_Montage_2'"));
	auto ZombieWalk1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Move/ZombieWalk1_Montage.ZombieWalk1_Montage'"));
	auto ZombieWalk2Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Move/ZombieWalk2_Montage.ZombieWalk2_Montage'"));
	auto ZombieHit1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Hit/ZombieHit_Montage.ZombieHit_Montage'"));
	auto ZombieHit2Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Hit/ZombieHit_Montage_2.ZombieHit_Montage_2'"));
	auto ZombieAttack1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Attack/ZombieAttack1_Montage.ZombieAttack1_Montage'"));
	auto ZombieAttack2Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Attack/ZombieAttack2_Montage.ZombieAttack2_Montage'"));
	auto ZombieAttack3Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Attack/ZombieAttack3_Montage.ZombieAttack3_Montage'"));
	auto ZombieAttack4Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Attack/ZombieAttack4_Montage.ZombieAttack4_Montage'"));
	
	if (ZombieIdle1Asset.Succeeded()) {
		ZombieIdle1 = ZombieIdle1Asset.Object;
	}
	if (ZombieIdle2Asset.Succeeded()) {
		ZombieIdle2 = ZombieIdle2Asset.Object;
	}
	if (ZombieDie1Asset.Succeeded()) {
		ZombieDie1 = ZombieDie1Asset.Object;
	}
	if (ZombieDie2Asset.Succeeded()) {
		ZombieDie2 = ZombieDie2Asset.Object;
	}
	if (ZombieWalk1Asset.Succeeded()) {
		ZombieWalk1 = ZombieWalk1Asset.Object;
	}
	if (ZombieWalk2Asset.Succeeded()) {
		ZombieWalk2 = ZombieWalk2Asset.Object;
	}
	if (ZombieAttack1Asset.Succeeded()) {
		ZombieAttack1 = ZombieAttack1Asset.Object;
	}
	if (ZombieAttack2Asset.Succeeded()) {
		ZombieAttack2 = ZombieAttack2Asset.Object;
	}
	if (ZombieAttack3Asset.Succeeded()) {
		ZombieAttack3 = ZombieAttack3Asset.Object;
	}
	if (ZombieAttack4Asset.Succeeded()) {
		ZombieAttack4 = ZombieAttack4Asset.Object;
	}

}