// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRogue.h"
#include "EnemyAIController.h"

// Sets default values
AEnemyRogue::AEnemyRogue()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyRogueBodyInit();
	EnemyRogueStateInit();
	//EnemyRogueAnimationInit();
	TakeStackInit();
	AllDotTickInit();
	AllStateInit();
	StateEffectInit();
	EnemyWeaponInit();
}

// Called when the game starts or when spawned
void AEnemyRogue::BeginPlay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("EnemyRogueOn")));
	Super::BeginPlay();
	EnemyRogueBodySetting();
	//EnemyRogueStateSetting();
	PostInitializeComponents();
	GetWorldGameMode();
	EnemyRogueTakeDamegeDelegateInit();
	WorldRogueInit();
	EnemyRogueWeaponInfo();
	SaveSlotName = TEXT("SaveSlot");
	URogueSaveGame* LoadGame = Cast<URogueSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (LoadGame == nullptr) {
		LoadGame = GetMutableDefault<URogueSaveGame>();
	}
	else {
		LoadGameData(LoadGame);
	}
}


void AEnemyRogue::LoadGameData(URogueSaveGame* LoadData) {
	URogueSaveGame* LoadGame = Cast<URogueSaveGame>(LoadData);
	Hp = (LoadGame->DungeonClearAllCount * 50) + Hp;
	//for(int i = 0; i < 3; i ++)
		//StoryProgress[i] = LoadGame->StoryProgress[i];
	//myRogue->SetActorLocation(LoadGame->LastLocation);
}

void AEnemyRogue::PostInitializeComponents() {
	Super::PostInitializeComponents();
	SetEnemyRogueAnimInstance = GetMesh()->GetAnimInstance();
	EnemyAnimInst = Cast<URogueAnimInstance>(SetEnemyRogueAnimInstance);
}

// Called every frame
void AEnemyRogue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (CheckHit() == false && DoWalk(EnemyForm) == false && DoAttack() == false && EnemyDead == false)
	//	DoIdle(EnemyForm);
	//SetActorRotation(ViewArm->GetRelativeTransform().GetRotation());
	//DoWalk(0);
	/*auto StartPos = GetActorLocation();

	FVector PlayerPos =
		GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector Direction = PlayerPos - StartPos;
	Direction.Normalize();

	SetActorLocation(StartPos + Direction);*/
}

void AEnemyRogue::WorldRogueInit() {
	UWorld* TheWorld = GetWorld();
	AActor* myPawn = UGameplayStatics::GetPlayerPawn(TheWorld, 0);
	myRogue = Cast<ARogue>(myPawn);
}

void AEnemyRogue::SetEnemyDownFinish(bool StartCheck) {
	EnemyDownFinish = StartCheck;
	if(EnemyDownFinish == true)
		Destroy();
}

void AEnemyRogue::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap(OtherActor);
	//ARogueWeapon* RogueWeapon = Cast<ARogueWeapon>(OtherActor);
	//ARogueTorch* RogueTorch = Cast<ARogueTorch>(OtherActor);
	/*OtherEnemy = Cast<AEnemyRogue>(OtherActor);
	if (OtherEnemy) {
		if (OtherEnemy->ExplosionBody == false)
			SetHp(OtherEnemy->ExplosionDamage);
	}*/
}

// Called to bind functionality to input
void AEnemyRogue::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyRogue::GetWorldGameMode() {
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
}

void AEnemyRogue::EnemyRogueTakeDamegeDelegateInit() {
	//MyGameMode->EnemyRogueTakeWeaponDamegeDelegate.BindUObject(this, &AEnemyRogue::EnemyRogueTakeWeaponDamege);
	//MyGameMode->EnemyRogueTakeTorchDamegeDelegate.BindUObject(this, &AEnemyRogue::EnemyRogueTakeTorchDamege);
	//MyGameMode->RogueAttackVectorToEnemyRogueDelegate.BindUObject(this, &AEnemyRogue::TakeAttackVector);
	//MyGameMode->WeaponHitKnockBackDelegate.BindUObject(this, &AEnemyRogue::TakeWeaponKnockBackCheck);
}

void AEnemyRogue::EnemyRogueBodyInit() {
	auto EnemyRogueBodyAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>
		(TEXT("SkeletalMesh'/Game/EnemyRogue/EnemyROgue.EnemyROgue'"));
	GetMesh()->SetSkeletalMesh(EnemyRogueBodyAsset.Object);
	
	GetMesh()->AddRelativeLocation(FVector(0, 0, -90));
	GetMesh()->AddRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetCollisionProfileName("NoCollision");
	RootComponent->AddRelativeRotation(FRotator(0, 90, 0));
	
	EnemyRogueCollisionInit();

	ViewArm = CreateDefaultSubobject<USpringArmComponent>("ViewArm");
	ViewArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, (TEXT("Head")));

	auto TakeHitSoundCueAsset1 = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/EnemyTakeHit/Attack01_Cue.Attack01_Cue'"));

	if (TakeHitSoundCueAsset1.Succeeded()) {
		TakeHitSoundCue = TakeHitSoundCueAsset1.Object;
	}
}

void AEnemyRogue::EnemyRogueBodySetting() {
	float RandScale1 = FMath::FRandRange(1, 1.15);
	float RandScale2 = FMath::FRandRange(1, 1.15);
	float RandScale3 = FMath::FRandRange(1, 1.15);
	GetMesh()->SetRelativeScale3D(FVector(RandScale1, RandScale2, RandScale3));
	GetCapsuleComponent()->SetRelativeScale3D(FVector(RandScale1, RandScale2, RandScale3));
}

void AEnemyRogue::EnemyRogueCollisionInit() {
	GetCapsuleComponent()->SetCollisionProfileName("EnemyRogueCollision");
	GetMesh()->SetCollisionProfileName("RogueAttackStateCollision");
}

void AEnemyRogue::EnemyWeaponInit() {
	EnemyWeapon = CreateDefaultSubobject<UChildActorComponent>("EnemyRogueWeapon");
	auto EnemyWeaponAsset = ConstructorHelpers::FClassFinder<AActor>
		(TEXT("Class'/Script/Castle_in_Dungeon.EnemyRogueWeapon'"));
	if (EnemyWeaponAsset.Succeeded())
		EnemyWeapon->SetChildActorClass(EnemyWeaponAsset.Class);

	EnemyWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandFarm"));
	EnemyWeapon->SetRelativeRotation(FRotator(270, 0, 0));
	/*RogueWeapons = CreateDefaultSubobject<UChildActorComponent>("RogueWeapon");
	auto WeaponAsset = ConstructorHelpers::FClassFinder<AActor>
		(TEXT("Class'/Script/Castle_in_Dungeon.RogueWeapon'"));
	if (WeaponAsset.Succeeded()) {
		RogueWeapons->SetChildActorClass(WeaponAsset.Class);
	}
	RogueWeapons->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandFarm"));
	RogueWeapons->SetRelativeRotation(FRotator(270, 0, 0));
	//RogueWeapons->SetRelativeLocation(FVector(-2, 0, 3));*/
}

void AEnemyRogue::EnemyRogueWeaponInfo() {
	EnemyRogueWeapon =
		Cast<AEnemyRogueWeapon>(EnemyWeapon->GetChildActor());
	EnemyRogueWeapon->EnemyRogueWeaponChange(StartWeaponNumber);
	if (EnemyRogueWeapon) {
		EnemyRogueWeaponRange = EnemyRogueWeapon->EnemyWeaponRange;
		EnemyRogueWeaponDamage = EnemyRogueWeapon->EnemyWeaponDamage;
		EnemyRogueWeaponSpeed = EnemyRogueWeapon->EnemyWeaponSpeed;
	}
}

void AEnemyRogue::EnemyRogueStateInit() {
	StartWeaponNumber = 0.f;
	SlowValue = 1.f;
	DeathData = 100;
	Karma = DeathData * 1.5;
	ElectriFicationValue = 1.f;
	Hp = 300.f;
	EnemyDead = false;
	EnemyDownFinish = false;
	AIControllerClass = AEnemyAIController::StaticClass();
	GetCharacterMovement()->MaxWalkSpeed = 95.f;
	HitCount = 0;
	HitCountLimite = 5;
	HitSuperArmorCount = 0;
	TakeDamageLimit = 1;
	TakeDamageCount = 0;
	ElementStatusLimit[0] = 100.f;
	ElementStatusLimit[1] = 100.f;
	ElementStatusLimit[2] = 100.f;
	ElementStatusLimit[3] = 100.f;
	ElementStatusLimit[4] = 100.f;
	/*auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
		(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation.BP_EnemyRogueAnimation_C'"));
	if (BlandAnim.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
	}
	GetCharacterMovement()->MaxWalkSpeed = 145.f;
	MoveSpeedValue = GetCharacterMovement()->MaxWalkSpeed;*/

	if (EnemyForm <= 6) {
		/*UAnimInstance* EnemyAnim = Cast<UAnimInstance>(StaticLoadClass(UAnimInstance::StaticClass(), NULL,
			TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation.BP_EnemyRogueAnimation_C'")));*/
		auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
			(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation.BP_EnemyRogueAnimation_C'"));
		if (BlandAnim.Succeeded()) {
			GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
			GetCharacterMovement()->MaxWalkSpeed = 165.f;
			HitCountLimite = 3;
			HitSuperArmorCount = 0;
			HitSuperArmorCountLimit = 2;
		}
	}
	else if (EnemyForm <= 8) {
		/*UAnimInstance* EnemyAnim = Cast<UAnimInstance>(StaticLoadClass(UAnimInstance::StaticClass(), NULL,
			TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_2.BP_EnemyRogueAnimation_2_C'")));
		GetMesh()->SetAnimInstanceClass(EnemyAnim->StaticClass());
		GetCharacterMovement()->MaxWalkSpeed = 165.f;*/
		auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
			(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_2.BP_EnemyRogueAnimation_2_C'"));
		if (BlandAnim.Succeeded()) {
			GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
			GetCharacterMovement()->MaxWalkSpeed = 185.f;
			HitCountLimite = 2;
			HitSuperArmorCount = 0;
			HitSuperArmorCountLimit = 2;
		}
	}
	else if (EnemyForm <= 9) {
		/*UAnimInstance* EnemyAnim = Cast<UAnimInstance>(StaticLoadClass(UAnimInstance::StaticClass(), NULL,
			TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_3.BP_EnemyRogueAnimation_3_C'")));
		GetMesh()->SetAnimInstanceClass(EnemyAnim->StaticClass());
		GetCharacterMovement()->MaxWalkSpeed = 85.f;*/
		auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
			(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_3.BP_EnemyRogueAnimation_3_C'"));
		if (BlandAnim.Succeeded()) {
			GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
			GetCharacterMovement()->MaxWalkSpeed = 95.f;
			HitCountLimite =2;
			HitSuperArmorCount = 0;
			HitSuperArmorCountLimit = 3;
		}
	}
	MoveSpeedValue = GetCharacterMovement()->MaxWalkSpeed;
	auto EnemyBehaviorTreeAsset = ConstructorHelpers::FObjectFinder<UBehaviorTree>
		(TEXT("BehaviorTree'/Game/EnemyRogue/BT/EnemyBehaviorTree.EnemyBehaviorTree'"));
	if (EnemyBehaviorTreeAsset.Succeeded())
		EnemyBehaviorTree = EnemyBehaviorTreeAsset.Object;

	/*EnemyForm = FMath::FRandRange(0, 9);
	if (EnemyForm <= 6) {
		auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
			(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation.BP_EnemyRogueAnimation_C'"));
		if (BlandAnim.Succeeded()) {
			GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
		}
		GetCharacterMovement()->MaxWalkSpeed = 145.f;
	}
	else if (EnemyForm <= 8) {
	auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
		(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_2.BP_EnemyRogueAnimation_2_C'"));
		if (BlandAnim.Succeeded()) {
			GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
		}
		GetCharacterMovement()->MaxWalkSpeed = 165.f;
	}
	else if (EnemyForm <= 9) {
	auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
		(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_3.BP_EnemyRogueAnimation_3_C'"));
		if (BlandAnim.Succeeded()) {
				GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
		}
		GetCharacterMovement()->MaxWalkSpeed = 85.f;
	}*/
}

void AEnemyRogue::EnemyRogueStateSetting() {
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("EnemyRogueStateOn")));
	//EnemyForm = FMath::FRandRange(0, 9);
	if (EnemyForm <= 6) {
		UAnimInstance* EnemyAnim = Cast<UAnimInstance>(StaticLoadClass(UAnimInstance::StaticClass(), NULL,
			TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation.BP_EnemyRogueAnimation_C'")));
		//auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
			//(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation.BP_EnemyRogueAnimation_C'"));
		//if (BlandAnim.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(EnemyAnim->StaticClass());
		GetCharacterMovement()->MaxWalkSpeed = 145.f;
	}
	else if (EnemyForm <= 8) {
		UAnimInstance* EnemyAnim = Cast<UAnimInstance>(StaticLoadClass(UAnimInstance::StaticClass(), NULL,
			TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_2.BP_EnemyRogueAnimation_2_C'")));
		GetMesh()->SetAnimInstanceClass(EnemyAnim->StaticClass());
		GetCharacterMovement()->MaxWalkSpeed = 165.f;
		/*auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
			(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_2.BP_EnemyRogueAnimation_2_C'"));
		if (BlandAnim.Succeeded()) {
			GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
		}*/
		//GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
		//GetCharacterMovement()->MaxWalkSpeed = 165.f;
	}
	else if (EnemyForm <= 9) {
		UAnimInstance* EnemyAnim = Cast<UAnimInstance>(StaticLoadClass(UAnimInstance::StaticClass(), NULL,
			TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_3.BP_EnemyRogueAnimation_3_C'")));
		GetMesh()->SetAnimInstanceClass(EnemyAnim->StaticClass());
		GetCharacterMovement()->MaxWalkSpeed = 85.f;
		/*auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
			(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_3.BP_EnemyRogueAnimation_3_C'"));
		if (BlandAnim.Succeeded()) {
			GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
		}
		GetCharacterMovement()->MaxWalkSpeed = 85.f;
	}
	MoveSpeedValue = GetCharacterMovement()->MaxWalkSpeed;*/
	}
	MoveSpeedValue = GetCharacterMovement()->MaxWalkSpeed; 
	UBehaviorTree* NewActionTree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), NULL,
		TEXT("BehaviorTree'/Game/EnemyRogue/BT/EnemyBehaviorTree.EnemyBehaviorTree'")));
	EnemyBehaviorTree = NewActionTree;
	/*auto EnemyBehaviorTreeAsset = ConstructorHelpers::FObjectFinder<UBehaviorTree>
		(TEXT("BehaviorTree'/Game/EnemyRogue/BT/EnemyBehaviorTree.EnemyBehaviorTree'"));
	if (EnemyBehaviorTreeAsset.Succeeded())
		EnemyBehaviorTree = EnemyBehaviorTreeAsset.Object;*/
}

void AEnemyRogue::EnemyRogueTakeWeaponDamege(float DefaultTotalDamege, float EffectTotalDamege, float DotDamege,
	int32 WeaponElementNumber, int32 WeaponAttackStack, bool* WeaponEffect,
	bool DoubleAttackChecks, int32 AttackDirectionOne, int32 AttackDirectionTwo, float WeaponSpeed) {
	HitKinds = 0;
	TakeCheckDoubleAttack = DoubleAttackChecks;
	TakeCheckAttackDirection[0] = AttackDirectionOne;
	TakeCheckAttackDirection[1] = AttackDirectionTwo;
	/*if (WeaponEffect[WeaponElementNumber] == false && TakeWeaponElementNumbers != 4)
		TakeWeaponDamege = DefaultTotalDamege;
	else
		TakeWeaponDamege = EffectTotalDamege;*/
	TakeWeaponEffect = WeaponEffect[WeaponElementNumber];
	TakeWeaponElementNumbers = WeaponElementNumber;
	TakeWeaponAttackStack = WeaponAttackStack;
	TakeDotDamege = DotDamege;
	RogueWeaponSpeed = WeaponSpeed;
	TakeTorchSpecial = false;
	ChangeKnockBackValue = 1.f * 1 / (WeaponSpeed * WeaponSpeed);
	if (WeaponKnockBack == true)
		ChangeKnockBackValue = 5.f;
	KnockBackValue = ChangeKnockBackValue;
	GetWorldTimerManager().SetTimer(KnockBackTimeHandle, this, &AEnemyRogue::TakeKnockBack, 0.01, true);
	//SetHp(TakeWeaponDamege);
	if (EnemyDead == false) {
		UGameplayStatics::PlaySoundAtLocation(this, TakeHitSoundCue, GetActorLocation());
		WeaponHitAnimationPlay();
	}
	if (TakeWeaponEffect == true) {
		switch (TakeWeaponElementNumbers) {
		case 0:
			TakeStun();
			ElectriFicationDPlusReady = false;
			break;
		case 1:
			TakeBurn();
			ElectriFicationDPlusReady = false;
			break;
		case 2:
			TakeCold();
			ElectriFicationDPlusReady = false;
			break;
		case 3:
			TakePoison();
			ElectriFicationDPlusReady = false;
			break;
		case 4:
			ElectriFicationDPlusReady = true;
			//TakeElectricExplosion();
			break;
		}
	}
}

void AEnemyRogue::EnemyHitFunc(bool DeadCheck) {
	UGameplayStatics::PlaySoundAtLocation(this, TakeHitSoundCue, GetActorLocation());
	if (DeadCheck == false) {
		WeaponHitAnimationPlay();
	}
	else {
		EnemyRogueDie();
	}
}

void AEnemyRogue::EnemyRogueTakeWeaponPhysicsDamege(float TakePhysicsDamege) {
	HitKinds = 0;
	TakeWeaponPhysicsDamege = TakePhysicsDamege;
	SetHp(TakeWeaponPhysicsDamege);
	EnemyHitFunc(EnemyDead);
	GetWorldTimerManager().SetTimer(KnockBackTimeHandle, this, &AEnemyRogue::TakeKnockBack, 0.01, true);
}

void AEnemyRogue::EnemyRogueTakeWeaponElementDamege(float TakeElementDamege) {
	HitKinds = 0;
	TakeWeaponElementDamege = TakeElementDamege;
	SetHp(TakeWeaponElementDamege);
}

void AEnemyRogue::EnemyRogueTakeElementStatus(int32 Element, float ElementStatusValue) {
	if (ElementStatusLimit[Element] > TakeElementStatusValue)
		TakeElementStatusValue += ElementStatusValue;
	else {
		switch (Element) {
		case 0:
			TakeStun();
			ElectriFicationDPlusReady = false;
			break;
		case 1:
			TakeBurn();
			ElectriFicationDPlusReady = false;
			break;
		case 2:
			TakeCold();
			ElectriFicationDPlusReady = false;
			break;
		case 3:
			TakePoison();
			ElectriFicationDPlusReady = false;
			break;
		case 4:
			ElectriFicationDPlusReady = true;
			//TakeElectricExplosion();
			break;
		}
		TakeElementStatusValue = 0;
	}
}

void AEnemyRogue::EnemyRogueTakeTorchDamege(float StabDamege, float BurnAttacksDamege, float SpecialDamege, int32* TorchEffectStack,
	bool StabAttackOn, bool* DefaultEffect, bool* SpecialEffect, int32 TorchElementNumber) {
	HitKinds = 1;
	ChangeKnockBackValue = 5.f;
	KnockBackValue = ChangeKnockBackValue;
	TakeTorchStabDamege = StabDamege;
	TakeTorchBurnAttacksDamege = BurnAttacksDamege;
	TakeTorchSpecialDamege = SpecialDamege;
	TakeTorchEffectStack = TorchEffectStack[TorchElementNumber];
	TakeTorchSpecial = SpecialEffect[TorchElementNumber];
	TakeTorchElementNumbers = TorchElementNumber;
	TakeStabAttackOn = StabAttackOn;
	TakeDefaultEffect = DefaultEffect[TorchElementNumber];
	UGameplayStatics::PlaySoundAtLocation(this, TakeHitSoundCue, GetActorLocation());
	GetWorldTimerManager().SetTimer(KnockBackTimeHandle, this, &AEnemyRogue::TakeKnockBack, 0.01, true);
	if (TakeStabAttackOn == true) {
		SetHp(TakeTorchStabDamege);
		if (EnemyDead == false) {
			UGameplayStatics::PlaySoundAtLocation(this, TakeHitSoundCue, GetActorLocation());
			TorchHitAnimationPlay();
		}
	}
	if (TakeDefaultEffect == true) {
		switch (TakeTorchElementNumbers) {
		case 0:
			TakeKnockBack();
			break;
		case 1:
			TakeBurnExplosionStack();
			break;
		case 2:
			TakeFreez();
			break;
		case 3:
			TakeVenom();
			break;
		case 4:
			TakeElectiFication();
			break;
		}
	}
	SetHp(TakeTorchBurnAttacksDamege);
	if (TakeTorchSpecial == true) {
		switch (TakeTorchElementNumbers) {
		case 0:
			TakeKnockBackExplosion();
			break;
		case 1:
			TakeBurnExplosion();
			break;
		case 2:
			TakeFreezExplosion();
			break;
		case 3:
			TakeVenomExplosion();
			break;
		case 4:
			TakeElectiFicationExplosion();
			break;
		}
	}
}

void AEnemyRogue::TakeStun() {
	SetHp(TakeWeaponPhysicsDamege*2);
	//StunDotTick = 8;
	//Stun = true;
	//GetWorldTimerManager().SetTimer(StunDotTimeHandle, this, &AEnemyRogue::EnemyRogueTakeStunDotTimer, 0.5, true);
}

void AEnemyRogue::EnemyRogueTakeStunDotTimer() {
	StunDotTick--;
	if (StunDotTick <= 0) {
		GetWorldTimerManager().ClearTimer(StunDotTimeHandle);
		Stun = false;
		StunDotTick = 0;
	}
}

void AEnemyRogue::TakeKnockBack() {
	EnemyRogueVectors = DirectionVector();
	if (TakeTorchSpecial == true) {
		GetCapsuleComponent()->AddRelativeLocation((EnemyRogueVectors) * KnockBigBackValue);
		KnockBigBackValue -= 0.5f;
		if (KnockBigBackValue < 0.f) {
			GetWorldTimerManager().ClearTimer(KnockBackTimeHandle);
			KnockBigBackValue = 15.f;
		}
	}
	else{
		GetCapsuleComponent()->AddRelativeLocation((EnemyRogueVectors) * KnockBackValue);
		KnockBackValue -= 0.1f;
		if (KnockBackValue < 0.f) {
			GetWorldTimerManager().ClearTimer(KnockBackTimeHandle);
			KnockBackValue = ChangeKnockBackValue;
		}
	}
}

void AEnemyRogue::TakeKnockBackExplosion() {
	if (Stun == true)
		TakeTorchSpecialDamege *= 2.f;
	else
		TakeTorchSpecialDamege *= 1.5f;
	ExplosionDamage = TakeTorchSpecialDamege;
	SetHp(ExplosionDamage);
}

//--------------------------------------------------------------

void AEnemyRogue::TakeBurn() {
	TakeBurnExplosion();
	if (Burning == false)
		BurningDotTick = 16;
	Burning = true;
	GetWorldTimerManager().SetTimer(BurnDotTimeHandle, this, &AEnemyRogue::EnemyRogueTakeBurningDotDamege, 0.5, true);
}

void AEnemyRogue::EnemyRogueTakeBurningDotDamege() {
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BurningEffect, GetActorLocation(),
		FRotator(0, 0, 0), FVector(0.5, 0.5, 0.5));
	if (BurningDotTick == 0 || EnemyDead == true) {
		/*UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BurnExplosionEffect, GetActorLocation(),
			FRotator(0, 0, 0), FVector(0.2, 0.2, 0.5));*/
		//SetHp(TakeWeaponElementDamege *2);
		GetWorldTimerManager().ClearTimer(BurnDotTimeHandle);
		Burning = false;
		BurningDotTick = -1;
		TakeWeaponTempDamege = 0;
		//StateEffectStop();
	}
	else {
		SetHp(TakeWeaponElementDamege*0.2);
		//TakeWeaponTempDamege += TakeWeaponDamege;
		
		BurningDotTick--;
	}
}

void AEnemyRogue::TakeBurnExplosion() {
	//TakeTorchSpecial = true;
	//ExplosionBody = true;
	if (Burning == true) {
		//MyGameMode->EnemyRogueEffectStateCheckDelegate.ExecuteIfBound();
		//TakeTorchSpecial = false;
		
		GetWorldTimerManager().ClearTimer(BurnDotTimeHandle);
		Burning = false;
		BurningDotTick = 0;
		//ExplosionDamage = TakeTorchSpecialDamege + TakeWeaponTempDamege * 0.8;
		SetHp(TakeWeaponElementDamege*2.f);
		TakeWeaponTempDamege = 0;
		
		/*UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BurnExplosionEffect, GetActorLocation(),
			FRotator(0, 0, 0), FVector(0.5+TakeWeaponAttackStack*0.05, 0.5 + TakeWeaponAttackStack * 0.05, 0.5 + TakeWeaponAttackStack * 0.05));*/
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BurnExplosionEffect, GetActorLocation(), FRotator(0, 0, 0), FVector(0.5, 0.5, 0.5));
		
		
		//ExplosionBody = false;
	}	
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("WeaponBurnExplosion : %f"), TakeWeaponDamege * 3.f));
		//ExplosionDamage = TakeTorchSpecialDamege;
		SetHp(TakeWeaponElementDamege*1.5f);
	}
	GetWorldTimerManager().SetTimer(KnockBackTimeHandle, this, &AEnemyRogue::TakeKnockBack, 0.01, true);
	TakeWeaponAttackStack = 0;
}

void AEnemyRogue::TakeBurnExplosionStack() {
	BurnExplosionStack = TakeTorchEffectStack;
	for (int i = 0; i < BurnExplosionStack; i++)
		TakeTorchSpecialDamege *= 1.05;
	if (Burning == true)
		TakeBurnExplosion();
}

//----------------------------------------------------------

void AEnemyRogue::TakeCold() {
	TakeFreezExplosion();
	ColdDotTick = 40;
	ColdSlowStack = 3;
	FreezSlow = true;
/*	ColdSlow = true;
	ColdSlowStack++;
	if (ColdSlowStack >= 9)
		ColdSlowStack = 9;
	if (FreezSlow == false)
		ColdDotTick = 24;
	else
		ColdDotTick = 40;*/
	
	EnemyRogueSlow(ColdSlowStack, FreezSlow);
	GetWorldTimerManager().SetTimer(ColdDotTimeHandle, this, &AEnemyRogue::EnemyRogueTakeColdSlowDotTimer, 0.5, true);
}



void AEnemyRogue::EnemyRogueTakeColdSlowDotTimer() {
	if (EnemyDead == false) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ColdSlowEffect, GetActorLocation() + FVector(0, 0, 50),
			FRotator(0, 0, 0), FVector(0.3, 0.3, 0.3));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FreezSlowEffect, GetActorLocation() + FVector(0, 0, 0),
			FRotator(0, 0, 0), FVector(0.1, 0.1, 0.1));
	}
	/*if (FreezSlow == true) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FreezSlowEffect, GetActorLocation() + FVector(0, 0, 0),
			FRotator(0, 0, 0), FVector(0.1, 0.1, 0.1));
	}*/
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("DotTick : %d"), ColdDotTick));
	ColdDotTick--;
	if (ColdDotTick <= 0) {
		ColdSlow = false;
		FreezSlow = false;
		EnemyRogueSlow(ColdSlowStack, FreezSlow);
		GetWorldTimerManager().ClearTimer(ColdDotTimeHandle);
		ColdDotTick = 0;
	}
}

void AEnemyRogue::TakeFreez() {
	FreezSlow = true;
	ColdDotTick = 40;
	EnemyRogueSlow(ColdSlowStack, FreezSlow);
	GetWorldTimerManager().SetTimer(ColdDotTimeHandle, this, &AEnemyRogue::EnemyRogueTakeColdSlowDotTimer, 0.5, true);
	if (ColdSlowStack >= 7 && TakeWeaponElementNumbers == 2) {
		MyGameMode->EnemyRogueEffectStateCheckDelegate.ExecuteIfBound();
		TakeFreezExplosion();
	}
}

void AEnemyRogue::TakeFreezExplosion() {
	//TakeTorchSpecial = true;
	//TakeAllStack();
	UParticleSystem* FreezSlowBoom = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL,
		TEXT("ParticleSystem'/Game/RogueStateEffect/Cold/P_GroundImpact02.P_GroundImpact02'")));
	UParticleSystem* FreezSlowBoomDobule = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL,
		TEXT("ParticleSystem'/Game/FireStick/Ice/P_ProjectileLob_Explo_Ice.P_ProjectileLob_Explo_Ice'")));
	/*if (AllStack >= 5) {
		if (ColdSlowStack >= 5 && TakeWeaponElementNumbers == 2) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FreezSlowBoom, GetActorLocation() + FVector(0, 0, 50),
				FRotator(FMath::FRandRange(-180, 180), FMath::FRandRange(-180, 180), FMath::FRandRange(-180, 180)),
				FVector(1 + ColdSlowStack * 0.1, 1 + ColdSlowStack * 0.1, 1 + ColdSlowStack * 0.1));
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FreezSlowBoomDobule, GetActorLocation() +
				FVector(0, -70, 0), FRotator(0, 0, 0), FVector(0.5, 0.5, 0.5) * 1.5);
			ExplosionDamage = TakeTorchSpecialDamege * 3.f;
			
		}
		else 
			ExplosionDamage = TakeTorchSpecialDamege * 2.f;
			
	}
	else
		ExplosionDamage = TakeTorchSpecialDamege * 1.2;*/
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FreezSlowBoom, GetActorLocation() + FVector(0, 0, 50),
		FRotator(FMath::FRandRange(-180, 180), FMath::FRandRange(-180, 180), FMath::FRandRange(-180, 180)),
		FVector(1 + ColdSlowStack * 0.1, 1 + ColdSlowStack * 0.1, 1 + ColdSlowStack * 0.1));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FreezSlowBoomDobule, GetActorLocation() +
		FVector(0, -70, 0), FRotator(0, 0, 0), FVector(0.5, 0.5, 0.5) * 1.5);
	ExplosionDamage = TakeWeaponElementDamege * 1.5f;
	SetHp(ExplosionDamage);
	//TakeStackInit();
	//AllDotTickInit();
	
	GetWorldTimerManager().SetTimer(KnockBackTimeHandle, this, &AEnemyRogue::TakeKnockBack, 0.01, true);
}

//----------------------------------------------------------


void AEnemyRogue::TakePoison() {
	TakeVenomExplosion();
	/*if (Venom == true) {
		VenomStack++;
		PoisonStack = VenomStack;
	}
	else
		PoisonStack++;
	if (VenomStack >= 12)
		VenomStack = 12;
	if (PoisonStack >= 12)
		PoisonStack = 12;*/
	Poison = true;
	PoisonDotTick = 12;
	
	GetWorldTimerManager().SetTimer(PoisonDotTimeHandle, this, &AEnemyRogue::EnemyRogueTakePoisonDotDamege, 0.5, true);
}

void AEnemyRogue::TakeVenom() {
	TakeVenomExplosion();
	Venom = true;
	if (Poison == true) {
		PoisonStack++;
		if (PoisonStack >= 12)
			PoisonStack = 12;
		VenomStack = PoisonStack;
		PoisonDotTick = 15;
		GetWorldTimerManager().SetTimer(PoisonDotTimeHandle, this, &AEnemyRogue::EnemyRogueTakePoisonDotDamege, 0.5, true);
	}
	else {
		VenomStack++;
		if (VenomStack >= 5)
			VenomStack = 5;
		PoisonDotTick = 12;
		GetWorldTimerManager().SetTimer(PoisonDotTimeHandle, this, &AEnemyRogue::EnemyRogueTakePoisonDotDamege, 0.5, true);
	}
}

void AEnemyRogue::TakeVenomExplosion() {
	TakeTorchSpecial = true;
	UParticleSystem* VenomBoom = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL,
		TEXT("ParticleSystem'/Game/RogueStateEffect/Poison/P_Aura_Poison_Shatter_01.P_Aura_Poison_Shatter_01'")));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VenomBoom, GetActorLocation() + FVector(0, 0, 0),
		FRotator(0, 0, 0), FVector(0.5, 0.5, 0.3));
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("VenomExplosionDamege : %f"), VenomStack * TakeTorchSpecialDamege));
	SetHp(TakeWeaponElementDamege*1.2f);
	//VenomStack /= 2;
	//PoisonStack /= 2;
	/*if (TakeWeaponElementNumbers == 3) {
		
	}
	else {
		TakeAllStack();
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("VenomExplosionDamege : %f"), AllStack * TakeTorchSpecialDamege));
		//ExplosionDamage = AllStack * TakeTorchSpecialDamege;
		//SetHp(ExplosionDamage);
		TakeStackInit();
		AllDotTickInit();
	}*/
	GetWorldTimerManager().SetTimer(KnockBackTimeHandle, this, &AEnemyRogue::TakeKnockBack, 0.01, true);
}

void AEnemyRogue::EnemyRogueTakePoisonDotDamege() {
	float DotDamege;
	//if (Venom == true) {
		DotDamege = TakeWeaponElementDamege * 0.1;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VenomEffect, GetActorLocation() + FVector(0, 0, 0),
			FRotator(0, 0, 0), FVector(0.5, 0.5, 1));
	//}
	/*else {
		DotDamege = TakeDotDamege * PoisonStack;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PoisonEffect, GetActorLocation() + FVector(0, 0, 50),
			FRotator(0, 0, 0), FVector(1, 1, 1));
	}*/
	SetHp(DotDamege);
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("DotTick : %d"), PoisonDotTick));
	PoisonDotTick--;
	if (PoisonDotTick <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("OverPoison")));
		GetWorldTimerManager().ClearTimer(PoisonDotTimeHandle);
		Poison = false;
		Venom = false;
		PoisonStack = 0;
		VenomStack = 0;
		PoisonDotTick = 0;
	}
}

//-------------------------------------------------------------------------------------

void AEnemyRogue::EnemyRogueTakeElectriFicationDotTimer() {
	if (GetFicationValue() > 1.f)
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("DotTick : %d"), ElectriFicationDotTick));
	ElectriFicationDotTick--;
	if (ElectriFicationDPlus == true) {
		UParticleSystem* ElectroDotEffect1 = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL,
			TEXT("ParticleSystem'/Game/RogueStateEffect/ElectriFication/P_ky_lightning3.P_ky_lightning3'")));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElectroDotEffect1, GetActorLocation() +
			FVector(FMath::FRandRange(-20, 20), FMath::FRandRange(-20, 20), FMath::FRandRange(-20, 20)),
			FRotator(0, 0, 0),
			FVector(0.3 + FMath::FRandRange(-0.2, 0.4), 0.3 + FMath::FRandRange(-0.2, 0.4), 0.2 + FMath::FRandRange(-0.2, 0.4)));
		SetHp(1.5f);
	}
	else if (ElectriFicationPlus == true) {
		UParticleSystem* ElectroDotEffect2 = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL,
			TEXT("ParticleSystem'/Game/RogueStateEffect/ElectriFication/P_ky_lightning2.P_ky_lightning2'")));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElectroDotEffect2, GetActorLocation() +
			FVector(FMath::FRandRange(-20, 20), FMath::FRandRange(-20, 20), FMath::FRandRange(-20, 20)),
			FRotator(0, 0, 0),
			FVector(0.3 + FMath::FRandRange(-0.2, 0.4), 0.3 + FMath::FRandRange(-0.2, 0.4), 0.2 + FMath::FRandRange(-0.2, 0.4)));
		SetHp(2.f);
	}
	else if(ElectriFication == true) {
		UParticleSystem* ElectroDotEffect3 = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL,
			TEXT("ParticleSystem'/Game/RogueStateEffect/ElectriFication/P_ky_lightning1.P_ky_lightning1'")));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElectroDotEffect3, GetActorLocation() +
			FVector(FMath::FRandRange(-20, 20), FMath::FRandRange(-20, 20), FMath::FRandRange(-20, 20)),
			FRotator(0, 0, 0),
			FVector(0.3 + FMath::FRandRange(-0.2, 0.4), 0.3 + FMath::FRandRange(-0.2, 0.4), 0.2 + FMath::FRandRange(-0.2, 0.4)));
		SetHp(3.f);
	}
	if (ElectriFicationDotTick <= 0) {
		ElectriFicationDotTick = 0;
		ElectriFication = false;
		ElectriFicationPlus = false;
		ElectriFicationDPlus = false;
		TakeTorchEffectStack = 0;
		SetFicationValue(1.f);
		GetWorldTimerManager().ClearTimer(ElectriFicationTimeHandle);
	}
}


void AEnemyRogue::TakeElectiFication() {
	
	if (ElectriFicationDPlus == true || ElectriFicationPlus == true)
		ElectriFication = false;
	else
		ElectriFication = true;
	if (TakeTorchEffectStack >= 4) {
		if (ElectriFicationDPlus == true)
			ElectriFicationDotTick = 30;
		else if(ElectriFicationPlus == true)
			ElectriFicationDotTick = 20;
		else {
			SetFicationValue(1.5f);
			ElectriFicationDotTick = 10;
			GetWorldTimerManager().SetTimer(ElectriFicationTimeHandle, this, &AEnemyRogue::EnemyRogueTakeElectriFicationDotTimer, 0.5, true);
			TakeTorchEffectStack = 0;
		}
	}
}

void AEnemyRogue::TakeElectiFicationExplosion() {
	if (ElectriFicationDPlusReady == true) {
		ElectriFication = false;
		ElectriFicationPlus = false;
		ElectriFicationDPlus = true;
		SetFicationValue(3.f);
		ElectriFicationDotTick = 30;
		GetWorldTimerManager().SetTimer(ElectriFicationTimeHandle, this, &AEnemyRogue::EnemyRogueTakeElectriFicationDotTimer, 0.5, true);
	}
	else {
		ElectriFication = false;
		ElectriFicationPlus = true;
		ElectriFicationDPlus = false;
		SetFicationValue(2.f);
		ElectriFicationDotTick = 20;
		GetWorldTimerManager().SetTimer(ElectriFicationTimeHandle, this, &AEnemyRogue::EnemyRogueTakeElectriFicationDotTimer, 0.5, true);
	}
}

//------------------------------------------------------------------------------

void AEnemyRogue::EnemyRogueSlow(int32 SlowStack, bool Freez) {
	if (Freez == true) {
		SlowValue -= SlowStack * 0.15;
	}
	else
		SlowValue = 1.f;

	/*if (ColdDotTick <= 0)
		SlowValue = 1.f;
	else {
		if (SlowValue >= 0.1) {
			if (Freez == true) {
				SlowValue -= SlowStack * 0.01;
			}
			else {
				SlowValue -= SlowStack * 0.05;
			}
			if (SlowValue <= 0.f)
				SlowValue = 0.1f;
		}
	}*/
}

void AEnemyRogue::EnemyRogueDie() {
	MyGameMode->RogueSetDataDelegate.ExecuteIfBound(-(DeathData / 2));
	MyGameMode->RogueSetKarmaDelegate.ExecuteIfBound(Karma);
	myRogue->MyRogueState->setRogueKill(1);
	myRogue->MyRogueState->setRogueTotalKill(1);
	GetCapsuleComponent()->SetCollisionProfileName("Death");
	/*if (GiftAbilityPer >= FMath::FRandRange(0, 100)) {
		GiftAbilityPer = 100.f;
		GiftAbilityIndex = FMath::FRandRange(0, 10);
		//MyGameMode->EnemyRogueDeathAndSendWeaponDelegate.ExecuteIfBound(GiftAbilityIndex);
	}
	else {
		GiftAbilityPer += 5.f;
	}*/
	//MyGameMode->Widget_ChangedWidgetDelegate.ExecuteIfBound(99);
	//Destroy();
	int32 DeathFormIndex = FMath::FRandRange(0, 8);

	if (DeathFormIndex == 0) {
		DeathForm = EnemyAnimInst->EnemyDownDeath1[1];
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyDownDeath1[0]);
	}
	else if (DeathFormIndex == 1) {
		DeathForm = EnemyAnimInst->EnemyDownDeath2[1];
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyDownDeath2[0]);
	}
	else if (DeathFormIndex == 2) {
		DeathForm = EnemyAnimInst->EnemyDownDeath3[1];
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyDownDeath3[0]);
	}

	else if (DeathFormIndex == 3) {
		DeathForm = EnemyAnimInst->EnemyUpDeath1[1];
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyUpDeath1[0]);
	}
	else if (DeathFormIndex == 4) {
		DeathForm = EnemyAnimInst->EnemyUpDeath2[1];
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyUpDeath2[0]);
	}
	else if (DeathFormIndex == 5) {
		DeathForm = EnemyAnimInst->EnemyUpDeath3[1];
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyUpDeath3[0]);
	}
	else if (DeathFormIndex <= 6) {
		DeathForm = EnemyAnimInst->EnemyDownDeath1[1];
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyDownDeath1[0]);
	}
	else if (DeathFormIndex == 7) {
		DeathForm = EnemyAnimInst->EnemyDownDeath2[1];
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyDownDeath2[0]);
	}
	else if (DeathFormIndex == 8) {
		DeathForm = EnemyAnimInst->EnemyUpDeath3[1];
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyUpDeath3[0]);
	}
}

void AEnemyRogue::SetHp(float Damege) {
	AEnemyAIController* AIControllers = Cast<AEnemyAIController>(GetController());
	float DamegeRange = FMath::FRandRange(0.8, 1.2);
	if (EnemyDead == false) {
		Hp -= (Damege * ElectriFicationValue) * DamegeRange;
		if (GetHp() <= 0) {
			EnemyDead = true;
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("Death"));
			GetMesh()->SetCollisionProfileName(TEXT("Death"));
		}
		if (AIControllers->SenseRogue == false) {
			RootComponent->AddRelativeRotation(FRotator(0, 180, 0));
		}
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("EnemyRogue Hp : %f"), Damege));
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("TakeDamege : %f"), (Damege * ElectriFicationValue) * DamegeRange));
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("EnemyRogue Hp : %f"), GetHp()));
	}
	//EnemyRogueDie();
}

void AEnemyRogue::TakeAllStack() {
	AllStack = BurnExplosionStack + ColdSlowStack + PoisonStack + VenomStack + ElectricHitStack;
}

void AEnemyRogue::TakeStackInit() {
	AllStack = 0;
	BurnExplosionStack = 0;
	ColdSlowStack = 0;
	PoisonStack = 0;
	VenomStack = 0;
	ElectricHitStack = 0;
	KnockBackValue = 5.f;
	KnockBigBackValue = 15.f;
}

void AEnemyRogue::AllDotTickInit() {
	BurningDotTick = 0;
	ColdDotTick = 0;
	PoisonDotTick = 0;
	ElectriFicationDotTick = 0;
}


void AEnemyRogue::AllClearTimer() {
	GetWorldTimerManager().ClearTimer(BurnDotTimeHandle);
	GetWorldTimerManager().ClearTimer(ColdDotTimeHandle);
	GetWorldTimerManager().ClearTimer(PoisonDotTimeHandle);
	GetWorldTimerManager().ClearTimer(ElectriFicationTimeHandle);
}

void AEnemyRogue::AllStateInit() {
	Stun = false;
	Burn = false;
	Burning = false;
	ColdSlow = false;
	FreezSlow = false;
	Poison = false;
	Venom = false;
	Hit = false;
	Idle = false;
	Attack = false;
	Walk = false;
	TakeWeaponTempDamege = 0;
}


void AEnemyRogue::StateEffectInit() {
	BurningRef = TEXT("ParticleSystem'/Game/RogueStateEffect/Burning/2_bonefire_fwd2_pt.2_bonefire_fwd2_pt'");
	BurnExplosionRef = TEXT("ParticleSystem'/Game/RogueStateEffect/Burning/Fire_Exp_00.Fire_Exp_00'");
	ColdRef = TEXT("ParticleSystem'/Game/RogueStateEffect/Cold/P_ProjectileLob_Ice.P_ProjectileLob_Ice'");
	FreezRef = TEXT("ParticleSystem'/Game/RogueStateEffect/Cold/P_Player_Frozen_Exit_01.P_Player_Frozen_Exit_01'");
	PoisonRef = TEXT("ParticleSystem'/Game/RogueStateEffect/Poison/P_Wolf_Body_Poison_01.P_Wolf_Body_Poison_01'");
	VenomRef = TEXT("ParticleSystem'/Game/RogueStateEffect/Poison/P_Skill_Leap_Poison_Impact_Impact.P_Skill_Leap_Poison_Impact_Impact'");
	ElectriFicationRef1 = TEXT("ParticleSystem'/Game/RogueStateEffect/ElectriFication/P_ky_thunderStorm.P_ky_thunderStorm'");

	BurningEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, BurningRef));
	BurnExplosionEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, BurnExplosionRef));
	ColdSlowEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, ColdRef));
	FreezSlowEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, FreezRef));
	PoisonEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, PoisonRef));
	VenomEffect = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, VenomRef));
	ElectriFicationEffect1 = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, ElectriFicationRef1));
}

/*void AEnemyRogue::StateEffectPlay() {
	if (Burning == true)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BurningEffect, GetActorLocation(),
			FRotator(0, 0, 0), FVector(0.5, 0.5, 1));
	if(Burn == true)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BurnExplosionEffect, GetActorLocation(),
			FRotator(0, 0, 0), FVector(0.1, 0.1, 0.2));
	if(ColdSlow == true)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ColdEffect, GetActorLocation(),
			FRotator(0, 0, 0), FVector(0.5, 0.5, 1));

}*/

void AEnemyRogue::TakeAttackVector(FVector TakeAttackVectors) {
	TakeAttackVectorValue = TakeAttackVectors;
	
}

void AEnemyRogue::TakeWeaponKnockBackCheck(bool KnockBackCheck) { 
	if(KnockBackCheck == true)
		WeaponKnockBack = true; 
	else
		WeaponKnockBack = false;
}

FVector AEnemyRogue::DirectionVector() {
	FVector Dest = FVector(GetTransform().GetLocation().X, GetTransform().GetLocation().Y, 0.f);
	FVector Start = FVector(myRogue->GetTransform().GetLocation().X, myRogue->GetTransform().GetLocation().Y, 0.f);


	FVector Dir = Dest - Start;
	FVector DirNomal = Dir.GetSafeNormal();

	float dot = FVector::DotProduct(myRogue->AttackFowardVectors, DirNomal);
	float AcosAngle = FMath::Acos(dot);
	float angle = FMath::RadiansToDegrees(AcosAngle);
	FVector Cross = FVector::CrossProduct(myRogue->AttackFowardVectors, DirNomal);
	
	return DirNomal;
}

void AEnemyRogue::WeaponHitAnimationPlay() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("AttackDirction %d"), 
		TakeCheckAttackDirection[HitDirectionIndex]));
	//EnemyAnimInst->Roll();
	//TakeCheckDoubleAttack
	//TakeCheckAttackDirection[0]
	//TakeCheckAttackDirection[1]
	int32 SuperArmorPer = FMath::RandRange(0, 9);
	if (HitCount < HitCountLimite && HitSuperArmorCount == 0) {
		HitCount++;
		if (SuperArmorPer >= 2) {
			WeaponAttackRandHitIndex = FMath::FRandRange(0, 4);
			if (TakeCheckAttackDirection[HitDirectionIndex] == 0) {
				if (WeaponAttackRandHitIndex <= 2) {
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyDownHit1, 1.f * SlowValue);
				}
				else if (WeaponAttackRandHitIndex == 3) {
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySideAndDownHit1, 1.f * SlowValue);
				}
				else if (WeaponAttackRandHitIndex == 4) {
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySideHit1, 1.f * SlowValue);
				}
			}
			else if (TakeCheckAttackDirection[HitDirectionIndex] == 1) {
				if (WeaponAttackRandHitIndex <= 1)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyUpHit1, 1.f * SlowValue);
				else if (WeaponAttackRandHitIndex <= 3) {
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyUpHit2, 1.f * SlowValue);
				}
				else if (WeaponAttackRandHitIndex == 4) {
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySideAndUpHit1, 1.f * SlowValue);
				}
			}
			else if (TakeCheckAttackDirection[HitDirectionIndex] == 2) {
				if (WeaponAttackRandHitIndex <= 2)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySideHit1, 1.f * SlowValue);
				else if (WeaponAttackRandHitIndex == 3) {
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySideAndDownHit1, 1.f * SlowValue);
				}
				else if (WeaponAttackRandHitIndex == 4) {
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySideAndUpHit1, 1.f * SlowValue);
				}
			}
			LastAttackDirection = TakeCheckAttackDirection[HitDirectionIndex];
			if (TakeCheckDoubleAttack == true) {
				if (HitDirectionIndex == 1)
					HitDirectionIndex = 0;
				else if (HitDirectionIndex == 0)
					HitDirectionIndex++;
			}
			else {
				HitDirectionIndex = 0;
			}
		}
	}
	else if(HitCount >= HitCountLimite) {
		HitCount = 0;
		HitSuperArmorCount = HitSuperArmorCountLimit-1;
	}
	else {
		HitSuperArmorCount--;
	}
}

void AEnemyRogue::TorchHitAnimationPlay() {
	TorchAttackRandHitIndex = FMath::RandRange(0, 4);
	switch (TorchAttackRandHitIndex) {
	case 0:
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyTorchDownHit1, 1.f * SlowValue);
		//EnemyAnimInst->Montage_SetPlayRate(EnemyAnimInst->EnemyDownHit1, AttackTempRate);
		break;
	case 1:
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyTorchUpHit1, 1.f * SlowValue);
		//EnemyAnimInst->Montage_SetPlayRate(EnemyAnimInst->EnemyUpHit1, AttackTempRate);
		break;
	case 2:
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyTorchSideAndUpHit1, 1.f * SlowValue);
		//EnemyAnimInst->Montage_SetPlayRate(EnemyAnimInst->EnemySideAndUpHit1, AttackTempRate);
		break;
	case 3:
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyTorchUpHit2, 1.f * SlowValue);
		//EnemyAnimInst->Montage_SetPlayRate(EnemyAnimInst->EnemyUpHit2, AttackTempRate);
		break;
	case 4:
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyTorchSideAndDownHit1, 1.f * SlowValue);
		//EnemyAnimInst->Montage_SetPlayRate(EnemyAnimInst->EnemySideAndDownHit1, AttackTempRate);
		break;
	}
}

//EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->FinalEnemyAttackForm) == true ||
bool AEnemyRogue::CheckAttack() {
	if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->FinalEnemyAttackForm) == true || EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyRoll) == true) {
		return true;
	}
	else
		return false;
}

bool AEnemyRogue::DoAttack() {
	EnemyAnimInst->EnemyRogueAttackFormIndex();
	if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->FinalEnemyAttackForm) != true) {
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("EnemyAttack"));
			//EnemyRogueWeaponSpeed
		//EnemyAnimInst->Montage_SetPlayRate(EnemyAnimInst->FinalEnemyAttackForm, EnemyRogueWeaponSpeed);
		GetMesh()->SetCollisionProfileName(TEXT("EnemyAttack"));
		EnemyAnimInst->Montage_Play(EnemyAnimInst->FinalEnemyAttackForm, EnemyRogueWeaponSpeed*1.2f*SlowValue);
		return true;
	}
	return false;
}

bool AEnemyRogue::DoIdle(int32 IdleIndex) {
	if (EnemyAnimInst->AnimationAllCheck == true) {
		if (EnemyForm <= 6) {
			if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyNormalIdle) != true) {
				EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyNormalIdle, 1.f * SlowValue);
				return true;
			}
			return false;
		}
		else if (EnemyForm <= 8) {
			if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyCombatIdle) != true) {
				EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyCombatIdle, 1.f * SlowValue);
				return true;
			}
			return false;
		}
		else if (EnemyForm <= 10) {
			if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemySadIdle) != true) {
				EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySadIdle, 1.f * SlowValue);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

/*bool AEnemyRogue::DoOrbitingWalk(int32 OrbitingDir) {
	if (EnemyAnimInst->AnimationAllCheck == true) {
		if()
	}
}*/

bool AEnemyRogue::DoWalk(int32 WalkIndex) {
	
	if (EnemyAnimInst->AnimationAllCheck == true) {
		if (EnemyForm <= 6) {
			switch (WalkIndex) {
			case 0:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyForwardWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyForwardWalk, 1.f * SlowValue);
				break;
			case 1:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyRightWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyRightWalk, 1.f * SlowValue);
				break;
			case 2:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyLeftWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyLeftWalk, 1.f * SlowValue);
				break;
			case 3:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyBackWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyBackWalk, 1.f * SlowValue);
				break;
			}
			return true;
		}
		else if (EnemyForm <= 8) {
			switch (WalkIndex) {
			case 0:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyCombatForwardWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyCombatForwardWalk, 1.f * SlowValue);
				break;
			case 1:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyCombatRightWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyCombatRightWalk, 1.f * SlowValue);
				break;
			case 2:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyCombatLeftWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyCombatLeftWalk, 1.f * SlowValue);
				break;
			case 3:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyCombatBackWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyCombatBackWalk, 1.f * SlowValue);
				break;
			}
			return true;
		}
		else if (EnemyForm <= 10) {
			switch (WalkIndex) {
			case 0:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemySadForwardWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySadForwardWalk, 1.f * SlowValue);
				break;
			case 1:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemySadRightWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySadRightWalk, 1.f * SlowValue);
				break;
			case 2:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemySadLeftWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySadLeftWalk, 1.f * SlowValue);
				break;
			case 3:
				if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemySadBackWalk) != true)
					EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemySadBackWalk,1.f*SlowValue);
				break;
			}
			return true;
		}
	}
	return false;
}

bool AEnemyRogue::DoConfused() {
	if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyConfused) != true) {
		EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyConfused);
		return true;
	}
	return false;
}

bool AEnemyRogue::DoAnyThing() {
	if (EnemyAnimInst->IsAnyMontagePlaying() == true)
		return true;
	else
		return false;
}

bool AEnemyRogue::DoRoll(int32 RollDirection) {
	if (RollDirection == 0) {
		if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyRoll) == false) {
			EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyRoll, 1.f*SlowValue);
			return true;
		}
		return false;
	}
	else if (RollDirection == 1) {
		if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyBackRoll) == false) {
			EnemyAnimInst->Montage_Play(EnemyAnimInst->EnemyBackRoll);
			return true;
		}
		return false;
	}
	else
		return false;
}

bool AEnemyRogue::CheckHit() {
	if (EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyUpHit1) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyUpHit2) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemySideHit1) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemySideAndDownHit1) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyDownHit1) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemySideAndUpHit1) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyTorchUpHit1) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyTorchUpHit2) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyTorchSideAndDownHit1) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyTorchDownHit1) == false
		&& EnemyAnimInst->Montage_IsPlaying(EnemyAnimInst->EnemyTorchSideAndUpHit1) == false) {
		return false;
	}
	else
		return true;
}

bool AEnemyRogue::GetTakeHit() {
	return AttackCanHit; 
}

void AEnemyRogue::SetTakeHit(bool newTakeHitState) {
	AttackCanHit = newTakeHitState; 
	EnemyRogueWeapon->SetTakeHit(AttackCanHit);
}


/*if (EnemyForm <= 6) {
	UAnimInstance* EnemyAnim = Cast<UAnimInstance>(StaticLoadClass(UAnimInstance::StaticClass(), NULL,
		TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation.BP_EnemyRogueAnimation_C'")));
	//auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
		//(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation.BP_EnemyRogueAnimation_C'"));
	//if (BlandAnim.Succeeded()) {
	GetMesh()->SetAnimInstanceClass(EnemyAnim->GetClass());
}
GetCharacterMovement()->MaxWalkSpeed = 145.f;
	}
	else if (EnemyForm <= 8) {
	auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
		(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_2.BP_EnemyRogueAnimation_2_C'"));
	if (BlandAnim.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
	}
	GetCharacterMovement()->MaxWalkSpeed = 165.f;
	}
	else if (EnemyForm <= 9) {
	auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
		(TEXT("AnimBlueprint'/Game/EnemyRogue/BP_EnemyRogueAnimation_3.BP_EnemyRogueAnimation_3_C'"));
	if (BlandAnim.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
	}
	GetCharacterMovement()->MaxWalkSpeed = 85.f;
	}
	MoveSpeedValue = GetCharacterMovement()->MaxWalkSpeed;*/