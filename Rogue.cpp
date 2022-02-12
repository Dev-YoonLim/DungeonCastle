// Fill out your copyright notice in the Description page of Project Settings.


#include "Rogue.h"
#include "EnemyRogue.h"
#include "EnemyRogueWeapon.h"
#include "DialogueZone.h"
#include "RogueWeapon.h"

// Sets default values
ARogue::ARogue()
{
	PrimaryActorTick.bCanEverTick = true;
	RogueStateInit();
	RogueMovementInit();
	RogueViewInit();
	RogueDialogueInit();
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
	BeepSound->Stop();
	DialogueSound->Stop();
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("RogueOn")));
	UPlayerInput* PlayerInputControll = GetWorld()->GetFirstPlayerController()->PlayerInput;
	AxisMapping(PlayerInputControll);
	PostInitializeComponents();
	getWorldGameMode();
	WeaponTorchDelegateInit();
	RogueAbilityDelegateInit();
	WeaponChange();
	SetFOV(100.f);
	//ViewArm->bUsePawnControlRotation = true;
	GameSettingOn = false;
	//ViewArm->SetRelativeTransform(FTransform(FRotator(90, 0, (-88 + ViewRotator)), FVector(-5, -25, 5), FVector(0, 0, 0)));
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
	if (BeepOn == true)
		Axel = 0.f;
	
	/*if (MyRogue->MyRogueState->DialogueTutorialCount < 4 &&
		MyRogue->MyRogueState->TotalEquipCount == MyRogue->MyRogueState->DialogueTutorialCount) {
		MyRogue->SetDialogueIndex((MyRogue->MyRogueState->DialogueTutorialCount) + 3);
		MyRogue->DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL, MyRogue->MyRogueState->FirstDialogueSourceRef[MyRogue->GetDialogueIndex()]));
		MyRogue->MyRogueState->StartDialogueState[(MyRogue->MyRogueState->DialogueTutorialCount) + 3] = 1;
		MyRogue->MyRogueState->DialogueTutorialCount++;
		if (MyRogue->BeepOn == false)
			MyRogue->BeepCall();
	}*/
	//if(OpenDialogueScreen == true)
		//DialogueVideoPlay();
	//DialogueEventCheck();
	
}

void ARogue::DialogueEventCheck() {

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
	MyGameMode->Widget_MouseCursorOnRogueNotInputDelegate.BindUObject(this, &ARogue::RogueCanNotInput);
	MyGameMode->RogueSpeedIncreaseDelegate.BindUObject(this, &ARogue::SetMultiplySpeed);
	MyGameMode->RogueSuperArmorDelegate.BindUObject(this, &ARogue::SuperArmorCheck);
	MyGameMode->Rogue_SpeedValueDelegate.ExecuteIfBound(Speed * 10);
	MyGameMode->Call_RogueFOVDelegate.BindUObject(this, &ARogue::SetFOV);
	MyGameMode->Call_HeadShakeDelegate.BindUObject(this, &ARogue::SetHeadShacke);
	MyGameMode->Call_RollingTrdCameraDelegate.BindUObject(this, &ARogue::SetRollingTrdCamera);
}

void ARogue::BeepCall() {
	if (OpenDialogueScreen == false) {
		MyGameMode->DialogueUICall();
		BeepSound->Play();
		BeepOn = true;
	}
	//else
		//DialogueVideoPlay();
}

void ARogue::FrontDialogueWindow() {
	UMaterial* DialogueMat = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("MaterialInstanceConstant'/Game/Dialogue_Video/DiscMaterial.DiscMaterial'")));
	DialogueWindowPlane->SetMaterial(0, DialogueMat);
	if (OpenDialogueScreen == false && BeepOn == true) {
		MyGameMode->MainUIUpdate();
		WindowArm->SetRelativeRotation(FRotator(100.f, 87.f, 0.f));
		WindowArm->SetRelativeLocation(FVector(-20.f, -20.f, 80.f));
		OpenDialogueScreen = true;
		if (BeepOn == true) {
			BeepSound->Stop();
		}
		//MyGameMode->MainUIUpdate();
		DialogueVideoPlay();
	}
	else {
		BeepOn = false;
		DialogueSequence = false;
		OpenDialogueScreen = false;
		DialoguePlayer->Close();
		DialogueSound->Stop();
		WindowArm->SetRelativeLocation(FVector(-20.f, -20.f, -80.f));
	}
}

void ARogue::DialogueVideoPlay() {
	UMaterial* DialogueMat = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Dialogue_Video/Dialogue_Mat.Dialogue_Mat'")));
	DialogueWindowPlane->SetMaterial(0, DialogueMat);
	USoundBase* DialogueSoundBase;
	if (DialogueKinds == 0) {
		if(MyGameMode->LanguageType == 0)
			DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
				MyRogueState->StartDialogueSourceRef[StartDialogueIndex][0]));
		else if(MyGameMode->LanguageType == 1)
			DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
				MyRogueState->StartDialogueSourceRef[StartDialogueIndex][1]));
		DialogueSoundBase = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), NULL,
			MyRogueState->StartDialogueSourceRef[StartDialogueIndex][2]));
		DialogueSound->SetSound(DialogueSoundBase);
		if (DialoguePlayer->IsPlaying() == false) {
			DialoguePlayer->OpenSource(DialogueSource);
			DialogueSound->Play();
			MyRogueState->StartDialogueState[StartDialogueIndex] = 2;
		}
	}
	else if (DialogueKinds == 1 && MyRogueState->MainDialogueState[MainDialogueIndex] == 0 && MyRogueState->GetCurrentKarma() > MainDialogueIndex*300) {
		if (MyGameMode->LanguageType == 0)
			DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
				MyRogueState->MainStoryDialogueSourceRef[MainDialogueIndex][0]));
		else if (MyGameMode->LanguageType == 1)
			DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
				MyRogueState->MainStoryDialogueSourceRef[MainDialogueIndex][1]));
		DialogueSoundBase = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), NULL,
			MyRogueState->MainStoryDialogueSourceRef[MainDialogueIndex][2]));
		DialogueSound->SetSound(DialogueSoundBase);
		if (DialoguePlayer->IsPlaying() == false) {
			DialoguePlayer->OpenSource(DialogueSource);
			DialogueSound->Play();
			MyRogueState->MainDialogueState[MainDialogueIndex] = 2;
			if(MainDialogueIndex < 4)
				MainDialogueIndex++;
			if (MainDialogueIndex > 4)
				MyRogueState->MainDialogueState[MainDialogueIndex] = 2;
		}
	}
	else if (DialogueKinds == 2 && MyRogueState->SubDialogueState[SubDialogueKinds][SubDialogueIndex] == 0 && MyRogueState->GetRogueAllData() > SubDialogueIndex * 500) {
		if (MyGameMode->LanguageType == 0)
			DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
				MyRogueState->SubStoryDialogueSourceRef[SubDialogueKinds][SubDialogueIndex][0]));
		else if (MyGameMode->LanguageType == 1)
			DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
				MyRogueState->SubStoryDialogueSourceRef[SubDialogueKinds][SubDialogueIndex][1]));
		DialogueSoundBase = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), NULL,
			MyRogueState->SubStoryDialogueSourceRef[SubDialogueKinds][SubDialogueIndex][2]));
		DialogueSound->SetSound(DialogueSoundBase);
		if (DialoguePlayer->IsPlaying() == false) {
			DialoguePlayer->OpenSource(DialogueSource);
			DialogueSound->Play();
			MyRogueState->SubDialogueState[SubDialogueKinds][SubDialogueIndex] = 2;
			if(SubDialogueKinds < 2 && SubDialogueIndex < 4)
				SubDialogueIndex++;
			if (SubDialogueIndex == 4 ) {
				SubDialogueKinds++;
				SubDialogueIndex = 0;
			}
			if (SubDialogueKinds > 1) {
				MyRogueState->SubDialogueState[SubDialogueKinds][SubDialogueIndex] = 2;
			}
		}
	}
		/*if (SubDialogueIndex == 4) {
			SubDialogueKinds++;
			SubDialogueIndex = 0;
		}
		if (MainDialogueIndex != 5) {
			MainDialogueIndex++;
		}*/
}

void ARogue::DialgoueVideoCancle() {
	for (int i = 0; i < 7; i++) {
		MyRogueState->StartDialogueState[i] = 2;
	}
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
	RogueHeadShake = false;
	RogueHp = 300;
	Speed = 0.1f;
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
	setTurnSpeed(0.3f);
	setAttackQue(0);
	setAttackAfterTime(0.f);
	GetCharacterMovement()->MaxWalkSpeed = 1700;
}

void ARogue::RogueDialogueInit() {
	WindowArm = CreateDefaultSubobject<USpringArmComponent>("WindowArm");
	WindowArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, (TEXT("Head")));
	WindowArm->TargetArmLength = 10.f;
	WindowArm->CameraLagSpeed = 15.f;
	WindowArm->CameraRotationLagSpeed = 10.f;
	WindowArm->bEnableCameraLag = true;
	WindowArm->bEnableCameraRotationLag = true;
	WindowArm->SetRelativeRotation(FRotator(100.f, 87.f, 0.f));
	WindowArm->SetRelativeLocation(FVector(-20.f, -20.f, -80.f));
	DialogueWindowPlane = CreateDefaultSubobject<UStaticMeshComponent>("DialogueWindowPlane");
	DialogueWindowPlane->AttachToComponent(WindowArm, FAttachmentTransformRules::KeepRelativeTransform);
	DialogueWindowCase = CreateDefaultSubobject<UStaticMeshComponent>("DialogueWindowCase");
	DialogueWindowCase->AttachToComponent(DialogueWindowPlane, FAttachmentTransformRules::KeepRelativeTransform);
	auto DialogueWindowPlaneAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Dialogue_Video/DialoguePlane.DialoguePlane'"));
	auto DialogueWindowCaseAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Dialogue_Video/DialogueCase.DialogueCase'"));
	if (DialogueWindowCaseAsset.Succeeded())
		DialogueWindowCase->SetStaticMesh(DialogueWindowCaseAsset.Object);
	if (DialogueWindowPlaneAsset.Succeeded())
		DialogueWindowPlane->SetStaticMesh(DialogueWindowPlaneAsset.Object);

	DialogueWindowCase->SetRelativeLocation(FVector(0.f, 30.f, -21.f));
	
	BeepSound = CreateDefaultSubobject<UAudioComponent>("BeepSound");
	auto BeepSoundAsset = ConstructorHelpers::FObjectFinder<USoundBase>
		(TEXT("SoundWave'/Game/Sound/SoundSource/Beep.Beep'"));
	if (BeepSoundAsset.Succeeded()) {
		BeepSound->SetSound(BeepSoundAsset.Object);
	}

	DialogueSound = CreateDefaultSubobject<UAudioComponent>("DialogueSound");
	auto DialogueSoundAsset = ConstructorHelpers::FObjectFinder<USoundBase>
		(TEXT("SoundCue'/Game/Movies/NewDialogue/Tutorial/Audio/GameStart_Cue.GameStart_Cue'"));
	if (DialogueSoundAsset.Succeeded()) {
		DialogueSound->SetSound(DialogueSoundAsset.Object);
	}

	DialoguePlayer = Cast<UMediaPlayer>(StaticLoadObject(UMediaPlayer::StaticClass(), NULL,
		TEXT("MediaPlayer'/Game/Dialogue_Video/DialoguePlayer.DialoguePlayer'")));
}

void ARogue::RogueViewInit() {
	ViewRotator = 0.0f;
	ViewArm = CreateDefaultSubobject<USpringArmComponent>("ViewArm");
	ViewArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, (TEXT("Head")));
	//ViewArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, (TEXT("Head")));
	
	ViewArm->TargetArmLength = 0.f;
	ViewArm->CameraLagSpeed = 3.f;
	ViewArm->CameraRotationLagSpeed = 10.f;
	ViewArm->bEnableCameraLag = true;
	ViewArm->bEnableCameraRotationLag = true;
	ViewArm->AddRelativeRotation(FRotator(90.f, 0, -90.f));
	ViewArm->bUsePawnControlRotation = true;
	RogueView = CreateDefaultSubobject<UCameraComponent>("RogueView");
	RogueView->AttachToComponent(ViewArm, FAttachmentTransformRules::KeepRelativeTransform);
	//RogueView->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, (TEXT("Head")));
	//RogueView->SetFieldOfView(100.f);
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
	if (GetCharacterMovement()->IsFalling() == true && NotRogueDie() == true) {
		myAnimInst->Idle();
		Falling = true;
	}
	else{
		Falling = false;
	}
	//&& NotTakeHitCheck() == true && NotRogueDie() == true && TakeHitOn == false
	if (right == false && forward == false && back == false 
		&& left == false && attack == false && roll == false && NotTakeHitCheck() == true && TakeHitOn == false && NotRogueDie() == true) {
		ViewRotator = 0.f;
		if (RogueHeadShake == false) {
			ViewArm->bUsePawnControlRotation = true;
		}
		else {
			ViewArm->bUsePawnControlRotation = false;
		}
		myAnimInst->Idle();
		return true;
	}
	else{
		return false;
	}
}

void ARogue::SetHeadShacke(bool HeadShake) {
	if (HeadShake == true) {
		RogueHeadShake = true;
		ViewArm->bUsePawnControlRotation = false;
	}
	else {
		RogueHeadShake = false;
		ViewArm->bUsePawnControlRotation = true;
	}
}

void ARogue::SetRollingTrdCamera(bool TrdCamera) {
	RollingTrdCamera = TrdCamera;
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
	MyGameMode->Call_WeaponChangeDelegate.ExecuteIfBound(GetWeaponNumber());
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
	if (myAnimInst->Montage_IsPlaying(myAnimInst->Roll_Montage) == false && myAnimInst->Montage_IsPlaying(myAnimInst->Roll_BackMontage) == false) {
		ViewArm->SetRelativeTransform(FTransform(FRotator(90, 0, (-88 + ViewRotator)), FVector(-5, -15, 10), FVector(0, 0, 0)));
		//ViewArm->SetRelativeRotation(FRotator(90, 0, (-88 + ViewRotator)));
	}
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
				AddMovementInput(GetActorForwardVector(), -0.3f);
				if (right == true)
					AddMovementInput(GetActorRightVector(), 0.3f);
				else if (left == true)
					AddMovementInput(GetActorRightVector(), -0.3f);
			}
			else {
				AddMovementInput(GetActorForwardVector(), -0.4f);
				if (right == true)
					AddMovementInput(GetActorRightVector(), 0.4f);
				else if (left == true)
					AddMovementInput(GetActorRightVector(), 0.4f);
			}
		}
	}
	else if (myAnimInst->Montage_IsPlaying(myAnimInst->Roll_Montage) == true) {
		/*if (right == true)
			//LastInput.Y += LastInput.X;
		else if (left == true)
			//LastInput.Y -= LastInput.X;*/
		if (Axel == 0.f) {
			AddMovementInput(GetActorForwardVector(), 0.3f);
			if (right == true)
				AddMovementInput(GetActorRightVector(), 0.3f);
			else if (left == true)
				AddMovementInput(GetActorRightVector(), -0.3f);
			//AddMovementInput(GetActorRightVector(), LastInput.X * 3);
		}
		else {
			AddMovementInput(GetActorForwardVector(), 0.4f);
			if (right == true)
				AddMovementInput(GetActorRightVector(), 0.4f);
			else if (left == true)
				AddMovementInput(GetActorRightVector(),-0.4f);
			//AddMovementInput(GetActorRightVector(), LastInput.X * 1.2);
		}
	}
	else if (myAnimInst->Montage_IsPlaying(myAnimInst->Dodge_Right) == true) {
		if(Axel == 0.f)
			AddMovementInput(GetActorRightVector(), LastInput.X * 1 + 0.1f);
		else
			AddMovementInput(GetActorRightVector(), LastInput.X * 1);
	}
	else if (myAnimInst->Montage_IsPlaying(myAnimInst->Dodge_Left) == true) {
		if (Axel == 0.f)
			AddMovementInput(GetActorRightVector(), LastInput.X * 1 - 0.1f);
		else
			AddMovementInput(GetActorRightVector(), LastInput.X * 1);
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
		if (RogueHeadShake == false) {
			ViewArm->bUsePawnControlRotation = false;
		}
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
		if (amount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false && Falling == false) {
			forward = true;
			back = false;
			LastInput.Y += (amount + Axel);
			if (myAnimInst != nullptr) {
				if (Axel == 0 && right == false && left == false && roll == false) {
					ViewRotator = -3.5f;
					MyRogueState->SetRogueDeshData(0.03f, -1.f);
					myAnimInst->Walking(right, left, forward, back, roll);
				}
				else if (right == false && left == false && roll == false) {
					ViewRotator = 0.f;
					MyRogueState->SetRogueDeshData(0.1f, 1.f);
					myAnimInst->Desh(right, left, forward, back, roll);
				}
			}
		}
		else if (amount == 0 && roll == false) {
			forward = false;
		}
	}
}

void ARogue::Back(float amount) {
	if (CanInput == true) {
		if (amount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false && Falling == false) {
			forward = false;
			back = true;
			LastInput.Y -= (amount + Axel);
			if (myAnimInst != nullptr) {
				if (Axel == 0 && right == false && left == false && roll == false) {
					ViewRotator = -4;
					MyRogueState->SetRogueDeshData(0.03f, -1.f);
					myAnimInst->Walking(right, left, forward, back, roll);
				}
				else if (right == false && left == false && roll == false) {
					ViewRotator = 0.f;
					MyRogueState->SetRogueDeshData(0.1f, 1.f);
					myAnimInst->Desh(right, left, forward, back, roll);
				}
			}
		}
		else if (amount == 0 && roll == false) {
			back = false;
		}
	}
}

void ARogue::Right(float amount) {
	
	if (CanInput == true) {
		if (amount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false && Falling == false) {
			LastInput.X += amount + Axel;
			if (myAnimInst != nullptr) {
				right = true;
				left = false;
				if (Axel == 0) {
					MyRogueState->SetRogueDeshData(0.03f, -1.f);
					myAnimInst->Walking(right, left, forward, back, roll);
				}
				else {
					MyRogueState->SetRogueDeshData(0.1f, 1.f);
					myAnimInst->Desh(right, left, forward, back, roll);
				}
			}
		}
		else if (amount == 0 && roll == false) {
			right = false;
		}
	}
}

void ARogue::Left(float amount) {
	if (CanInput == true) {
		if (amount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false && Falling == false) {
			
			ViewRotator = -3.f;
			LastInput.X -= (amount + Axel);
			if (myAnimInst != nullptr) {
				right = false;
				left = true;
				if (Axel == 0) {
					MyRogueState->SetRogueDeshData(0.03f, -1.f);
					myAnimInst->Walking(right, left, forward, back, roll);
				}
				else {
					myAnimInst->Desh(right, left, forward, back, roll);
					MyRogueState->SetRogueDeshData(0.1f, 1.f);
				}
			}
		}
		else if (amount == 0 && roll == false) {
			left = false;
		}
	}
}

void ARogue::Dash(float Dashamount) {
	if (Dashamount != 0 && NotAttackState() == true && NotTakeHitCheck() == true && TakeHitOn == false && Falling == false && MyRogueState->GetRogueData() > 0) {
		if (Axel < 0.2f && BeepOn == false)
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
		if (Axel >= 0.f) {
			Axel -= 0.01;
		}
		if (Axel < 0.f) {
			Axel = 0.0f;
		}
	}
}

void ARogue::Roll() {
	if (CanInput == true && Falling == false) {
		if (NotAttackState() == true && myAnimInst->Montage_IsPlaying(myAnimInst->Roll_Montage) == false
			&& myAnimInst->Montage_IsPlaying(myAnimInst->Roll_BackMontage) == false
			&& myAnimInst->Montage_IsPlaying(myAnimInst->Dodge_Right) == false
			&& myAnimInst->Montage_IsPlaying(myAnimInst->Dodge_Left) == false
			&& NotTakeHitCheck() == true && TakeHitOn == false && MyRogueState->GetRogueData() > 9) {
			RollStepQue = 1;
			if (myAnimInst != nullptr) {
				RightRotator = GetControlRotation();
				roll = true;
				if (forward == false && back == false) {
					if (right == true) {
						myAnimInst->RightStep();
					}
					else if (left == true) {
						myAnimInst->LeftStep();
					}
				}
				else {
					if (forward == true) {
						myAnimInst->Roll();
					}
					else if (back == true) {
						RollStepQue = 3;
						myAnimInst->BackStep();
					}
				}
				TempSuperArmorPer = SuperArmorPer;
				SuperArmorPer = 99.f;

				/*if (forward == true) {
					RollStepQue = 1;
					myAnimInst->Roll();
				}
				else if (back == true) {
					RollStepQue = 3;
					myAnimInst->BackStep();
				}
				if (right == false && left == false) {
					TempRollRotatorValue = 0.f;
					if (back == true) {
						RollStepQue = 3;
						myAnimInst->BackStep();
					}
					else if (forward == true)
						RollStepQue = 1;
						myAnimInst->Roll();
					else
						
				}
				else if (right == true) {
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
				else if (left == true) {
					if (back == true) {
						RollStepQue = 3;
						myAnimInst->BackStep();
					}
					else {
						AddControllerYawInput(TempRollRotatorValue);
						myAnimInst->Roll();
					}
				}*/
				if (RollingTrdCamera == true) {
					ViewArm->bUsePawnControlRotation = true;
					ViewArm->ResetRelativeTransform();
					ViewArm->SetRelativeRotation(FRotator(90, 0, (-88 + ViewRotator)));
					//ViewArm->TargetArmLength = 50.f;
				}
			}
		}
	}
}

void ARogue::RollEnd() {
	roll = false;
	/*if (RollStepQue == 1)
		AddControllerYawInput(-TempRollRotatorValue);*/
	RollStepQue = 0;
	if (RollingTrdCamera == true) {
		if(RogueHeadShake == true)
			ViewArm->bUsePawnControlRotation = false;
		else
			ViewArm->bUsePawnControlRotation = true;
		ViewArm->TargetArmLength = 0.f;
	}
	SuperArmorPer = TempSuperArmorPer;
	TempSuperArmorPer = 0.f;
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

	/*PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 0", EKeys::Zero));
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

	//PlayerInputControll->AddActionMapping(FInputActionKeyMapping("Number 1alt", EKeys::One, false, true));*/
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
	
	/*PlayerInputComponent->BindAction("Number 0", IE_Pressed, this, &ARogue::SetWeaponNumberToZero);
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
	//PlayerInputComponent->BindAction("Stat", IE_Pressed, this, &ARogue::setFourWeaponElementForm);*/
}

void ARogue::setZeroTorchElementForm() {
	
	TorchElementForm = 0;
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(0, true);
}

void ARogue::setOneTorchElementForm() { 
	
	TorchElementForm = 1; 
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(1, true);
}

void ARogue::setTwoTorchElementForm() {
	
	TorchElementForm = 2;
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(2, true);
}

void ARogue::setThreeTorchElementForm() {
	
	TorchElementForm = 3;
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(3, true);
}

void ARogue::setFourTorchElementForm() {
	
	TorchElementForm = 4;
	MyGameMode->TorchElementChangeDelegate.ExecuteIfBound(4, true);
}

void ARogue::setZeroWeaponElementForm() {
	
	WeaponElementForm = 0;
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(0, true);
}

void ARogue::setOneWeaponElementForm() {
	
	WeaponElementForm = 1;
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(1, true);
}

void ARogue::setTwoWeaponElementForm() {
	
	WeaponElementForm = 2;
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(2, true);
}

void ARogue::setThreeWeaponElementForm() {
	
	WeaponElementForm = 3;
	MyGameMode->WeaponElementChangeDelegate.ExecuteIfBound(3, true);
}

void ARogue::setFourWeaponElementForm() {
	
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
//&& RogueHp > 0
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
		if (FMath::FRandRange(0, 100) < SuperArmorPer) {
			MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(EnemyRogueWeapon->EnemyWeaponDamage * FMath::RandRange(20, 26));
			SuperArmor = true;
		}
		else {
			MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(EnemyRogueWeapon->EnemyWeaponDamage * FMath::RandRange(25,32));
			SuperArmor = false;
		}
		GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Yellow, FString::Printf(TEXT("RogueHit")));
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HaveRogueWeapon->HitEffect, 
			GetActorLocation() + GetActorForwardVector().GetSafeNormal() * FMath::FRandRange(90, 110) +
			GetActorRightVector().GetSafeNormal()*FMath::FRandRange(-20, 20) + FVector(0, 0, FMath::FRandRange(90, 120)),
			FRotator(0, 0, 0), FVector(FMath::FRandRange(1, 1.5), FMath::FRandRange(1, 1.5), FMath::FRandRange(1, 1.5)));
		
		UGameplayStatics::PlaySoundAtLocation(this, TakeHitSoundCue, GetActorLocation());
		if(MyRogueState->AttackSuccessToSpecialPerPlusCount != 0)
			HaveRogueWeapon->SetTotalElementPer(HaveRogueWeapon->GetDefaultElementPer());
		if (MyRogueState->NoHitToHighAttackSynergyCount != 0)
			HaveRogueWeapon->InitAttackDmgPlusValue();
		if (RogueHp <= 0) {
			GetCapsuleComponent()->SetCollisionProfileName("Death");
			RogueDieState(HitForm);

			GetWorldTimerManager().SetTimer(RogueDieTimeHandle, this, &ARogue::RogueDie, 2, false, 4);
		}
		else {
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
		MyRogueState->SetSaveState(true);
		if (DialogueKinds != 1) {
			DialogueKinds = 1;
		}
		if(MyRogueState->GetCurrentKarma() > MainDialogueIndex * 300){
			if (MyRogueState->GetDungeonClearAllCount() >= 1) {
				MainDialogueIndex++;
			}
		}
		/*if (MyRogueState->GetRogueAllData() > SubDialogueIndex * 500) {
			SubDialogueIndex++;
		}
		if (SubDialogueIndex == 4) {
			SubDialogueKinds++;
			SubDialogueIndex = 0;
		}*/
		MyRogueState->PlusDungeonClearCount(MyGameMode->StageIndex);

		MyGameMode->StageIndex = 0;
		MyGameMode->StageSubIndex = 0;
		MyGameMode->WidgetCount = 0;
		MyGameMode->Call_GameSaveDelegate.ExecuteIfBound();
		MyGameMode->GetWidgetNumber(-2);
		//ADungeonEnd* DungeonEnd = Cast<ADungeonEnd>(OtherActor);
	}
	if (OtherComp->GetCollisionProfileName() == TEXT("DialogueEvent")) {
		//MyRogueState->DialogueRefInit();
		ADialogueZone* DialogueZone = Cast<ADialogueZone>(OtherActor);
		DialogueKinds = DialogueZone->DialogueKindsNumber;
		if (DialogueKinds == 0) {
			StartDialogueIndex = DialogueZone->DialogueZoneNumber;
			if (StartDialogueIndex < 7) {
				if (MyRogueState->StartDialogueState[StartDialogueIndex] == 0 && DialogueZone->DialogueCount == 1) {
					//DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
						//MyRogueState->StartDialogueSourceRef[StartDialogueIndex]));
					DialogueSequence = true;
					MyRogueState->StartDialogueState[StartDialogueIndex] = 1;
					if (StartDialogueIndex == 2 || StartDialogueIndex == 3)
						MyRogueState->TaskLevel = StartDialogueIndex-1;
					//DialogueKinds = 0;
					DialogueZone->DialogueCount--;
					BeepCall();
				}
			}
		}
		else if (DialogueKinds == 1) {
			//DialogueKinds = DialogueZone->DialogueKindsNumber;
			//MainDialogueIndex = DialogueZone->DialogueZoneNumber;
			if (MyRogueState->MainDialogueState[MainDialogueIndex] == 0 && MyRogueState->GetCurrentKarma() > MainDialogueIndex * 500 && DialogueZone->DialogueCount == 1) {
				//MyRogueState->SetCurrentKarma(100);
				if (MainDialogueIndex <= 3 && MyRogueState->GetDungeonClearAllCount() >= 1 && MyRogueState->GetDungeonClearAllCount() <= 3) {
					//MainDialogueIndex++;
					/*DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
						MyRogueState->MainStoryDialogueSourceRef[MainDialogueIndex][0]));
					DialogueSequence = true;
					MyRogueState->MainDialogueState[MainDialogueIndex] = 1;*/
					DialogueZone->DialogueCount--;
					BeepCall();
				}
			}
		}
		else if (DialogueKinds == 2) {
			//DialogueKinds = DialogueZone->DialogueKindsNumber;
			//SubDialogueIndex = DialogueZone->DialogueZoneNumber;
			if (MyRogueState->SubDialogueState[SubDialogueKinds][SubDialogueIndex] == 0 && MyRogueState->GetRogueAllData() > SubDialogueIndex * 700 && DialogueZone->DialogueCount == 1) {
				/*DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
					MyRogueState->SubStoryDialogueSourceRef[SubDialogueKinds][SubDialogueIndex][0]));
				DialogueSequence = true;
				MyRogueState->SubDialogueState[SubDialogueKinds][SubDialogueIndex] = 1;
				//DialogueKinds = 2;
				SubDialogueIndex++;
				if (SubDialogueIndex == 4) {
					SubDialogueKinds++;
					SubDialogueIndex = 0;
				}*/
				DialogueZone->DialogueCount--;
				BeepCall();
			}
		}
		
		/*if (MyRogueState->StartDialogueState[DialogueZone->DialogueZoneNumber] == 0) {
			MyRogueState->StartDialogueState[DialogueZone->DialogueZoneNumber] = 1;
			BeepCall();
		}*/
	}
}

void ARogue::EnterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherComp->GetCollisionProfileName() == TEXT("LoadData")) {
		if (MyGameMode->GameSettingOn == false) {
			MyGameMode->GameSettingOn = true;
			MyGameMode->GetWidgetNumber(1);
			MyRogueState->MoveSpeedIncreaseCountValue = 1.f;
			SetMultiplySpeed(0.1f);
			MyRogueState->RogueDataInit();
			MyRogueState->GameSettingSaveInit();
			MyRogueState->Call_RogueStartWeaponNumber();
			MyRogueState->Call_RogueStartAttackFormNumber();
			MyRogueState->Call_RogueStartTorchElementalNumber();
			MyRogueState->LastSpeedSetting();
			MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(0);
			//SetMultiplySpeed((MyRogueState->MoveSpeedIncreaseCountValue)*0.1f);
			//MyGameMode->RogueSpeedIncreaseDelegate.ExecuteIfBound(0.1 * MoveSpeedIncreaseCountValue);
			SetFOV(MyGameMode->FOVValue);
			GameLoad = true;
			
			if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == TEXT("Stage0")) {
				GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("GetDungeonClears : %d"), MyRogueState->GetDungeonClearAllCount()));
				//if (MyRogueState->StartDialogueState[0] == 0) {
					//StartDialogueIndex = 0;
				//}
				if (MyRogueState->GetDungeonClearAllCount() == 0 && MyRogueState->StartDialogueState[0] == 0) {
					//DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
						//MyRogueState->StartDialogueSourceRef[StartDialogueIndex]));
					MyRogueState->TaskLevel = 0;
					GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("StartDialogue")));
					BeepCall();
				}
				else if (MyRogueState->GetDungeonClearAllCount() >= 1 && MyRogueState->GetCurrentKarma() > MainDialogueIndex * 300 
					&& MyRogueState->MainDialogueState[MainDialogueIndex] == 0) {
					DialogueKinds = 1;
					DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
						MyRogueState->MainStoryDialogueSourceRef[MainDialogueIndex][0]));
					if (MyRogueState->GetDungeonClearAllCount() < 3)
						MyRogueState->TaskLevel = 9;
					else
						MyRogueState->TaskLevel = 10;
					GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("MainDialogue : %d"), MainDialogueIndex));
					BeepCall();
				}
			}
			else if(UGameplayStatics::GetCurrentLevelName(GetWorld()) != TEXT("StartMap_2")){
				GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("SubDialogue : %d"), MyRogueState->SubStoryDialogueSourceRef[SubDialogueKinds][SubDialogueIndex][0]));
				MyRogueState->TaskLevel = MyGameMode->StageIndex + 5;
				if (SubDialogueIndex == 4) {
					SubDialogueKinds++;
					SubDialogueIndex = 0;
				}
				if (MyRogueState->GetRogueAllData() > SubDialogueIndex * 500
					&& MyRogueState->SubDialogueState[SubDialogueKinds][SubDialogueIndex] == 0) {
					DialogueKinds = 2;
					DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL,
						MyRogueState->SubStoryDialogueSourceRef[SubDialogueKinds][SubDialogueIndex][0]));
					BeepCall();
				}
			}
		}
	}
	else if (OtherComp->GetCollisionProfileName() == TEXT("BonFire")) {
		if (MyRogueState->DialogueTutorialCount < 4 &&
			MyRogueState->TotalEquipCount == MyRogueState->DialogueTutorialCount && DialogueKinds == 0) {
			SetStartDialogueIndex((MyRogueState->DialogueTutorialCount) + 3);
			//DialogueSource = Cast<UMediaSource>(StaticLoadObject(UMediaSource::StaticClass(), NULL, MyRogueState->StartDialogueSourceRef[GetStartDialogueIndex()]));
			MyRogueState->StartDialogueState[(MyRogueState->DialogueTutorialCount) + 3] = 1;
			MyRogueState->DialogueTutorialCount++;
			MyRogueState->TaskLevel = 0;
			if (BeepOn == false) {
				BeepCall();
			}
		}
	}
}

void ARogue::DeathZoneDamege() {
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("DeathZones1")));
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
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Red, FString::Printf(TEXT("DeathZones2")));
	MyGameMode->Call_RogueDamageDelegate.ExecuteIfBound(9999);
	RogueDieState(FMath::RandRange(0, 5));
	GetWorldTimerManager().SetTimer(RogueDieTimeHandle, this, &ARogue::RogueDie, 2, false, 4);
	GetCapsuleComponent()->SetCollisionProfileName("Death");
	GetWorldTimerManager().ClearTimer(RogueDeathZone);
}

void ARogue::RogueDie() {
	MyRogueState->setRogueDeath(1);
	MyGameMode->NewGameStart = true;
	MyRogueState->SetSaveState(true);
	MyRogueState->DeleteAbility();
	MyGameMode->GetWidgetNumber(-2);
	GetWorldTimerManager().ClearTimer(RogueDieTimeHandle);
}

void ARogue::TakeHitState(int32 Index) {
	if (RogueHeadShake == false) {
		ViewArm->bUsePawnControlRotation = false;
	}
	if (SuperArmor == false) {
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
	}
	TakeHitOn = false;
}

void ARogue::RogueDieState(int32 Index) {
	if (RogueHeadShake == false) {
		ViewArm->bUsePawnControlRotation = false;
	}
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