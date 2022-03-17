// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanoidEnemyAniminstance.h"


UHumanoidEnemyAniminstance::UHumanoidEnemyAniminstance() {
	ZombieAnimationInit();
}

void UHumanoidEnemyAniminstance::NativeBeginPlay() {
	Super::NativeBeginPlay();
}

void UHumanoidEnemyAniminstance::NativeUpdateAnimation(float DeltaSec) {
	Super::NativeUpdateAnimation(DeltaSec);
}

void UHumanoidEnemyAniminstance::ZombieAnimationInit() {
	/*auto ZombieIdle1Asset = ConstructorHelpers::FObjectFinder<UAnimMontage>
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
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Hit/NewAnimMontage.NewAnimMontage'"));
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
	
	if (ZombieHit1Asset.Succeeded()) {
		ZombieHit1 = ZombieHit1Asset.Object;
	}
	if (ZombieHit2Asset.Succeeded()) {
		ZombieHit2 = ZombieHit2Asset.Object;
	}
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
	}*/
	auto ReactionAsset = ConstructorHelpers::FObjectFinder<UAnimMontage>
		(TEXT("AnimMontage'/Game/HumanoidEnemy/Zombie/Default/Animation/Reaction/Reaction.Reaction'"));
	if (ReactionAsset.Succeeded()) {
		Reactions = ReactionAsset.Object;
	}
}

void UHumanoidEnemyAniminstance::ZombieHitPlay() {
	Montage_Play(Reactions);
}

/*void UHumanoidEnemyAniminstance::ZombieIdlePlay() {
	if (Montage_IsPlaying(ZombieIdle1) == false && Montage_IsPlaying(ZombieIdle2) == false) {
		if (FMath::RandRange(0, 1) == 0) {
			Montage_Play(ZombieIdle1);
		}
		else {
			Montage_Play(ZombieIdle2);
		}
	}
}

void UHumanoidEnemyAniminstance::ZombieWalkPlay() {
	if (Montage_IsPlaying(ZombieWalk1) == false && Montage_IsPlaying(ZombieWalk2) == false) {
		if (FMath::RandRange(0, 1) == 0) {
			Montage_Play(ZombieWalk1);
		}
		else {
			Montage_Play(ZombieWalk2);
		}
	}
}

void UHumanoidEnemyAniminstance::ZombieAttackPlay() {
	if (Montage_IsPlaying(ZombieIdle1) == false && Montage_IsPlaying(ZombieIdle2) == false) {
		switch (FMath::RandRange(0, 3)) {
		case 0:
			Montage_Play(ZombieAttack1);
			break;
		case 1:
			Montage_Play(ZombieAttack2);
			break;
		case 2:
			Montage_Play(ZombieAttack3);
			break;
		case 3:
			Montage_Play(ZombieAttack4);
			break;
		}
	}
}

void UHumanoidEnemyAniminstance::ZombieHitPlay() {
	Montage_Play(ZombieHit1);
	//if (Montage_IsPlaying(ZombieHit1) == false && Montage_IsPlaying(ZombieHit2) == false) {
		
	//}
	/*if (FMath::RandRange(0, 1) == 0) {
		Montage_Play(ZombieHit1);
	}
	else {
		Montage_Play(ZombieHit2);
	}
}

void UHumanoidEnemyAniminstance::ZombieDiePlay() {
	if (Montage_IsPlaying(ZombieDie1) == false && Montage_IsPlaying(ZombieDie2) == false) {
		if (FMath::RandRange(0, 1) == 0) {
			Montage_Play(ZombieDie1);
		}
		else {
			Montage_Play(ZombieDie2);
		}
	}
}*/

void UHumanoidEnemyAniminstance::TestFun() {
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("EnemyHitHitHit123")));
}