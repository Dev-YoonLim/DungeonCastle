// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueTorch.h"
#include "EnemyRogue.h"

// Sets default values
ARogueTorch::ARogueTorch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TorchStatusInit();
	TorchStick();
	TorchFire();
	TorchLight();
	TorchRightLeftCapsuleInit();
	TorchAttackEffectInit();
	setTorchArrive(true);
	setRightSide(true);
	TorchWallCrashDelegateInit();
}

// Called when the game starts or when spawned
void ARogueTorch::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("RogueTorchOn")));
	UGameplayStatics::PlaySoundAtLocation(this, IdleFireSound, GetActorLocation());
	WorldRogueInit();
	WorldGameModeInit();
	TorchChangeElementDelegateInit();
	TorchChangeElement(0, 1.f);
	//MyGameMode->Call_GameStartTorchElementalNumberDelegate.ExecuteIfBound();
}

void ARogueTorch::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	
	setTorchArrive(false);
}

// Called every frame
void ARogueTorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*GetOverlappingActors(EnemyArray, TSubclassOf<AEnemyRogue>());
	for (int32 Index = 0; Index != EnemyArray.Num(); Index++) {
		AEnemyRogue* Enemys = Cast<AEnemyRogue>(EnemyArray[Index]);
		
		if (Enemys->TakeTorchSpecial == true) {
			Enemys->SetHp(Enemys->ExplosionDamage);
			
		}
	}*/

}

void ARogueTorch::TorchStatusInit() {
	CanStabAttack = true;
	TorchHitCounter = 0.f;
	StabDamege = 20.f;
	BurnAttacksDamege = 3.f;
	ElementLevelValue = 1.f;
	/*TorchLevel = 1.f;
	TorchLevelValue = 1.0f + TorchLevel * 0.05;
	TorchLevelValueSize = FVector(TorchLevelValue, TorchLevelValue, TorchLevelValue);*/
	//TorchBurnAttacksHitValue = 1.f;
	TorchHitLimit = 3;
	for (int i = 0; i < 5; i++)
		SetTorchEffectsStack(0, i);
	auto FireSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/Fire/Torch_Cue.Torch_Cue'"));
	if (FireSoundAsset.Succeeded()) {
		IdleFireSound = FireSoundAsset.Object;
	}
}

void ARogueTorch::TorchStick() {
	FireStick = CreateDefaultSubobject<UStaticMeshComponent>("FireStick");

	auto FireStickAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/FireStick/FireStick_Ball2.FireStick_Ball2'"));

	if (FireStickAsset.Succeeded()) {
		FireStick->SetStaticMesh(FireStickAsset.Object);
	}
	FireStick->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(1.2, 1.2, 1.2)));
	FireStick->SetCollisionProfileName("RogueTorchsCollision");
}

void ARogueTorch::TorchFire() {
	FireEffect = CreateDefaultSubobject<UParticleSystemComponent>("Fire");
	FireEffectElement = CreateDefaultSubobject<UParticleSystemComponent>("FireEffect");

	auto FireEffectAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'"));


	if (FireEffectAsset.Succeeded()) {
		FireEffect->SetTemplate(FireEffectAsset.Object);
	}
	FireEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 42), FVector(0.17, 0.17, 0.1)));
	FireEffectElement->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 42), FVector(0.05, 0.05, 0.05)));
	FireEffect->AttachToComponent(FireStick, FAttachmentTransformRules::KeepRelativeTransform);
	FireEffectElement->AttachToComponent(FireStick, FAttachmentTransformRules::KeepRelativeTransform);
}

void ARogueTorch::TorchLight() {
	ExplosionSphere = CreateDefaultSubobject<USphereComponent>("ExplosionRange");
	FireLight = CreateDefaultSubobject<UPointLightComponent>("FireLight");
	FireLight->SetLightColor(FLinearColor(0.8, 0.2, 0, 0));
	FireLight->AttachToComponent(FireEffect, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionSphere->AttachToComponent(FireEffect, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionSphere->SetRelativeScale3D(FVector(30, 30, 30) * ElementLevelValue);
	ExplosionSphere->SetCollisionProfileName("RogueTorchsCollision");
	FireLight->SetAttenuationRadius(500.f);
}

void ARogueTorch::WorldRogueInit() {
	UWorld* TheWorld = GetWorld();
	AActor* myPawn = UGameplayStatics::GetPlayerPawn(TheWorld, 0);
	myRogue = Cast<ARogue>(myPawn);
}

void ARogueTorch::WorldGameModeInit() {
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
}

void ARogueTorch::TorchWallCrashDelegateInit() {
	FireStick->OnComponentBeginOverlap.AddDynamic(this, &ARogueTorch::EnterBeginOverlap);
	FireStick->OnComponentEndOverlap.AddDynamic(this, &ARogueTorch::EnterEndOverlap);
	RightCapsule->OnComponentBeginOverlap.AddDynamic(this, &ARogueTorch::EnterBeginOverlap);
	RightCapsule->OnComponentEndOverlap.AddDynamic(this, &ARogueTorch::EnterEndOverlap);
	LeftCapsule->OnComponentBeginOverlap.AddDynamic(this, &ARogueTorch::EnterBeginOverlap);
	LeftCapsule->OnComponentEndOverlap.AddDynamic(this, &ARogueTorch::EnterEndOverlap);
}

void ARogueTorch::TorchChangeElementDelegateInit() {
	MyGameMode->TorchElementChangeDelegate_.BindUObject(this, &ARogueTorch::TorchChangeElement);
	MyGameMode->TorchTotalDamegeDelegate.BindUObject(this, &ARogueTorch::GetTorchTotalDamege);
	//MyGameMode->RogueTorchLevelUpDelegate.BindUObject(this, &ARogueTorch::TorchLevelUp);
	MyGameMode->RogueElementLevelToTorchDelegate.BindUObject(this, &ARogueTorch::ElementLevelUp);
	MyGameMode->TorchBurnAttacksHitValueDelegate.BindUObject(this, &ARogueTorch::SetBurnAttackHitIncrease);
	MyGameMode->RogueTorchAttackFinishDelegate.BindUObject(this, &ARogueTorch::CheckTorchAttackFinish);
	MyGameMode->EnemyRogueEffectStateCheckDelegate.BindUObject(this, &ARogueTorch::StateEffectSpecialExplosionCheck);
	MyGameMode->RogueAttackVectorToEnemyRogueDelegate.AddUObject(this, &ARogueTorch::TakeAttackVector);
}

void ARogueTorch::TorchAttackEffectInit() {
	TorchElementNumber = 0;
	auto HitParticle = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/FireStick/TorchHitBurnAttacksEffect.TorchHitBurnAttacksEffect'"));
	if (HitParticle.Succeeded())
		TorchHitEffect = HitParticle.Object;

	auto CriParticle = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/FireStick/TorchHitBurnAttacksCriEffect.TorchHitBurnAttacksCriEffect'"));
	if (CriParticle.Succeeded())
		TorchHitBurnAttacksCriEffect = CriParticle.Object;
}

void ARogueTorch::TorchChangeElement(int32 ElementIndex, float SelectElementLevelValue) {
	ElementLevelValue = SelectElementLevelValue;
	TorchElementNumber = ElementIndex;
	TorchStateDefaultEffects[TorchElementNumber] = false;
	TorchTempDamegeValue = 1.f;
	ElementLevelValueSize = FVector(ElementLevelValue, ElementLevelValue, ElementLevelValue);
	switch (ElementIndex){
	case 0:
		FireEffectReference = TEXT("ParticleSystem'/Game/FireStick/P_ky_fireBall.P_ky_fireBall'");
		FireEffectElementReference = TEXT("ParticleSystem'/Game/FireStick/P_Buff_Char_TerraDrain_01.P_Buff_Char_TerraDrain_01'");
		FireBurnAttacksEffectReference = TEXT("ParticleSystem'/Game/FireStick/TorchHitBurnAttacksEffect.TorchHitBurnAttacksEffect'");
		FireBurnAttacksCriEffectReference = TEXT("ParticleSystem'/Game/FireStick/TorchHitBurnAttacksCriEffect.TorchHitBurnAttacksCriEffect'");
		FireLight->SetLightColor(FLinearColor(0.8, 0.2, 0, 0));
		FireLight->SetAttenuationRadius(500.f);
		StabDamege = 30.f;
		BurnAttacksDamege = 3.f ;
		BurnAttacksCriPer = 10.f;
		ElementSpecialDamegeDamege = 30.f;
		TorchAttackCostData = 2;
		break;
	case 1:
		FireEffectReference = TEXT("ParticleSystem'/Game/FireStick/Fire/P_ky_fireBall.P_ky_fireBall'");
		FireEffectElementReference = TEXT("ParticleSystem'/Game/FireStick/Fire/P_ky_fireStorm.P_ky_fireStorm'");
		FireBurnAttacksEffectReference = TEXT("ParticleSystem'/Game/FireStick/Fire/TorchHitBurnAttacksEffect_Fire.TorchHitBurnAttacksEffect_Fire'");
		FireBurnAttacksCriEffectReference = TEXT("ParticleSystem'/Game/FireStick/Fire/BurnAttacksCriIgnite_Explosion.BurnAttacksCriIgnite_Explosion'");
		FireEffectElement->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 41.3), FVector(0.07, 0.07, 0.07) * ElementLevelValueSize));
		FireLight->SetLightColor(FLinearColor(1, 0.3, 0, 0));
		FireLight->SetAttenuationRadius(700.f);
		StabDamege = 15.f;
		BurnAttacksDamege = 7.f;
		BurnAttacksCriPer = 15.f;
		ElementSpecialDamegeDamege = 40.f;
		TorchAttackCostData = 3;
		break;
	case 2:
		FireEffectReference = TEXT("ParticleSystem'/Game/FireStick/Ice/TorchIceBall.TorchIceBall'");
		FireEffectElementReference = TEXT("ParticleSystem'/Game/FireStick/Ice/TorchIdle_Ice.TorchIdle_Ice'");
		FireBurnAttacksEffectReference = TEXT("ParticleSystem'/Game/FireStick/Ice/P_Player_Frozen_Exit_01.P_Player_Frozen_Exit_01'");
		FireBurnAttacksCriEffectReference = TEXT("ParticleSystem'/Game/FireStick/Ice/P_ProjectileLob_Explo_Ice.P_ProjectileLob_Explo_Ice'");
		FireEffectElement->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 42), FVector(0.2, 0.2, 0.2) * ElementLevelValueSize));
		FireLight->SetLightColor(FLinearColor(0, 0.2, 0.8, 0));
		FireLight->SetAttenuationRadius(500.f);
		StabDamege =18.f;
		BurnAttacksDamege = 5.f;
		BurnAttacksCriPer = 20.f;
		ElementSpecialDamegeDamege = 50.f;
		TorchAttackCostData = 5;
		break;
	case 3:
		FireEffectReference = TEXT("ParticleSystem'/Game/FireStick/Poison/TorchPoisonball.TorchPoisonball'");
		FireEffectElementReference = TEXT("ParticleSystem'/Game/FireStick/Poison/TorchIdle_Poison.TorchIdle_Poison'");
		FireBurnAttacksEffectReference = TEXT("ParticleSystem'/Game/FireStick/Poison/WeaponsHitEffect.WeaponsHitEffect'");
		FireBurnAttacksCriEffectReference = TEXT("ParticleSystem'/Game/FireStick/Poison/P_Skill_Leap_Poison_Impact_Impact.P_Skill_Leap_Poison_Impact_Impact'");
		FireEffectElement->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 42), FVector(0.3, 0.3, 0.3) * ElementLevelValueSize));
		FireLight->SetLightColor(FLinearColor(0, 0.7, 0.2, 0));
		FireLight->SetAttenuationRadius(500.f);
		StabDamege = 3.f;
		BurnAttacksDamege = 1.5f;
		BurnAttacksCriPer = 10.f;
		ElementSpecialDamegeDamege = 20.f;
		TorchAttackCostData = 2;
		break;
	case 4:
		FireEffectReference = TEXT("ParticleSystem'/Game/FireStick/Electro/TorchElectroBall.TorchElectroBall'");
		FireEffectElementReference = TEXT("ParticleSystem'/Game/FireStick/Electro/P_ky_thunderStorm.P_ky_thunderStorm'");
		FireBurnAttacksEffectReference = TEXT("ParticleSystem'/Game/FireStick/Electro/TorchHitEffect_Electro.TorchHitEffect_Electro'");
		FireBurnAttacksCriEffectReference = TEXT("ParticleSystem'/Game/FireStick/Electro/P_ky_lightning3.P_ky_lightning3'");
		FireEffectElement->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 25), FVector(0.07, 0.07, 0.06) * ElementLevelValueSize));
		FireLight->SetLightColor(FLinearColor(0.1, 0.1, 0.1, 0));
		FireLight->SetAttenuationRadius(600.f);
		StabDamege = 20.f;
		BurnAttacksDamege = 5.f;
		BurnAttacksCriPer = 10.f;
		ElementSpecialDamegeDamege = 45.f;
		TorchAttackCostData = 7;
		break;
	}
	MyGameMode->TorchStatusSynergyDelegate.ExecuteIfBound(StabDamege, BurnAttacksDamege, ElementSpecialDamegeDamege,
		BurnAttacksCriPer);
	MyGameMode->TorchTotalDamgeSettingDelegate.ExecuteIfBound();
	
	UParticleSystem* NewFireEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, FireEffectReference));
	UParticleSystem* NewElementEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, FireEffectElementReference));
	UParticleSystem* NewElementBurnAttacksEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, FireBurnAttacksEffectReference));
	UParticleSystem* NewElementBurnAttacksCriEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, FireBurnAttacksCriEffectReference));
	if (NewFireEffect)
		FireEffect->SetTemplate(NewFireEffect);
	if (NewElementEffect)
		FireEffectElement->SetTemplate(NewElementEffect);
	if (NewElementBurnAttacksEffect)
		TorchHitEffect = NewElementBurnAttacksEffect;
	if (NewElementBurnAttacksCriEffect)
		TorchHitBurnAttacksCriEffect = NewElementBurnAttacksCriEffect;

	FireEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 42), 
		FVector(0.17, 0.17, 0.1)* ElementLevelValueSize));
	//FireEffectElement->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 42), FVector(0.05, 0.05, 0.05)));
}

void ARogueTorch::GetTorchTotalDamege(float StabDameges, float BurnAttacksDameges, float SpecialDameges, float ElementSpecialPer) {
	TorchStabDamegeValue = StabDameges;
	TorchBurnAttacksDamegeValue = BurnAttacksDameges;
	TorchSpecialDamegeValue = SpecialDameges;
	BurnAttacksCriPer = ElementSpecialPer;
}

void ARogueTorch::BurnAttacksSpecial(float Per) {
	if (FMath::RandRange(0.f, 100.f) <= Per)
		BurnAttacksSpecialOn = true;
}

void ARogueTorch::EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	TorchHitOn = true;
	if (OtherComp->GetCollisionProfileName() == TEXT("WallCollision")) {
		if (OverlappedComponent->GetName() == TEXT("FireStick")) {
			
			TorchCrashDelegate();
		}
		else if (OverlappedComponent->GetName() == TEXT("RightCapsule")) {
			
			TorchSideCrashDelegate(true);
		}
		else if (OverlappedComponent->GetName() == TEXT("LeftCapsule")) {
			
			TorchSideCrashDelegate(false);
		}
	}
	else if (OtherComp->GetCollisionProfileName() == TEXT("EnemyRogueCollision") && myRogue->NotTorchAttackState() == false) {
		if (OverlappedComponent->GetName() == TEXT("FireStick")) {
			//CanStabAttack = true;
			if (TorchAttackFinsh == false) {
				HitPlaceName = OtherComp->GetAttachSocketName();
				HitPlace = OtherComp->GetSocketLocation(HitPlaceName);
				HitPlace.Z = GetActorLocation().Z;
				OtherActors = OtherActor;
				
				TorchAttackEffectPlay(); //¿ä°ÍÀÌ ½ºÅÇ
				
				GetWorldTimerManager().SetTimer(HitTimeHandle, this, &ARogueTorch::TorchAttackEffectPlay, 0.01, true);
			}
		}
	}
}

void ARogueTorch::EnterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	TorchHitOn = false;
	if (OtherComp->GetCollisionProfileName() == TEXT("WallCollision")) {
		if (OverlappedComponent->GetName() == TEXT("FireStick")) {
			
			TorchLeaveDelegate();
		}
		else if (OverlappedComponent->GetName() == TEXT("RightCapsule")) {
			
			TorchSideLeaveDelegate(true);
		}
		else if (OverlappedComponent->GetName() == TEXT("LeftCapsule")) {
			
			TorchSideLeaveDelegate(false);
		}
	}
	else if (OtherComp->GetCollisionProfileName() == TEXT("EnemyRogueCollision") && myRogue->NotTorchAttackState() == false) {
		if (OverlappedComponent->GetName() == TEXT("FireStick")) {
			//TorchAttackEffectPlay();
			CanStabAttack = true;
			TorchAttackFinsh = true;
			TorchStateSpecialEffects[TorchElementNumber] = false;
			TorchStateDefaultEffects[TorchElementNumber] = false;
			
			TorchHitCounter = 0;
			GetWorldTimerManager().ClearTimer(HitTimeHandle);
		}
	}
}

void ARogueTorch::TorchAttackEffectPlay() {
	AEnemyRogue* EnemyRogue = Cast<AEnemyRogue>(OtherActors);
	if (TorchHitCounter < TorchHitLimit+TorchLimitPlus) {
		if (myRogue->NotAttackState() == false && TorchHitOn == true && myRogue->getCanHit() == true) {
			TorchStateDefaultEffects[TorchElementNumber] = true;
			TorchStateDefaultEffect();
			ConstData();
			EnemyRogue->TakeAttackVector(TackAttackVectorValue);
			if (CanStabAttack == false) {
				BurnAttacksSpecial(BurnAttacksCriPer);
				if (BurnAttacksSpecialOn == true) {
					GetOverlappingActors(EnemyArray, TSubclassOf<AEnemyRogue>());
					GetWorldTimerManager().ClearTimer(HitTimeHandle);
					TorchHitCounter = TorchHitLimit + TorchLimitPlus;
					TorchStateSpecialEffects[TorchElementNumber] = true;
					//EnemyRogue->EnemyRogueTakeTorchDamege(TorchStabDamegeValue, TorchBurnAttacksDamegeValue, TorchSpecialDamegeValue,
						//TorchEffectsStack, CanStabAttack, TorchStateDefaultEffects, TorchStateSpecialEffects, TorchElementNumber);
					for (int32 Index = 0; Index != EnemyArray.Num(); Index++) {
						AEnemyRogue* Enemys = Cast<AEnemyRogue>(EnemyArray[Index]);
						Enemys->EnemyRogueTakeTorchDamege(TorchStabDamegeValue, TorchBurnAttacksDamegeValue, TorchSpecialDamegeValue, 
							TorchEffectsStack, CanStabAttack, TorchStateDefaultEffects, TorchStateSpecialEffects, TorchElementNumber);
						Enemys->TakeAttackVector(TackAttackVectorValue);
					}
					TorchEffectsStack[TorchElementNumber] = 0;
					if (TorchElementNumber == 4)
						BurnAttacksCriPer = 5.f;
					//TorchStateSpecialEffect(TorchStabDamegeValue, TorchSpecialDamegeValue);

					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TorchHitBurnAttacksCriEffect, GetActorLocation() +
						FVector(0, -70, 0), FRotator(0, 0, 0), FVector(0.5, 0.5, 0.5) * ElementLevelValueSize * 1.5);
					BurnAttacksSpecialOn = false;
				}
				else { //³´½ºÆä¼ÈÀÌÆåÆ®
					EnemyRogue->EnemyRogueTakeTorchDamege(TorchStabDamegeValue, TorchBurnAttacksDamegeValue, TorchSpecialDamegeValue,
						TorchEffectsStack, CanStabAttack, TorchStateDefaultEffects, TorchStateSpecialEffects, TorchElementNumber);
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TorchHitEffect, HitPlace, FRotator(0, 0, 0), FVector(0.3, 0.3, 0.3) * ElementLevelValueSize * 0.8);
				}
			}
			else { //½ºÅÇ
				EnemyRogue->EnemyRogueTakeTorchDamege(TorchStabDamegeValue, TorchBurnAttacksDamegeValue, TorchSpecialDamegeValue,
					TorchEffectsStack, CanStabAttack, TorchStateDefaultEffects, TorchStateSpecialEffects, TorchElementNumber);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TorchHitEffect, HitPlace, FRotator(0, 0, 0), FVector(0.3, 0.3, 0.3) * ElementLevelValueSize * 0.8);
				CanStabAttack = false;
			}
		}
		TorchHitCounter++;
	}
	else {
		GetWorldTimerManager().ClearTimer(HitTimeHandle);
	}
}

void ARogueTorch::StateEffectSpecialExplosionCheck() {
	BurnAttacksSpecialOn = true;
}

void ARogueTorch::TorchStateDefaultEffect() {
	TorchEffectsStack[TorchElementNumber]++;
	switch (TorchElementNumber){
	case 4:
		BurnAttacksCriPer += 2.f;
		if (BurnAttacksCriPer >= 90.f)
			BurnAttacksCriPer = 90.f;
		break;
	}
}

/*void ARogueTorch::TorchStateSpecialEffect(float StabDameges, float SpecialDamege){
	switch (TorchElementNumber) {
	case 0:
		SetEffectDamege(SpecialDamege);
		break;
	case 1:
		SetEffectDamege(SpecialDamege);
		break;
	case 2:
		SetEffectDamege(SpecialDamege);
		break;
	case 3:
		SetEffectDamege(SpecialDamege);
		break;
	case 4:
		SetEffectDamege(SpecialDamege);
		break;
	}
}*/

void ARogueTorch::TorchCrashDelegate() {
	if (getTorchArrive() == true) {
		MyGameMode->TorchWallCrash.ExecuteIfBound();
	}
}

void ARogueTorch::TorchSideCrashDelegate(bool RightSideValue) {
	if (getTorchArrive() == true) {
		MyGameMode->TorchWallSideCrash.ExecuteIfBound(RightSideValue);
	}
}

void ARogueTorch::TorchLeaveDelegate() {
	if (getTorchArrive() == true) {
		MyGameMode->TorchWallLeave.ExecuteIfBound();
	}
}

void ARogueTorch::TorchSideLeaveDelegate(bool RIghtSideValue) {
	if (getTorchArrive() == true) {
		MyGameMode->TorchWallSideLeave.ExecuteIfBound(RIghtSideValue);
	}
}

void ARogueTorch::TorchRightLeftCapsuleInit() {
	RightCapsule = CreateDefaultSubobject<UCapsuleComponent>("RightCapsule");
	LeftCapsule = CreateDefaultSubobject<UCapsuleComponent>("LeftCapsule");
	RightCapsule->AttachToComponent(FireStick, FAttachmentTransformRules::KeepRelativeTransform);
	LeftCapsule->AttachToComponent(FireStick, FAttachmentTransformRules::KeepRelativeTransform);
	
	RightCapsule->SetCapsuleHalfHeight(2.f);
	RightCapsule->SetCapsuleRadius(2);
	RightCapsule->SetRelativeLocation(FVector(8, -3, -20));
	RightCapsule->SetCollisionProfileName("RogueTorchsCollision");
	
	LeftCapsule->SetCapsuleHalfHeight(2.f);
	LeftCapsule->SetCapsuleRadius(2);
	LeftCapsule->SetRelativeLocation(FVector(0, 10, -20));
	LeftCapsule->SetCollisionProfileName("RogueTorchsCollision");
}

void ARogueTorch::ConstData() {
	MyGameMode->RogueSetDataDelegate.ExecuteIfBound(TorchAttackCostData);
}

/*void ARogueTorch::TorchLevelUp() {
	TorchLevel += 1;
	TorchLevelValue = 1.f + TorchLevel * 0.05;
	MyGameMode->TorchStatusSynergyDelegate.ExecuteIfBound(StabDamege, BurnAttacksDamege, ElementSpecialDamegeDamege,
		BurnAttacksCriPer, TorchLevelValue, TorchLevel);
	TorchLevelValueSize = FVector(TorchLevelValue, TorchLevelValue, TorchLevelValue);
	ExplosionSphere->SetRelativeScale3D(FVector(20, 20, 20)*TorchLevelValueSize*ElementLevelValueSize);
	MyGameMode->TorchTotalDamgeSettingDelegate.ExecuteIfBound();
}*/

void ARogueTorch::ElementLevelUp(int32 ElementLevels, float ElementLevelValues) {
	ElementLevel = ElementLevels;
	ElementLevelValue = ElementLevelValues;
	ElementLevelValueSize = FVector(ElementLevelValue, ElementLevelValue, ElementLevelValue);
	FireEffectElement->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 42), FVector(0.3, 0.3, 0.3) * ElementLevelValueSize));
	FireEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 42),
		FVector(0.17, 0.17, 0.1) * ElementLevelValueSize));
}

void ARogueTorch::TakeAttackVector(FVector RogueAttackVector) {
	TackAttackVectorValue = RogueAttackVector;
}
