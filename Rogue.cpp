// Fill out your copyright notice in the Description page of Project Settings.


#include "Rogue.h"
#include "EnemyRogue.h"
#include "EnemyRogueWeapon.h"
#include "RogueWeapon.h"

// Sets default values
ARogue::ARogue()
{
	PrimaryActorTick.bCanEverTick = true;
	RogueStateInit();
	RogueMovementInit();
	RogueViewInit();
	RogueWeaponInit();
	RogueTorchInit();
	setCanHit(false);
	SetTorchCanHit(false);
	//DialogueInit();
}

// Called when the game starts or when spawned
void ARogue::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("RoguePlace %d"), GetWeaponNumber()));
	UPlayerInput* PlayerInputControll = GetWorld()->GetFirstPlayerController()->PlayerInput;
	AxisMapping(PlayerInputControll);
	PostInitializeComponents();
	getWorldGameMode();
	WeaponTorchDelegateInit();
	RogueAbilityDelegateInit();
	WeaponChange();
	SetFOV(MyGameMode->FOVValue);
	//WindowArm->SetRelativeRotation(FRotator(90.f, 0.f, -90.f));
	MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(0);
}

void ARogue::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	WeaponTorchUnDelegate();
}

// Called every frame
void ARogue::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);
	RogueViewWork();
	RogueMovementValue();
	NotAttackState();
	IdleState();
	
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Y : %f"), GetControlRotation().Vector().Y));
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("X : %f"), GetControlRotation().Vector().X));
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Z : %f"), GetControlRotation().Vector().Z));
}

// Called to bind functionality to input
void ARogue::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	BindAxis_func(PlayerInputComponent);
}

void ARogue::PostInitializeComponents() {
	Super::PostInitializeComponents();
	SetRogueAnimInstance = GetMesh()->GetAnimInstance();
	myAnimInst = Cast<URogueAnimInstance>(SetRogueAnimInstance);
}

void ARogue::getWorldGameMode() {
	UWorld* TheWorld = GetWorld();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
	MyGameMode = Cast<ACastle_in_DungeonGameModeBase>(GameMode);
	MyRogueState = Cast<ARogueState>(GetPlayerState());
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARogue::EnterBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ARogue::EnterEndOverlap);
}

void ARogue::WeaponTorchDelegateInit() {
	MyGameMode->WeaponWallCrash.BindUObject(this, &ARogue::AttackFinish);
	MyGameMode->TorchWallCrash.BindUObject(this, &ARogue::ForwardStop);
	MyGameMode->TorchWallLeave.BindUObject(this, &ARogue::ForwardDo);
	MyGameMode->TorchWallSideCrash.BindUObject(this, &ARogue::SideStop);
	MyGameMode->TorchWallSideLeave.BindUObject(this, &ARogue::SideDo);
	//UseWeaponNumber.BindUObject(this, &ARogue::)
}

void ARogue::WeaponTorchUnDelegate() {
	MyGameMode->WeaponWallCrash.Unbind();
	MyGameMode->TorchWallCrash.Unbind();
	MyGameMode->TorchWallLeave.Unbind();
	MyGameMode->TorchWallSideCrash.Unbind();
	MyGameMode->TorchWallSideCrash.Unbind();
}

void ARogue::RogueAbilityDelegateInit(){
	MyGameMode->Rogue_GetHpDelegate.BindUObject(this, &ARogue::CheckHp);
	MyGameMode->Return_GameStartWeaponNumberDelegate.BindUObject(this, &ARogue::RogueWeaponNumberInit);
	//MyGameMode->Call_GameStartWeaponNumberDelegate.ExecuteIfBound();
	MyGameMode->Widget_MouseCursorOnRogueNotInputDelegate.BindUObject(this, &ARogue::RogueCanNotInput);
	MyGameMode->RogueSpeedIncreaseDelegate.BindUObject(this, &ARogue::SetMultiplySpeed);
	MyGameMode->RogueSuperArmorDelegate.BindUObject(this, &ARogue::SuperArmorCheck);
	MyGameMode->Rogue_SpeedValueDelegate.ExecuteIfBound(Speed * 10);
	MyGameMode->Call_RogueFOVDelegate.BindUObject(this, &ARogue::SetFOV);
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("ddd %f"), Speed*10));
}

void ARogue::FrontDialogueWindow() {
	WindowArm->AddRelativeRotation(FRotator(150.f, 0.f, 0.f));
}

void ARogue::ReturnDialogueWindow() {
	
}

void ARogue::DialogueInit() {
	
	//RogueDialogue->SetRelativeRotation(FRotator())
}

void ARogue::SetFOV(float NewFOVValue) {
	RogueView->SetFieldOfView(NewFOVValue);
}

void ARogue::CheckHp(int32 newHp) {
	RogueHp = newHp;
}

void ARogue::RogueCanNotInput(int32 value) {
	if (value == 0)
		CanInput = false;
	else
		CanInput = true;
}

void ARogue::SetMultiplySpeed(float NewSpeed) { 
	Speed = NewSpeed; 
	MyGameMode->Rogue_SpeedValueDelegate.ExecuteIfBound(Speed * 10);
}

void ARogue::RogueStateInit() {
	forward = false;
	right = false;
	left = false;
	back = false;
	attack = false;
	CombatStart = false;
	Canforward = true;
	CanSide = true;
	AttackFormFinsh = false;
	SuperArmorPer = 0.f;
	AttackStoping = false;
	//RogueHp = 300;
	//AttackForm = 0;

	RoguePerceptionStimuliSource =
		CreateOptionalDefaultSubobject<UAIPerceptionStimuliSourceComponent>("RoguePSS");

	auto MeshAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>
		(TEXT("SkeletalMesh'/Game/Character/Ch44_nonPBR.Ch44_nonPBR'"));
	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	auto BlandAnim = ConstructorHelpers::FClassFinder<UAnimInstance>
		(TEXT("AnimBlueprint'/Game/Character/BP_RogueAnimation.BP_RogueAnimation_C'"));
	if (BlandAnim.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(BlandAnim.Class);
	}

	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetCapsuleComponent()->SetCapsuleRadius(30);
	GetMesh()->SetCollisionProfileName("RogueAttackStateCollision");
	GetCapsuleComponent()->SetCollisionProfileName("RogueBodyCollision");

	//RoguePerceptionStimuliSource->GetAi
	auto TakeHitSoundAsset = ConstructorHelpers::FObjectFinder<USoundCue>
		(TEXT("SoundCue'/Game/Sound/SoundQue/TakeHit/RogueTakeHit2_Cue.RogueTakeHit2_Cue'"));
	if (TakeHitSoundAsset.Succeeded()) {
		TakeHitSoundCue = TakeHitSoundAsset.Object;
	}
}

void ARogue::RogueMovementInit() {
	LastInput = FVector::ZeroVector;
	setAxel(0.00f);
	setSpeed(0.1f);
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("%f"), getSpeed()));
	setTurnSpeed(0.3f);
	setAttackQue(0);
	setAttackAfterTime(0.f);
	GetCharacterMovement()->MaxWalkSpeed = 1500;
	
}

void ARogue::RogueViewInit() {
	ViewRotator = 0.0f;
	ViewArm = CreateDefaultSubobject<USpringArmComponent>("ViewArm");
	ViewArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, (TEXT("Head")));

	ViewArm->TargetArmLength = 0.f;
	ViewArm->CameraLagSpeed = 3.f;
	ViewArm->CameraRotationLagSpeed = 10.f;
	ViewArm->bEnableCameraLag = true;
	ViewArm->bEnableCameraRotationLag = true;
	ViewArm->AddRelativeRotation(FRotator(90.f, 0, -90.f));
	RogueView = CreateDefaultSubobject<UCameraComponent>("RogueView");
	RogueView->AttachToComponent(ViewArm, FAttachmentTransformRules::KeepRelativeTransform);
	//RogueView->SetFieldOfView(100.f);

	WindowArm = CreateDefaultSubobject<USpringArmComponent>("WindowArm");
	WindowArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, (TEXT("Head")));
	WindowArm->TargetArmLength = 10.f;
	//WindowArm->CameraLagSpeed = 8.f;
	WindowArm->CameraRotationLagSpeed = 15.f;
	//WindowArm->bEnableCameraLag = true;
	WindowArm->bEnableCameraRotationLag = true;
	//WindowArm->SetRelativeRotation(FRotator(90.f, 0.f, -90.f));

	DialogueWindowPlane = CreateDefaultSubobject<UStaticMeshComponent>("DialogueWindowPlane");
	DialogueWindowPlane->AttachToComponent(WindowArm, FAttachmentTransformRules::KeepRelativeTransform);
	DialogueWindowCase = CreateDefaultSubobject<UStaticMeshComponent>("DialogueWindowCase");
	DialogueWindowCase->AttachToComponent(DialogueWindowPlane, FAttachmentTransformRules::KeepRelativeTransform);
	auto DialogueWindowPlaneAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Dialogue_Video/DialoguePlane.DialoguePlane'"));
	auto DialogueWindowCaseAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Dialogue_Video/DialogueCase.DialogueCase'"));
	if (DialogueWindowCaseAsset.Succeeded())
		DialogueWindowPlane->SetStaticMesh(DialogueWindowCaseAsset.Object);
	if (DialogueWindowPlaneAsset.Succeeded())
		DialogueWindowPlane->SetStaticMesh(DialogueWindowPlaneAsset.Object);
}

void ARogue::RogueTorchInit() {
	RogueTorchs = CreateDefaultSubobject<UChildActorComponent>("RogueTorch");
	auto TorchAsset = ConstructorHelpers::FClassFinder<AActor>
		(TEXT("Class'/Script/Castle_in_Dungeon.RogueTorch'"));

	if (TorchAsset.Succeeded()) {
		RogueTorchs->SetChildActorClass(TorchAsset.Class);
	}
	RogueTorchs->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftHandIndex1"));
	RogueTorchs->SetRelativeTransform(FTransform(FRotator(90, 0, 0), FVector(20, 0, 5), FVector(1, 1, 1)));
}

void ARogue::RogueWeaponInit() {
	RogueWeapons = CreateDefaultSubobject<UChildActorComponent>("RogueWeapon");
	auto WeaponAsset = ConstructorHelpers::FClassFinder<AActor>
		(TEXT("Class'/Script/Castle_in_Dungeon.RogueWeapon'"));
	if (WeaponAsset.Succeeded()) {
		RogueWeapons->SetChildActorClass(WeaponAsset.Class);
	}
	RogueWeapons->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandFarm"));
	RogueWeapons->SetRelativeRotation(FRotator(270, 0, 0));
	//RogueWeapons->SetRelativeLocation(FVector(-2, 0, 3));
}

void ARogue::RogueWeaponNumberInit(int32 WeaponNumbers) {
	WeaponNumber = WeaponNumbers;
}

bool ARogue::IdleState() {
	if (right == false && forward == false && back == false 
		&& left == false && attack == false && roll == false
		&& NotTakeHitCheck() == true && NotRogueDie() == true && TakeHitOn == false) {
		ViewRotator = 0.f;
		myAnimInst->Idle();
		return true;
	}
	else{
		return false;
	}
}

bool ARogue::NotAttackState() {
	if (myAnimInst->Montage_IsPlaying(myAnimInst->AttackOneMontage) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->AttackTwoMontage) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->AttackThreeMontage) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->TorchAttackMontage) == false) {
		MyGameMode->RogueTorchAttackFinishDelegate.ExecuteIfBound();

		attack = false;
		if (CombatStart == true && AttackFormFinsh == false){
			AttackFormFinsh = true;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("stoping???")));
			GetWorldTimerManager().SetTimer(AttackTimeHandle, this, &ARogue::AttackTimeLimit, 0.5, true);
		}
		return true;
	}
	else {
		attack = true;
		GetWorldTimerManager().ClearTimer(AttackTimeHandle);
		Weaponattack = true;
		return false;
	}
}

bool ARogue::NotAttackCheck() {
	if (myAnimInst->Montage_IsPlaying(myAnimInst->AttackOneMontage) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->AttackTwoMontage) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->AttackThreeMontage) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->TorchAttackMontage) == false) {
		return true;
	}
	else
		return false;
}

void ARogue::AttackTimeLimit() {
	AttackAfterTime++;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("leftdddddddddddddd : %f"), AttackAfterTime));
	if (AttackAfterTime >= 3) {
		AttackFinish();
		GetWorldTimerManager().ClearTimer(AttackTimeHandle);
	}
}

bool ARogue::NotWeaponAttackState() {
	if (myAnimInst->Montage_IsPlaying(myAnimInst->AttackOneMontage) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->AttackTwoMontage) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->AttackThreeMontage) == false) {
		//GetCapsuleComponent()->SetCollisionProfileName("RogueBodyCollision");
		if (CombatStart == true && AttackFormFinsh == true)
			GetWorldTimerManager().SetTimer(AttackTimeHandle, this, &ARogue::AttackTimeLimit, 0.5, true);
		Weaponattack = false;
		return true;
	}
	else {
		attack = true;
		Weaponattack = true;
		return false;
	}
}


bool ARogue::NotTorchAttackState() {
	if (myAnimInst->Montage_IsPlaying(myAnimInst->TorchAttackMontage) == false) {
		Torchattack = false;
		return true;
	}
	else {
		Torchattack = true;
		return false;
	}
}

void ARogue::WeaponChange() {
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("RogueWeaponCheck")));
	//MyGameMode->Call_WeaponChangeDelegate.ExecuteIfBound(GetWeaponNumber());
	//myAnimInst->AttackFormToChangeAnimReferens(GetAttackForm());
	/*if(GetWeaponNumber() == 4)
		RogueWeapons->SetRelativeRotation(FRotator(270, 180, 0));
	else
		RogueWeapons->SetRelativeRotation(FRotator(270, 0, 0));*/
}


bool ARogue::ForwardCheck() {
	if (Canforward == false)
		return false;
	else
		return true;
}

bool ARogue::CanSideCheck() {
	if (CanSide == false)
		return false;
	else
		return true;
}

void ARogue::RogueViewWork() {
	ViewArm->SetRelativeTransform(FTransform(FRotator(90, 0, (-88 + ViewRotator)), FVector(-5, -25, 5), FVector(0, 0, 0)));
	RogueView->SetRelativeTransform(FTransform(FRotator(ViewUp, 0, 0), FVector(0, 0, 0), FVector(0, 0, 0)));
}


void ARogue::RogueMovementValue() {
	NowSpeed = LastInput.Size();
	if (NowSpeed > getSpeed() && Axel == 0) {
		LastInput = (LastInput / NowSpeed) * getSpeed();
	}

	else if (NowSpeed > getSpeed() + Axel && Axel != 0) {
		LastInput = (LastInput / NowSpeed) * (getSpeed() + Axel);
	}
	if (ForwardCheck() == false) {
		if (LastInput.Y >= 0.f)
			LastInput.Y = 0;
	}
	if (myAnimInst->Montage_IsPlaying(myAnimInst->Roll_BackMontage) == true) {
		if (back == true) {
			if (Axel == 0.f) {
				AddMovementInput(GetActorForwardVector(), LastInput.Y * 4);
				AddMovementInput(GetActorRightVector(), LastInput.X * 4);
			}
			else {
				AddMovementInput(GetActorForwardVector(), LastInput.Y * 1.2);
				AddMovementInput(GetActorRightVector(), LastInput.X * 1.2);
			}
		}
	}
	else if (myAnimInst->Montage_IsPlaying(myAnimInst->Roll_Montage) == true) {
		if (right == true)
			LastInput.Y += LastInput.X;
		else if (left == true)
			LastInput.Y -= LastInput.X;
		if (Axel == 0.f) {
			AddMovementInput(GetActorForwardVector(), LastInput.Y * 4);
			//AddMovementInput(GetActorRightVector(), LastInput.X * 3);
		}
		else {
			AddMovementInput(GetActorForwardVector(), LastInput.Y * 1.2);
			//AddMovementInput(GetActorRightVector(), LastInput.X * 1.2);
		}
	}
	
	else {
		if (RollStepQue == 1 || RollStepQue == 3) {
			RollEnd();
		}
		roll = false;
		AddMovementInput(GetActorForwardVector(), LastInput.Y);
		AddMovementInput(GetActorRightVector(), LastInput.X);
	}

	RollRotator = LastInput.Rotation();
	LastInput = FVector(0.f, 0.f, 0.f);
}


void ARogue::AttackFinish() {
	CombatStart = false;
	attack = false;
	AttackQue = 0;
	AttackAfterTime = 0.f;
}

void ARogue::TorchAttack() {
	if(NotAttackState() == true)
		AttackQue = 4;
	Attack();
}

void ARogue::Attack() {
	if (CanInput == true && NotTakeHitCheck() == true && TakeHitOn == false) {
		AttackFowardVectors = GetControlRotation().Vector();
		MyGameMode->RogueAttackVectorToEnemyRogueDelegate.Broadcast(AttackFowardVectors);
		if (AttackQue == 0 && attack == false) {
			CombatStart = true;
		}
		if (NotAttackCheck() == true) {
			MyGameMode->WeaponAttackQueDelegate.ExecuteIfBound(AttackQue);
			myAnimInst->Attack(AttackQue);
			attack = true;
			AttackFormFinsh = false;
			AttackAfterTime = 0;
			if (AttackQue <= 2) {
				AttackQue++;
			}
			if (AttackQue == 3 || AttackQue == 4)
				AttackQue = 0;
		}
	}
}

void ARogue::Forward(float amount) {
	if (CanInput == true) {
		if (amount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false) {
			forward = true;
			back = false;
			LastInput.Y += (amount + Axel);
			if (myAnimInst != nullptr) {
				if (Axel == 0 && right == false && left == false && roll == false) {
					ViewRotator = -3.5f;
					myAnimInst->Walking(right, left, forward, back, roll);
				}
				else if (right == false && left == false && roll == false) {
					ViewRotator = 0.f;
					myAnimInst->Desh(right, left, forward, back, roll);
				}
			}
		}
		else {
			forward = false;
		}
	}
}

void ARogue::Back(float amount) {
	if (CanInput == true) {
		if (amount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false) {
			forward = false;
			back = true;
			LastInput.Y -= (amount + Axel);
			if (myAnimInst != nullptr) {
				if (Axel == 0 && right == false && left == false && roll == false) {
					ViewRotator = -4;
					myAnimInst->Walking(right, left, forward, back, roll);
				}
				else if (right == false && left == false && roll == false) {
					ViewRotator = 0.f;
					myAnimInst->Desh(right, left, forward, back, roll);
				}
			}
		}
		else {
			back = false;
		}
	}
}

void ARogue::Right(float amount) {
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("RIghtdddddddddddddd : %f"), amount));
	if (CanInput == true) {
		if (amount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false) {
			LastInput.X += amount + Axel;
			if (myAnimInst != nullptr) {
				right = true;
				left = false;
				if (Axel == 0)
					myAnimInst->Walking(right, left, forward, back, roll);
				else
					myAnimInst->Desh(right, left, forward, back, roll);
			}
		}
		else {
			right = false;
		}
	}
}

void ARogue::Left(float amount) {
	if (CanInput == true) {
		if (amount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false) {
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("leftdddddddddddddd : %f"), amount));
			ViewRotator = -3.f;
			LastInput.X -= (amount + Axel);
			if (myAnimInst != nullptr) {
				right = false;
				left = true;
				if (Axel == 0)
					myAnimInst->Walking(right, left, forward, back, roll);
				else
					myAnimInst->Desh(right, left, forward, back, roll);
			}
		}
		else {
			left = false;
		}
	}
}

void ARogue::Dash(float Dashamount) {
	if (Dashamount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false) {
		if (Axel < 0.2f)
			Axel += 0.01;
		/*RogueWeapons->AttachToComponent(GetMesh(), 
			FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponBack"));
		if (WeaponBack == false) {
			RogueWeapons->AddRelativeRotation(FRotator(0.f, 90.f, 0));
			WeaponBack = true;
		}*/
	}
	else {
		/*RogueWeapons->AttachToComponent(GetMesh(), 
			FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandFarm"));
		if (WeaponBack == true) {
			RogueWeapons->AddRelativeRotation(FRotator(0.f, -90.f, 0));
			WeaponBack = false;
		}*/
		if (Axel < 0.f) {
			Axel = 0.0f;
		}
		if (Axel >- 0.f)
			Axel -= 0.01;
	}
}

void ARogue::Roll() {
	if (CanInput == true) {
		if (NotAttackState() == true && myAnimInst->Montage_IsPlaying(myAnimInst->Roll_Montage) == false
			&& myAnimInst->Montage_IsPlaying(myAnimInst->Roll_BackMontage) == false && NotTakeHitCheck() == true && TakeHitOn == false) {
			RollStepQue = 1;
			if (myAnimInst != nullptr) {
				RightRotator = GetControlRotation();
				roll = true;
				if (right == false && left == false) {
					TempRollRotatorValue = 0.f;
					if (back == true) {
						RollStepQue = 3;
						myAnimInst->BackStep();
					}
					else
						myAnimInst->Roll();
				}
				else if (right == true || left == true) {
					if(right == true)
						TempRollRotatorValue = 40 - (RollRotator.Yaw) * 0.33;
					else if(left == true)
						TempRollRotatorValue = 33 - (RollRotator.Yaw) * 0.33;
					if (back == true) {
						RollStepQue = 3;
						myAnimInst->BackStep();
					}
					else {
						AddControllerYawInput(TempRollRotatorValue);
						myAnimInst->Roll();
					}
				}
			}
		}
	}
}

void ARogue::RollEnd() {
	roll = false;
	if (RollStepQue == 1)
		AddControllerYawInput(-TempRollRotatorValue);
	RollStepQue = 0;
}

void ARogue::Turn(float amount) {
	if (CanInput == true && NotTakeHitCheck() == true && TakeHitOn == false) {
		if (NotAttackState() == true) {
			if (CanSideCheck() == false) {
				if (RightCapsule == true) {
					if (amount > 0) {
						amount = 0;
						AddControllerYawInput(amount);
					}
					else
						AddControllerYawInput(amount);
				}
				else {
					if (amount < 0) {
						amount = 0;
						AddControllerYawInput(amount);
					}
					else
						AddControllerYawInput(amount);
				}
			}
			else
				AddControllerYawInput(amount);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("MoveVectorValue : %f"), amount));
}

void ARogue::LookUp(float amount) {
	if (CanInput == true && NotTakeHitCheck() == true && TakeHitOn == false) {
		//AddControllerPitchInput(amount);
		if (ViewUp <= -30 && amount < 0) {
			amount = 0;
			ViewUp = -30;
		}
		if (ViewUp >= 80 && amount > 0) {
			amount = 0;
			ViewUp = 80;
		}
		ViewUp += amount;
	}
}

void ARogue::AxisMapping(UPlayerInput* PlayerInputControll) {
	PlayerInputControll->AddAxisMapping(FInputAxisKeyMapping("Forward", EKeys::W, getSpeed()));
	PlayerInputControll->AddAxisMapping(FInputAxisKeyMapping("Back", EKeys::S, getSpeed()));
	PlayerInputControll->AddAxisMapping(FInputAxisKeyMapping("Right", EKeys::D, getSpeed()));
	PlayerInputControll->AddAxisMapping(FInputAxisKeyMapping("Left", EKeys::A, getSpeed()));
	PlayerInputControll->AddAxisMapping(FInputAxisKeyMapping("Dash", EKeys::LeftShift, getSpeed()));

	PlayerInputControll->AddAxisMapping(FInputAxisKeyMapping("Turn", EKeys::MouseX, getTurnSpeed()));
	PlayerInputControll->AddAxisMapping(FInputAxisKeyMapping("LookUp", EKeys::MouseY, getTurnSpeed()));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Roll", EKeys::SpaceBar));

	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("MouseLeft", EKeys::LeftMouseButton));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("MouseRight", EKeys::RightMouseButton));

	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 0", EKeys::Zero));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 1", EKeys::One));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 2", EKeys::Two));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 3", EKeys::Three));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 4", EKeys::Four));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 5", EKeys::Five));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 6", EKeys::Six));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 7", EKeys::Seven));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 8", EKeys::Eight));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 9", EKeys::Nine));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 10", EKeys::Eight, true));

	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 0ctrl", EKeys::Zero,false, true));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 0alt", EKeys::Zero, false, false, true));

	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 1ctrl", EKeys::One, false, true));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 2ctrl", EKeys::Two, false, true));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 3ctrl", EKeys::Three, false, true));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 4ctrl", EKeys::Four, false, true));

	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 1alt", EKeys::One, false, false, true));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 2alt", EKeys::Two, false, false, true));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 3alt", EKeys::Three, false, false, true));
	PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 4alt", EKeys::Four, false, false, true));
	//PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Stat", EKeys::T));

	//PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 1alt", EKeys::One, false, true));
}

void ARogue::BindAxis_func(UInputComponent* PlayerInputComponent) {
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &ARogue::Forward);
	PlayerInputComponent->BindAxis("Back", this, &ARogue::Back);
	PlayerInputComponent->BindAxis("Right", this, &ARogue::Right);
	PlayerInputComponent->BindAxis("Left", this, &ARogue::Left);
	PlayerInputComponent->BindAxis("Dash", this, &ARogue::Dash);

	PlayerInputComponent->BindAxis("Turn", this, &ARogue::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ARogue::LookUp);

	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ARogue::Roll);
	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &ARogue::Attack);
	PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &ARogue::TorchAttack);
	
	PlayerInputComponent->BindAction("Number 0", IE_Pressed, this, &ARogue::SetWeaponNumberToZero);
	PlayerInputComponent->BindAction("Number 1", IE_Pressed, this, &ARogue::SetWeaponNumberToOne);
	PlayerInputComponent->BindAction("Number 2", IE_Pressed, this, &ARogue::SetWeaponNumberToTwo);
	PlayerInputComponent->BindAction("Number 3", IE_Pressed, this, &ARogue::SetWeaponNumberToThree);
	PlayerInputComponent->BindAction("Number 4", IE_Pressed, this, &ARogue::SetWeaponNumberToFour);
	PlayerInputComponent->BindAction("Number 5", IE_Pressed, this, &ARogue::SetWeaponNumberToFive);
	PlayerInputComponent->BindAction("Number 6", IE_Pressed, this, &ARogue::SetWeaponNumberToSix);
	PlayerInputComponent->BindAction("Number 7", IE_Pressed, this, &ARogue::SetWeaponNumberToSeven);
	PlayerInputComponent->BindAction("Number 8", IE_Pressed, this, &ARogue::SetWeaponNumberToEight);
	PlayerInputComponent->BindAction("Number 9", IE_Pressed, this, &ARogue::SetWeaponNumberToNine);
	PlayerInputComponent->BindAction("Number 10", IE_Pressed, this, &ARogue::SetWeaponNumberToTen);

	PlayerInputComponent->BindAction("Number 1ctrl", IE_Pressed, this, &ARogue::setOneTorchElementForm);
	PlayerInputComponent->BindAction("Number 1alt", IE_Pressed, this, &ARogue::setOneWeaponElementForm);
	PlayerInputComponent->BindAction("Number 0ctrl", IE_Pressed, this, &ARogue::setZeroTorchElementForm);
	PlayerInputComponent->BindAction("Number 0alt", IE_Pressed, this, &ARogue::setZeroWeaponElementForm);

	PlayerInputComponent->BindAction("Number 2ctrl", IE_Pressed, this, &ARogue::setTwoTorchElementForm);
	PlayerInputComponent->BindAction("Number 2alt", IE_Pressed, this, &ARogue::setTwoWeaponElementForm);
	PlayerInputComponent->BindAction("Number 3ctrl", IE_Pressed, this, &ARogue::setThreeTorchElementForm);
	PlayerInputComponent->BindAction("Number 3alt", IE_Pressed, this, &ARogue::setThreeWeaponElementForm);

	PlayerInputComponent->BindAction("Number 4ctrl", IE_Pressed, this, &ARogue::setFourTorchElementForm);
	PlayerInputComponent->BindAction("Number 4alt", IE_Pressed, this, &ARogue::setFourWeaponElementForm);
	//PlayerInputComponent->BindAction("Stat", IE_Pressed, this, &ARogue::setFourWeaponElementForm);
}

void ARogue::setZeroTorchElementForm() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	TorchElementForm = 0;
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(0, true);
}

void ARogue::setOneTorchElementForm() { 
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	TorchElementForm = 1; 
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(1, true);
}

void ARogue::setTwoTorchElementForm() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	TorchElementForm = 2;
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(2, true);
}

void ARogue::setThreeTorchElementForm() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	TorchElementForm = 3;
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(3, true);
}

void ARogue::setFourTorchElementForm() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	TorchElementForm = 4;
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(4, true);
}

void ARogue::setZeroWeaponElementForm() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	WeaponElementForm = 0;
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(0, true);
}

void ARogue::setOneWeaponElementForm() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	WeaponElementForm = 1;
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(1, true);
}

void ARogue::setTwoWeaponElementForm() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	WeaponElementForm = 2;
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(2, true);
}

void ARogue::setThreeWeaponElementForm() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	WeaponElementForm = 3;
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(3, true);
}

void ARogue::setFourWeaponElementForm() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("1st_Input"));
	WeaponElementForm = 4;
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(4, true);
}

void ARogue::SetWeaponNumberToZero() {
	WeaponNumber = 0;
	WeaponChange();
}
void ARogue::SetWeaponNumberToOne() {
	WeaponNumber = 1;
	WeaponChange();
}
void ARogue::SetWeaponNumberToTwo() {
	WeaponNumber = 2;
	WeaponChange();
}
void ARogue::SetWeaponNumberToThree() {
	WeaponNumber = 3;
	WeaponChange();
}
void ARogue::SetWeaponNumberToFour() {
	WeaponNumber = 4;
	WeaponChange();
}
void ARogue::SetWeaponNumberToFive() {
	WeaponNumber = 5;
	WeaponChange();
}
void ARogue::SetWeaponNumberToSix() {
	WeaponNumber = 6;
	WeaponChange();
}
void ARogue::SetWeaponNumberToSeven() {
	WeaponNumber = 7;
	WeaponChange();
}
void ARogue::SetWeaponNumberToEight() {
	WeaponNumber = 8;
	WeaponChange();
}
void ARogue::SetWeaponNumberToNine() {
	WeaponNumber = 9;
	WeaponChange();
}

void ARogue::SetWeaponNumberToTen() {
	WeaponNumber = 10;
	WeaponChange();
}

void ARogue::SuperArmorCheck(float PerCent) {
	SuperArmorPer += PerCent;
}

bool ARogue::NotTakeHitCheck() {
	if (myAnimInst->Montage_IsPlaying(myAnimInst->RogueUpHit1) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->RogueUpHit2) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->RogueDownHit1) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->RogueSideAndUpHit1) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->RogueSideAndDownHit1) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->RogueSideHit1) == false)
		return true;
	else
		return false;
}

bool ARogue::NotRogueDie() {
	if (myAnimInst->Montage_IsPlaying(myAnimInst->EnemyDownDeath1[0]) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->EnemyDownDeath2[0]) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->EnemyDownDeath3[0]) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->EnemyUpDeath1[0]) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->EnemyUpDeath2[0]) == false
		&& myAnimInst->Montage_IsPlaying(myAnimInst->EnemyUpDeath3[0]) == false && RogueHp > 0)
		return true;
	else
		return false;
}

void ARogue::EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	int32 HitForm = FMath::RandRange(0, 5);
	AEnemyRogueWeapon* EnemyRogueWeapon = Cast<AEnemyRogueWeapon>(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, FString::Printf(TEXT("RogueHit")));
	ARogueWeapon* HaveRogueWeapon = Cast<ARogueWeapon>(RogueWeapons->GetChildActor());
	
	if (OtherComp->GetCollisionProfileName() == TEXT("EnemyRogueWeaponCollision") && EnemyRogueWeapon->GetTakeHit() == true) {
		TakeHitOn = true;
		GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Yellow, FString::Printf(TEXT("RogueHit")));
		MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(EnemyRogueWeapon->EnemyWeaponDamage*30);
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HaveRogueWeapon->HitEffect, 
			GetActorLocation() + GetActorForwardVector().GetSafeNormal() * FMath::FRandRange(90, 110) +
			GetActorRightVector().GetSafeNormal()*FMath::FRandRange(-20, 20) + FVector(0, 0, FMath::FRandRange(90, 120)),
			FRotator(0, 0, 0), FVector(FMath::FRandRange(1, 1.5), FMath::FRandRange(1, 1.5), FMath::FRandRange(1, 1.5)));
		
		UGameplayStatics::PlaySoundAtLocation(this, TakeHitSoundCue, GetActorLocation());
		if (FMath::FRandRange(0, 100) < SuperArmorPer) {
			SuperArmor = true;
		}
		else
			SuperArmor = false;
		if(MyRogueState->AttackSuccessToSpecialPerPlusCount != 0)
			HaveRogueWeapon->SetTotalElementPer(HaveRogueWeapon->GetDefaultElementPer());
		if (MyRogueState->NoHitToHighAttackSynergyCount != 0)
			HaveRogueWeapon->InitAttackDmgPlusValue();
		if (RogueHp <= 0) {
			GetCapsuleComponent()->SetCollisionProfileName("Death");
			RogueDieState(HitForm);

			GetWorldTimerManager().SetTimer(RogueDieTimeHandle, this, &ARogue::RogueDie, 2, false, 4);
		}
		else if(SuperArmor == false){
			TakeHitState(HitForm);
		}
	}
	if (OtherComp->GetCollisionProfileName() == TEXT("DeathZone")) {
		ADeathZone* DeathZone = Cast<ADeathZone>(OtherActor);
		if (DeathZone->DeathZoneNumber == 1)
			GetWorldTimerManager().SetTimer(RogueDeathZone, this, &ARogue::DeathZoneDamege, 0.5, true);
		else if (DeathZone->DeathZoneNumber == 0)
			DeathZoneDirectDie();
	}
	if (OtherComp->GetCollisionProfileName() == TEXT("DungeonEnd")) {

		MyGameMode->StageIndex = 0;
		MyGameMode->StageSubIndex = 0;
		MyGameMode->WidgetCount = 0;
		MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
		MyGameMode->GetWidgetNumber(-2);
		//ADungeonEnd* DungeonEnd = Cast<ADungeonEnd>(OtherActor);
	}
}

void ARogue::EnterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

}

void ARogue::DeathZoneDamege() {
	MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(50);
	TakeHitState(FMath::RandRange(0, 5));
	if (RogueHp <= 0) {
		RogueDieState(FMath::RandRange(0, 5));
		GetWorldTimerManager().SetTimer(RogueDieTimeHandle, this, &ARogue::RogueDie, 2, false, 4);
		GetCapsuleComponent()->SetCollisionProfileName("Death");
		GetWorldTimerManager().ClearTimer(RogueDeathZone);
	}
}

void ARogue::DeathZoneDirectDie() {
	MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(9999);
	RogueDieState(FMath::RandRange(0, 5));
	GetWorldTimerManager().SetTimer(RogueDieTimeHandle, this, &ARogue::RogueDie, 2, false, 4);
	GetCapsuleComponent()->SetCollisionProfileName("Death");
	GetWorldTimerManager().ClearTimer(RogueDeathZone);
}

void ARogue::RogueDie() {
	MyGameMode->NewGameStart = true;
	MyRogueState->DeleteAbility();
	MyGameMode->GetWidgetNumber(-2);
	GetWorldTimerManager().ClearTimer(RogueDieTimeHandle);
}

void ARogue::TakeHitState(int32 Index) {
	switch (Index) {
	case 0:
		myAnimInst->Montage_Play(myAnimInst->RogueUpHit1);
		break;
	case 1:
		myAnimInst->Montage_Play(myAnimInst->RogueUpHit2);
		break;
	case 2:
		myAnimInst->Montage_Play(myAnimInst->RogueDownHit1);
		break;
	case 3:
		myAnimInst->Montage_Play(myAnimInst->RogueSideAndUpHit1);
		break;
	case 4:
		myAnimInst->Montage_Play(myAnimInst->RogueSideAndDownHit1);
		break;
	case 5:
		myAnimInst->Montage_Play(myAnimInst->RogueSideHit1);
		break;
	}
	TakeHitOn = false;
}

void ARogue::RogueDieState(int32 Index) {
	switch (Index) {
	case 0:
		myAnimInst->Montage_Play(myAnimInst->EnemyDownDeath1[0]);
		break;
	case 1:
		myAnimInst->Montage_Play(myAnimInst->EnemyDownDeath2[0]);
		break;
	case 2:
		myAnimInst->Montage_Play(myAnimInst->EnemyDownDeath3[0]);
		break;
	case 3:
		myAnimInst->Montage_Play(myAnimInst->EnemyUpDeath1[0]);
		break;
	case 4:
		myAnimInst->Montage_Play(myAnimInst->EnemyUpDeath2[0]);
		break;
	case 5:
		myAnimInst->Montage_Play(myAnimInst->EnemyUpDeath3[0]);
		break;
	default:
		myAnimInst->Montage_Play(myAnimInst->EnemyDownDeath1[0]);
		break;
	}
	MyGameMode->Widget_MouseCursorChangedDelegate.ExecuteIfBound(2);
	TakeHitOn = false;
}