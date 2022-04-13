// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueWeapon.h"
#include "EnemyRogue.h"
#include "DataTableBase.h"

// Sets default values
ARogueWeapon::ARogueWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponInit();
	DataTableInit();
	WeaponAttackEffectInit();
	WeaponAttackDamegeInit();
	Weapon->OnComponentBeginOverlap.AddDynamic(this, &ARogueWeapon::EnterBeginOverlap);
	Weapon->OnComponentEndOverlap.AddDynamic(this, &ARogueWeapon::EnterEndOverlap);
	
}

// Called when the game starts or when spawned
void ARogueWeapon::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("RogueWeaponOn")));
	WorldRogueInit();
	WorldGameModeInit();
	WeaponDelegate();
	//WeaponNumberChange();
	//WeaponChangeElement(0, 1.f);
	//WeaponNumberChange(myRogueState->StartWeaponNumber);
	//MyGameMode->Call_GameStartWeaponNumberDelegate.ExecuteIfBound();
}

void ARogueWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MyRogue->NotAttackCheck() == true)
		WeaponAttackCheck = true;
}

void ARogueWeapon::AttackWallCrashDelegate() {
	MyGameMode->WeaponWallCrash.ExecuteIfBound();
}

void ARogueWeapon::WeaponDelegate() {
	MyGameMode->Return_WeaponChangeDelegate.BindUObject(this, &ARogueWeapon::WeaponNumberChange);
	MyGameMode->WeaponElementChangeDelegate_.BindUObject(this, &ARogueWeapon::WeaponChangeElement);
	MyGameMode->WeaponAttackQueDelegate.BindUObject(this, &ARogueWeapon::GetAttackQue);
	MyGameMode->WeaponTotalDamegeDelegate.BindUObject(this, &ARogueWeapon::SetWeaponTotalDamegeValue);
	MyGameMode->WeaponDoubleAttackAndAttackDirectionDelegate.BindUObject(this, &ARogueWeapon::GetWeaponDoubleCheckAndAttackDirection);
	//MyGameMode->RogueWeaponLevelDelegate.BindUObject(this, &ARogueWeapon::WeaponLevelUp);
	MyGameMode->RogueElementLevelToWeaponDelegate.BindUObject(this, &ARogueWeapon::ElementLevelUp);
	MyGameMode->WeaponAttackToEffectPercentIncreaseDelegate.BindUObject(this, &ARogueWeapon::SetHitPlusElement);
	MyGameMode->WeaponAttackToDmgIncreaseDelegate.BindUObject(this, &ARogueWeapon::SetAttackDmgValue);
	MyGameMode->WeaponHitKnockBackDelegate.BindUObject(this, &ARogueWeapon::TakeKnockBackCheck);
	MyGameMode->RogueAttackVectorToEnemyRogueDelegate.AddUObject(this, &ARogueWeapon::TakeAttackVector);
	MyGameMode->Call_RogueUseWeaponReferenceDelegate.BindUObject(this, &ARogueWeapon::Receive_CallRogueUseWeapon);
}

void ARogueWeapon::WeaponAttackDamegeInit() {
	for (int i = 0; i < 3; i++)
		WeaponAttackPhysicsDameges[i] = 0;
	WeaponAttackElementDamege = 0;
	ElementValue = 0;
	DefaultElementValue = 0;
}

void ARogueWeapon::DataTableInit() {
	auto DataAsset = ConstructorHelpers::FObjectFinder<UDataTable>(TEXT("DataTable'/Game/DataTable/RogueWeaponData.RogueWeaponData'"));
	if (DataAsset.Succeeded()) {
		WeaponDataTable = DataAsset.Object;
	}
}

void ARogueWeapon::WorldRogueInit() {
	UWorld* TheWorld = GetWorld();
	AActor* myPawn = UGameplayStatics::GetPlayerPawn(TheWorld, 0);
	MyRogue = Cast<ARogue>(myPawn);
	myRogueState = Cast<ARogueState>(MyRogue->GetPlayerState());
}

void ARogueWeapon::WorldGameModeInit() {
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
}

void ARogueWeapon::WeaponInit() {
	setHitCrash(false);
	WeaponReference = TEXT("StaticMesh'/Game/Weapons/Mace.Mace'");
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	auto WeaponAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(WeaponReference);
	
	if (WeaponAsset.Succeeded()) {
		Weapon->SetStaticMesh(WeaponAsset.Object);
	}

	ElementEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Normal/P_Buff_Char_SpeedUp_01.P_Buff_Char_SpeedUp_01'");
	WeaponElementEffect = CreateDefaultSubobject<UParticleSystemComponent>("WeaponElementEffect");
	auto WeaponElementEffectAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(ElementEffectReference);
	if (WeaponElementEffectAsset.Succeeded()) {
		WeaponElementEffect->SetTemplate(WeaponElementEffectAsset.Object);
	}

	Weapon->SetCollisionProfileName("RogueWeaponsCollision");

	WeaponElementEffect->AttachToComponent(Weapon, FAttachmentTransformRules::KeepRelativeTransform);
	/*WeaponLevel = 1;
	WeaponLevelValue = 1.0f + WeaponLevel * 0.05;
	ElementLevel = 1;
	ElementLevelValue = 1.f + ElementLevel * 0.05;*/

	AttackDmgPlusValue = 1.f;
}

void ARogueWeapon::WeaponAttackEffectInit() {
	auto HitParticle = ConstructorHelpers::FObjectFinder<UParticleSystem>
		(TEXT("ParticleSystem'/Game/Weapons/Effect/Normal/WeaponHitEffect_zero.WeaponHitEffect_zero'"));
	if (HitParticle.Succeeded())
		HitEffect = HitParticle.Object;
	HitEffectScale = 0.5f;
	EffectMinRange = -20.f;
	EffectMaxRange = 20.f;
	HitElementEffectScale = 0.3f;
	//EffectAvgRange = -300.f;
}

void ARogueWeapon::WeaponNumberChange(int32 WeaponNumber) {
	SelectWeaponNumber = WeaponNumber;
	if (WeaponDataTable != nullptr) {
		FRogueWeaponDataBase* WeaponDataTableRow = WeaponDataTable->FindRow<FRogueWeaponDataBase>(FName(*(FString::FormatAsNumber(SelectWeaponNumber))), FString(""));
		if (WeaponNumber == 0) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/Dagger.Dagger'");
			HitEffectScale = 0.7;
			WeaponDamege = 3.f;
			WeaponSpeed = 1.1f;
			ElementSynergy = 1.5f;
			WeaponAttackCostData = 5;
			ElementEffectSize = FVector(0.05, 0.05, 0.04);
			WeaponSynergy(0.5f, 0.3f, 1.5f);
		}
		else if (WeaponNumber == 1) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/Mace.Mace'");
			HitEffectScale = 1.f;
			WeaponDamege = 6.f;
			WeaponSpeed = 1.f;
			ElementSynergy = 1.3f;
			WeaponAttackCostData = 3;
			ElementEffectSize = FVector(0.06, 0.06, 0.05);

			WeaponSynergy(0.4f, 1.3f, 0.5f);
		}
		else if (WeaponNumber == 2) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/G_Axe.G_Axe'");
			WeaponDamege = 9.f;
			HitEffectScale = 0.9;
			WeaponSpeed = 0.8f;
			ElementSynergy = 0.6f;
			WeaponAttackCostData = 2;
			ElementEffectSize = FVector(0.07, 0.07, 0.06);

			WeaponSynergy(1.5f, 1.1f, 0.8f);
		}
		else if (WeaponNumber == 3) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/G_Hammer.G_Hammer'");
			WeaponDamege = 11.f;
			HitEffectScale = 1.3;
			WeaponSpeed = 0.75f;
			ElementSynergy = 1.2f;
			WeaponAttackCostData = 2;
			ElementEffectSize = FVector(0.08, 0.08, 0.06);

			WeaponSynergy(0.2f, 2.2f, 0.f);
		}
		else if (WeaponNumber == 4) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/G_Sword.G_Sword'");
			WeaponDamege = 8.f;
			HitEffectScale = 0.9f;
			WeaponSpeed = 0.85f;
			ElementSynergy = 1.f;
			WeaponAttackCostData = 2;
			ElementEffectSize = FVector(0.06, 0.06, 0.075);

			WeaponSynergy(1.7f, 0.8f, 1.0f);
		}
		else if (WeaponNumber == 5) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/NewShortSword.NewShortSword'");
			HitEffectScale = 0.7f;
			WeaponDamege = 5.f;
			WeaponSpeed = 1.1f;
			ElementSynergy = 1.2f;
			WeaponAttackCostData = 3;
			ElementEffectSize = FVector(0.05, 0.05, 0.04);

			WeaponSynergy(0.7f, 0.2f, 1.7f);
		}
		else if (WeaponNumber == 6) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/Axe.Axe'");
			HitEffectScale = 0.8f;
			WeaponDamege = 6.f;
			WeaponSpeed = 1.15f;
			ElementSynergy = 0.6f;
			WeaponAttackCostData = 4;
			ElementEffectSize = FVector(0.06, 0.06, 0.05);

			WeaponSynergy(1.3f, 0.8f, 0.8f);
		}
		else if (WeaponNumber == 7) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/SM_Spear.SM_Spear'");
			WeaponDamege = 10.f;
			HitEffectScale = 1.f;
			WeaponSpeed = 0.75f;
			ElementSynergy = 0.7f;
			WeaponAttackCostData = 1;
			ElementEffectSize = FVector(0.05, 0.05, 0.14);

			WeaponSynergy(1.7f, 1.2f, 0.8f);
		}
		else if (WeaponNumber == 8) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/SM_Sickle.SM_Sickle'");
			WeaponDamege = 11.f;
			HitEffectScale = 1.1f;
			WeaponSpeed = 0.75f;
			ElementSynergy = 1.2f;
			WeaponAttackCostData = 1;
			ElementEffectSize = FVector(0.05, 0.05, 0.13);

			WeaponSynergy(1.4f, 1.2f, 0.8f);
		}
		else if (WeaponNumber == 10) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/SM_Shield.SM_Shield'");
			WeaponDamege = 7.f;
			HitEffectScale = 0.8f;
			WeaponSpeed = 0.85f;
			ElementSynergy = 1.f;
			WeaponAttackCostData = 4;
			ElementEffectSize = FVector(0.12, 0.12, 0.15);

			WeaponSynergy(1.3f, 0.7f, 1.0f);
		}
		else if (WeaponNumber == 9) {
			WeaponReference = TEXT("StaticMesh'/Game/Weapons/SM_Throwing.SM_Throwing'");
			WeaponDamege = 2.f;
			HitEffectScale = 0.6f;
			WeaponSpeed = 1.3f;
			ElementSynergy = 2.3f;
			WeaponAttackCostData = 5;
			ElementEffectSize = FVector(0.04, 0.04, 0.03);

			WeaponSynergy(0.2f, 0.f, 1.5f);
		}
		HitEffectScale = WeaponDataTableRow->HitEffectScale;
		WeaponDamege = WeaponDataTableRow->WeaponDamage;
		WeaponSpeed = WeaponDataTableRow->WeaponSpeed;
		ElementSynergy = WeaponDataTableRow->ElementSynergy;
		WeaponAttackCostData = WeaponDataTableRow->AttackCost;
		ElementEffectSize = WeaponDataTableRow->ElementEffectSize;
		WeaponSynergy(WeaponDataTableRow->FormSynergyX, WeaponDataTableRow->FormSynergyY, WeaponDataTableRow->FormSynergyZ);

		MyGameMode->WeaponElementSynergyDelegate.ExecuteIfBound(ElementSynergy, DefaultElementDamege, DefaultElementValue);
		MyGameMode->WeaponSynergyDelegate.ExecuteIfBound(SelectWeaponNumber, SlashSynergy, BreakSynergy, StabSynergy, WeaponDamege, WeaponSpeed);
		MyGameMode->WeaponTotalDamegeSettingDelegate.ExecuteIfBound();

		UStaticMesh* NewWeapon = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, WeaponReference));
		if (NewWeapon)
			Weapon->SetStaticMesh(NewWeapon);
		WeaponTransformSetting(WeaponNumber);


		WeaponElementEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), ElementEffectSize * ElementLevelValue));
		if (SelectWeaponNumber == 4)
			WeaponElementEffect->SetRelativeRotation(FRotator(180, 0, 0));
		else
			WeaponElementEffect->SetRelativeRotation(FRotator(0, 0, 0));
	}
}

void ARogueWeapon::WeaponTransformSetting(int32 WeaponNumber) {
	Weapon->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(1, 1, 1)));
	if (WeaponNumber == 2 || WeaponNumber == 6)
		Weapon->SetRelativeRotation(FRotator(0, 180, 0));
	if (WeaponNumber == 4)
		Weapon->SetRelativeRotation(FRotator(180, 0, 0));
	/*if (WeaponNumber == 9) {
		Weapon->SetRelativeRotation(FRotator(0, -20, 180));
		Weapon->SetRelativeLocation(FVector(3, -5, 0));
		Weapon->SetRelativeScale3D(FVector(0.5, 0.6, 0.5));
	}
	else 
		Weapon->SetRelativeRotation(FRotator(0, 0, 0));
	*/

	if (WeaponNumber == 2 || WeaponNumber == 3)
		Weapon->SetRelativeScale3D(FVector(0.8, 0.8, 1));
	if (WeaponNumber == 4 || WeaponNumber == 7 || WeaponNumber == 8)
		Weapon->SetRelativeScale3D(FVector(1.1, 1.1, 1));
}



void ARogueWeapon::WeaponChangeElement(int32 ElementIndex, float SelectElementLevelValue) {
	SelectWeaponElementNumber = ElementIndex;
	ElementLevelValue = SelectElementLevelValue;
	switch (ElementIndex) {
	case 0:
		ElementEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Normal/P_Buff_Char_SpeedUp_01.P_Buff_Char_SpeedUp_01'");
		ElementHitEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Normal/P_ky_hit2.P_ky_hit2'");
		WeaponElementEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), ElementEffectSize * ElementLevelValue));
		DefaultElementDamege = 10.f;
		HitElementEffectScale = 0.3;
		DefaultElementValue = 20.f;
		//DefaultElementPer = 20.f;
		break;
	case 1:
		ElementEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Fire/P_ky_fireStorm.P_ky_fireStorm'");
		ElementHitEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Fire/WeaponHitEffect_Fire.WeaponHitEffect_Fire'");
		WeaponElementEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), ElementEffectSize * ElementLevelValue));
		DefaultElementDamege = 12.f;
		HitElementEffectScale = 0.3;
		DefaultElementValue = 15.f;
		//DefaultElementPer = 20.f;
		break;
	case 2:
		ElementEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Ice/P_ky_healAura.P_ky_healAura'");
		ElementHitEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Ice/P_ShoulderIce01.P_ShoulderIce01'");
		WeaponElementEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), ElementEffectSize * ElementLevelValue));
		DefaultElementDamege = 8.f;
		HitElementEffectScale = 0.2;
		DefaultElementValue = 10.f;
		//DefaultElementPer = 50.f;
		break;
	case 3:
		ElementEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Poison/P_ky_storm.P_ky_storm'");
		ElementHitEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Poison/P_ky_hit1.P_ky_hit1'");
		WeaponElementEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), ElementEffectSize * ElementLevelValue));
		DefaultElementDamege = 1.f;
		HitElementEffectScale = 0.25;
		DefaultElementValue = 30.f;
		//DefaultElementPer = 90.f;
		break;
	case 4:
		ElementEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Electro/P_DOT_Lightning_01.P_DOT_Lightning_01'");
		ElementHitEffectReference = TEXT("ParticleSystem'/Game/Weapons/Effect/Electro/P_ky_ThunderBallHit.P_ky_ThunderBallHit'");
		WeaponElementEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), ElementEffectSize * ElementLevelValue));
		DefaultElementDamege = 6.f;
		HitElementEffectScale = 0.1;
		DefaultElementValue = 50.f;
		//DefaultElementPer = 0.f;
		break;
	}
	MyGameMode->WeaponElementSynergyDelegate.ExecuteIfBound(ElementSynergy, DefaultElementDamege, DefaultElementValue);
	MyGameMode->WeaponSynergyDelegate.ExecuteIfBound(SelectWeaponNumber, SlashSynergy, BreakSynergy, StabSynergy, WeaponDamege, WeaponSpeed);
	MyGameMode->WeaponTotalDamegeSettingDelegate.ExecuteIfBound();

	if (SelectWeaponNumber == 4)
		WeaponElementEffect->SetRelativeRotation(FRotator(180, 0, 0));
	else
		WeaponElementEffect->SetRelativeRotation(FRotator(0, 0, 0));
	
	UParticleSystem* NewElementEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, ElementEffectReference));
	UParticleSystem* NewElementHitEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, ElementHitEffectReference));
	
	if (NewElementEffect) {
		WeaponElementEffect->SetTemplate(NewElementEffect);
	}
	if (NewElementHitEffect)
		WeaponElementHitEffect = NewElementHitEffect;
}

void ARogueWeapon::WeaponSynergy(float Slash, float Break, float Stab) {
	SlashSynergy = Slash;
	BreakSynergy = Break;
	StabSynergy = Stab;
}

void ARogueWeapon::GetAttackQue(int32 NowQue) {
	AttackQue = NowQue;
}

void ARogueWeapon::SetWeaponTotalDamegeValue(float* WeaponDameges,  float ElementDamege, float ElementValues) {
	WeaponAttackPhysicsDameges[0] = WeaponDameges[0];
	WeaponAttackPhysicsDameges[1] = WeaponDameges[1];
	WeaponAttackPhysicsDameges[2] = WeaponDameges[2];

	WeaponAttackElementDamege = ElementDamege;

	SetElementValue(ElementValues*(1.0+0.1*ElementPlusValue));
}

void ARogueWeapon::GetWeaponDoubleCheckAndAttackDirection(bool First, bool Snd, bool Trd, int32 ZeroZeroDirect,
	int32 ZeroOneDirect, int32 OneZeroDirect, int32 OneOneDirect, int32 TwoZeroDirect, int32 TwoOneDirect) {
	DoubleAttackChecks[0] = First;
	DoubleAttackChecks[1] = Snd;
	DoubleAttackChecks[2] = Trd;
	AttackDirection[0][0] = ZeroZeroDirect;
	AttackDirection[0][1] = ZeroOneDirect;
	AttackDirection[1][0] = OneZeroDirect;
	AttackDirection[1][1] = OneOneDirect;
	AttackDirection[2][0] = TwoZeroDirect;
	AttackDirection[2][1] = TwoOneDirect;
}

void ARogueWeapon::SpawnHitEffect() {
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitPlace +
		FVector(FMath::FRandRange(EffectMinRange, EffectMaxRange),
			FMath::FRandRange(EffectMinRange, EffectMaxRange),
			FMath::FRandRange(EffectMinRange, EffectMaxRange)),
		FRotator(0, 0, 0), FVector(HitEffectScale, HitEffectScale, HitEffectScale));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponElementHitEffect, HitPlace +
		FVector(FMath::FRandRange(EffectMinRange, EffectMaxRange),
			FMath::FRandRange(EffectMinRange, EffectMaxRange),
			FMath::FRandRange(EffectMinRange, EffectMaxRange)),
		FRotator(FMath::FRandRange(EffectMinRange, EffectMaxRange),
			FMath::FRandRange(EffectMinRange, EffectMaxRange),
			FMath::FRandRange(EffectMinRange, EffectMaxRange)),
		FVector(HitElementEffectScale, HitElementEffectScale, HitElementEffectScale));
}

void ARogueWeapon::WeaponAttackPlay(AActor* OtherActor, UPrimitiveComponent* OtherComp) {
	AEnemyRogue* EnemyRogue = Cast<AEnemyRogue>(OtherActor);
	if (MyRogue->NotAttackState() == false && MyRogue->getCanHit() == true ){ // 무기 사용자 상태 체크
		WeaponAttackCheck = false; 
		CostData(); // 공격 코스트 함수
		SetDamegeTaken(0.f); //데미지 초기화
		SpawnHitEffect(); // 공격 성공시 이펙트
		EnemyRogue->EnemyRogueTakeWeaponPhysicsDamege(WeaponAttackPhysicsDameges[AttackQue]);
		EnemyRogue->EnemyRogueTakeWeaponElementDamege(WeaponAttackElementDamege);
		EnemyRogue->EnemyRogueTakeElementStatus(SelectWeaponElementNumber, ElementValue);
		if (WeaponKnockBack == true) {
			EnemyRogue->TakeAttackVector(TackAttackVectorValue); //공격방향에 따른 백터값
			EnemyRogue->TakeWeaponKnockBackCheck(WeaponKnockBack); //넉백 체크 및 넉백발동
		}
		if (StateEffect[4] == true) { // 전격속성일 경우 스택형 이펙트 발동
			UParticleSystem* ElectricAttackBoomEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL,
				TEXT("ParticleSystem'/Game/Weapons/Effect/Electro/P_ky_lightning2.P_ky_lightning2'")));
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElectricAttackBoomEffect, HitPlace - FVector(0, 0, 20),
				FRotator(0, 0, 0), FVector(0.6, 0.6, 0.6));
		}
		MyRogue->MyRogueState->WeaponLevelEx++; // 무기 레벨 경험치 증가
		if (MyRogue->MyRogueState->WeaponLevelEx > MyRogue->MyRogueState->WeaponLevelExMax) {
			MyRogue->MyRogueState->SetWeaponLevelUp(); // 무기 경험치 최대치 도달 시 레벨 업
		}
		if (MyRogue->MyRogueState->ElementLevelEx > MyRogue->MyRogueState->ElementLevelExMax) {
			MyRogue->MyRogueState->SetElementLevelUp(); // 속성 경험치 최대치 도달 시 레벨 업
		}
		//for (int i = 0; i < 5; i++)
			//StateEffect[i] = false; // 속성 특수능력 발동 초기화
		
		
		
		//AttackElementStateEffect(GetElementPer(), WeaponAttackDefaultPhysicsElementDameges[AttackQue]* AttackDmgPlusValue);
		//무기 속성 발동 및 상태 함수

		
		
		/*EnemyRogue->EnemyRogueTakeWeaponDamege(WeaponAttackDefaultPhysicsElementDameges[AttackQue]* AttackDmgPlusValue,
			GetDamegeTaken(), GetDotDamege(SelectWeaponElementNumber), SelectWeaponElementNumber,
			ElementStack[SelectWeaponElementNumber], StateEffect,
			DoubleAttackChecks[AttackQue], AttackDirection[AttackQue][0], AttackDirection[AttackQue][1], WeaponSpeed);*/
			// 데미지 발동 함수 - 공격, 속성, 특수능력 발동, 도트데미지, 방향, 스택정보 전달
		
		

		/*if (ElementPlusValue != 0) { // 공격성공 및 피격이 없을 경우 발동되는 스택형 능력 구현 함수, 아직 완벽히 구현되지 않았음
			SetPlusElementPer(ElementPlusValue);
			MyGameMode->WeaponElementSynergyDelegate.ExecuteIfBound(ElementSynergy, DefaultElementDamege, TotalElementPer);
		}
		
		if (AttackDmgPlusValue != 1.f) {
			SetAttackDmgPlusValue(AttackDmgValue);
		}*/
		
	}
}

void ARogueWeapon::EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
		if (OtherComp->GetCollisionProfileName() == TEXT("WallCollision")) {
			
			AttackWallCrashDelegate();
			//WeaponAttackPlay();
		}
		else if (OtherComp->GetCollisionProfileName() == TEXT("EnemyRogueCollision") && MyRogue->NotAttackCheck() == false
			&& WeaponAttackCheck == true && MyRogue->NotTorchAttackState() == true) {
			HitPlaceName = OtherComp->GetAttachSocketName();
			HitPlace = OtherComp->GetSocketLocation(HitPlaceName);
			HitPlace.Z = GetActorLocation().Z;
			WeaponAttackPlay(OtherActor, OtherComp);

			
		}

		if (OtherComp->GetOwner() == OtherActor) {

		}
	
}

void ARogueWeapon::EnterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherComp->GetCollisionProfileName() == TEXT("WallCollision")) {
		
		//AttackCrashDelegate();
		//WeaponAttackPlay();
	}
	else if (OtherComp->GetCollisionProfileName() == TEXT("EnemyRogueCollision") && MyRogue->NotWeaponAttackState() == false) {
		//WeaponAttackPlay();
		WeaponAttackCheck = true;
	}
	
}

void ARogueWeapon::AttackElementStateEffect(float Per, float InputDamege) {
	switch (SelectWeaponElementNumber)
	{
	case 0:
		if (Per >= FMath::RandRange(0.f, 100.f)) {
			SetStun(InputDamege);
			if (FMath::RandRange(0, 100) > 20)
				MyRogue->MyRogueState->ElementLevelEx++;
		}
		else
			StateEffect[0] = false;
		break;
	case 1:
		if (Per >= FMath::RandRange(0.f, 100.f)) {
			SetBurn(InputDamege);
			if (FMath::RandRange(0, 100) > 20)
				MyRogue->MyRogueState->ElementLevelEx++;
		}
		else
			StateEffect[1] = false;
		break;
	case 2:
		if (Per >= FMath::RandRange(0.f, 100.f)) {
			SetCold(InputDamege);
			if(FMath::RandRange(0, 100) > 50)
				MyRogue->MyRogueState->ElementLevelEx++;
		}
		else
			StateEffect[2] = false;
		break;
	case 3:
		if (Per >= FMath::RandRange(0.f, 100.f)) {
			SetPoison(InputDamege);
			if (FMath::RandRange(0, 100) > 80)
				MyRogue->MyRogueState->ElementLevelEx++;
		}
		else
			StateEffect[3] = false;
		break;
	case 4:
		SetElectricStack(Per, InputDamege);
		break;
	}

}

void ARogueWeapon::SetStun(float InputDamege) {
	ElementStack[0]++;
	StateEffect[0] = true;
	//DamegeTaken = InputDamege * 1.5;
	SetDamegeTaken(InputDamege * 1.3f);
	
}

void ARogueWeapon::SetBurn(float InputDamege) {
	ElementStack[1]++;
	StateEffect[1] = true;
	SetDamegeTaken(InputDamege * 1.1f);
	SetDotDamege(1, DamegeTaken, 0.1);
	
}

void ARogueWeapon::SetCold(float InputDamege) {
	ElementStack[2]++;
	StateEffect[2] = true;
	SetDamegeTaken(InputDamege * 1.2f);
	
}

void ARogueWeapon::SetPoison(float InputDamege) {
	ElementStack[3]++;
	StateEffect[3] = true;
	SetDotDamege(3, 2.f, 0.5);
	SetDamegeTaken(InputDamege);
	
}

void ARogueWeapon::SetElectricStack(float Per, float InputDamege) {
	ElementStack[4]++;
	Per = ElementStack[4] * 5.f;
	for(int i = 0; i < ElementStack[4]; i++)
		InputDamege *= 1.05;
	if (Per >= FMath::RandRange(0.f, 100.f)) {
		StateEffect[4] = true;
		SetDamegeTaken(InputDamege*2.5f);
		ElementStack[4] = 0;
		Per = 0.f;
		MyRogue->MyRogueState->ElementLevelEx++;
	}
	else{
		StateEffect[4] = false;
		SetDamegeTaken(InputDamege);
		
	}
	
}

void ARogueWeapon::SetDotDamege(int32 DotDamegeElement, float OriginDamege, float DotPer) {
	DotDamege[DotDamegeElement] = OriginDamege * DotPer;
}

void ARogueWeapon::CostData() {
	MyGameMode->RogueSetDataDelegate.ExecuteIfBound(-WeaponAttackCostData);
}

/*void ARogueWeapon::WeaponLevelUp() {
	WeaponLevel += 1;
	WeaponLevelValue = 1.0f + WeaponLevel * 0.05;
	MyGameMode->WeaponSynergyDelegate.ExecuteIfBound(SelectWeaponNumber, SlashSynergy, BreakSynergy, StabSynergy, WeaponDamege, WeaponLevel, WeaponSpeed, WeaponLevelValue);
	MyGameMode->WeaponTotalDamegeSettingDelegate.ExecuteIfBound();
}*/

void ARogueWeapon::ElementLevelUp(int32 ElementLevels, float ElementLevelValues) {
	ElementLevel = ElementLevels;
	ElementLevelValue = ElementLevelValues;
	//MyGameMode->WeaponSynergyDelegate.ExecuteIfBound(SelectWeaponNumber, SlashSynergy, BreakSynergy, StabSynergy, WeaponDamege, WeaponSpeed);
	//MyGameMode->WeaponTotalDamegeSettingDelegate.ExecuteIfBound();
	WeaponElementEffect->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), ElementEffectSize * ElementLevelValue));
	HitElementEffectScale *=  ElementLevelValue;
}
void ARogueWeapon::TakeAttackVector(FVector RogueAttackVector) {
	TackAttackVectorValue = RogueAttackVector;
}

void ARogueWeapon::TakeKnockBackCheck(int32 Check) {
	if(Check == 1)
		WeaponKnockBack = true;
	else if(Check == 0)
		WeaponKnockBack = false;
}

void ARogueWeapon::Receive_CallRogueUseWeapon() {
	MyGameMode->Return_RogueUseWeaponReferenceDelegate.ExecuteIfBound(SelectWeaponNumber);
}
