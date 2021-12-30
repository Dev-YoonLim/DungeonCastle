// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SynthComponent.h"
#include "MediaSoundComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "RogueAnimInstance.h"
#include "RogueState.h"
#include "Sound/SoundCue.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Castle_in_DungeonGameModeBase.h"
#include "DeathZone.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSource.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Rogue.generated.h"

//DECLARE_DELEGATE_OneParam(UseWeaponDelegateSignature, int);

UCLASS()
class CASTLE_IN_DUNGEON_API ARogue : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARogue();
	//UseWeaponDelegateSignature UseWeaponNumber;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	UFUNCTION()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
		void EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EnterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//virtual void NotifyActorBeginOverlap(AActor* Others) override;

public:
	void getWorldGameMode();
	void AxisMapping(UPlayerInput*);
	void BindAxis_func(UInputComponent*);

	void Forward(float amount);
	void Back(float amount);
	void Right(float amount);
	void Left(float amount);
	void Dash(float Dashamount);
	void Roll();
	void RollEnd();
	void Attack();
	void TorchAttack();
	void Turn(float amount);
	void LookUp(float amount);

	bool NotAttackState();
	bool NotTorchAttackState();
	bool NotWeaponAttackState();
	bool NotAttackCheck();
	bool NotTakeHitCheck();
	bool NotRogueDie();
	bool IdleState();
	bool AttackState() { return attack; }
	void AttackTimeLimit();
	void RogueDie();

	void RogueWeaponNumberInit(int32 WeaponNumber);
	void RogueWeaponInit();
	void RogueTorchInit();
	void RogueViewInit();
	void RogueMovementInit();
	void RogueStateInit();
	void RogueDialogueInit();
	void DialogueInit();
	//void ChangeDialogueText();

	void RogueViewWork();
	void RogueMovementValue();
	
	void AttackFinish();
	void ForwardStop() { Canforward = false; }
	void ForwardDo() { Canforward = true; }
	void SideStop(bool RightSide) { CanSide = false; RightCapsule = RightSide; }
	void SideDo(bool RightSide) { CanSide = true; RightCapsule = RightSide; }
	bool ForwardCheck();
	bool CanSideCheck();

	void WeaponTorchDelegateInit();
	void WeaponTorchUnDelegate();
	void RogueAbilityDelegateInit();
	void WeaponChange();
	void SuperArmorCheck(float PerCent);

	void RogueCanNotInput(int32 Value);
	void TakeHitState(int32 Index);
	void RogueDieState(int32 Index);

public:
	bool GetCombatState() { return CombatStart; }

	float getSpeed() { return Speed; }
	void SetMultiplySpeed(float NewSpeed);
	void setPlusSpeed(float NewSpeed) { Speed += NewSpeed; }
	void setSpeed(float NewSpeed) { Speed = NewSpeed; }

	float getTurnSpeed() { return TurnSpeed; }
	void setTurnSpeed(float NewTurn) { TurnSpeed = NewTurn; }

	float getAxel() { return Axel; }
	void setAxel(float NewAxel) { Axel = NewAxel; }

	int getAttackQue() { return AttackQue; }
	void setAttackQue(int NewQue) { AttackQue = NewQue; }

	float getAttackAfterTime() { return AttackAfterTime; }
	void setAttackAfterTime(float NewTime) { AttackAfterTime = NewTime; }

	bool getCanHit() { return CanHit; }
	void setCanHit(bool newHitState) { CanHit = newHitState; }


	void SetTorchCanHit(bool NewTorchHitState) { TorchCanHit = NewTorchHitState; }
	bool GetTorchCanHit() { return TorchCanHit; }

	void setAttackForm(int NewForm) { AttackFormSlot = NewForm; }

	void SetWeaponNumberToZero();
	void SetWeaponNumberToOne();
	void SetWeaponNumberToTwo();
	void SetWeaponNumberToThree();
	void SetWeaponNumberToFour();
	void SetWeaponNumberToFive();
	void SetWeaponNumberToSix();
	void SetWeaponNumberToSeven();
	void SetWeaponNumberToEight();
	void SetWeaponNumberToNine();
	void SetWeaponNumberToTen();

	int32 GetAttackForm() { return AttackFormSlot; }
	int32 GetWeaponNumber() { return WeaponNumber; }
	void SetWeaponNumber(int32 WeaponNumbers) { WeaponNumber = WeaponNumbers; }

	void setZeroTorchElementForm();
	void setOneTorchElementForm();
	void setTwoTorchElementForm();
	void setThreeTorchElementForm();
	void setFourTorchElementForm();

	void setZeroWeaponElementForm();
	void setOneWeaponElementForm();
	void setTwoWeaponElementForm();
	void setThreeWeaponElementForm();
	void setFourWeaponElementForm();

	void CheckHp(int32 newHp);
	int32 GetRogueHp() { return RogueHp; }
	void DeathZoneDamege();
	void DeathZoneDirectDie();
	void SetFOV(float NewFOVValue);
	void BeepCall();
	void DialogueVideoPlay();
	void DialgoueVideoCancle();
	void DialogueEventCheck();

	bool GetRogueSettingOn() { return GameSettingOn; }
	//void setZeroWeaponElementForm();
	//void setOneWeaponElementForm();

	UFUNCTION(BlueprintCallable) void FrontDialogueWindow();
	UFUNCTION(BlueprintCallable) void ReturnDialogueWindow();

	bool GetDialogueSequence() { return DialogueSequence; }

	int32 GetStartDialogueIndex() { return StartDialogueIndex; }
	void SetStartDialogueIndex(int32 SetDialogueIndex) { StartDialogueIndex = SetDialogueIndex; }
	
	int32 GetMainDialogueIndex() { return MainDialogueIndex; }
	void SetMainDialogueIndex(int32 SetDialogueIndex) { MainDialogueIndex = SetDialogueIndex; }
	
	int32 GetSubDialogueIndex() { return SubDialogueIndex; }
	void SetSubDialogueIndex(int32 SetDialogueIndex) { SubDialogueIndex = SetDialogueIndex; }

	int32 GetSubDialogueKinds() { return SubDialogueKinds; }
	void SetSubDialogueKinds(int32 SetDialogueKinds) { SubDialogueKinds = SetDialogueKinds; }

	int32 GetDialogueKinds() { return DialogueKinds; }
	void SetDialogueKinds(int32 DialogueKind) { DialogueKinds = DialogueKind; }
	
	void SetHeadShacke(bool Shake);
	void SetRollingTrdCamera(bool Check);
	bool GetRollingTrdCamera() { return RollingTrdCamera; }

private:
	float Axel;
	float Speed;
	float TurnSpeed;
	float NowSpeed;
	float ViewRotator;
	float ViewUp;
	int AttackQue;
	float AttackAfterTime;
	int32 WeaponNumber;//간이용 웨펀넘버
	int32 AttackFormSlot; //간이용 애님넘버
	int32 RogueHp;
	int32 StartDialogueIndex;
	int32 MainDialogueIndex;
	int32 SubDialogueKinds;
	int32 SubDialogueIndex;
	int RollStepQue;
	float TempRollRotatorValue;
	float SuperArmorPer;
	int32 DialogueKinds;

	

	int TorchElementForm;
	int WeaponElementForm;


	bool CombatStart;
	bool right;
	bool left;
	bool forward;
	bool back;
	bool attack;
	bool roll;
	bool desh;
	bool Weaponattack;
	bool Torchattack;
	bool Canforward;
	bool CanSide;
	bool RightCapsule;
	bool CanHit;
	bool TorchCanHit;
	bool SuperArmor;
	bool AttackFormFinsh;
	bool CanInput;
	bool AttackStoping;
	bool WeaponBack = false;
	bool TakeHitOn = false;
	bool OpenDialogueScreen = false;
	bool GameSettingOn = false;
	bool Falling;
	bool DialogueSequence;
	bool RogueHeadShake;
	bool RollingTrdCamera;

public:
	FVector LastInput;
	UAnimInstance* SetRogueAnimInstance;
	URogueAnimInstance* myAnimInst;
	FVector AttackFowardVectors;
	FRotator RightRotator;
	FRotator RollRotator;
	
	FTimerHandle RollTimeHandle;
	FTimerHandle AttackTimeHandle;
	FTimerHandle RogueDieTimeHandle;
	FTimerHandle RogueDeathZone;

	USoundCue* TakeHitSoundCue;

	UPROPERTY(EditAnywhere)
		UMediaSoundComponent* RogueDialogueSound;

	UPROPERTY(EditAnywhere)
		UTextRenderComponent* RogueDialogue;

	UPROPERTY(EditAnyWhere)
		UChildActorComponent* RogueWeapons;

	UPROPERTY(EditAnyWhere)
		UChildActorComponent* RogueTorchs;

	UPROPERTY(EditAnyWhere)
		UCameraComponent* RogueView;

	UPROPERTY(EditAnyWhere)
		USpringArmComponent* ViewArm;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* WindowArm;
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DialogueWindowPlane;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DialogueWindowCase;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent *TorchCapsules;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* ArmCapsules;

	UPROPERTY(EditAnywhere)
		ACastle_in_DungeonGameModeBase* MyGameMode;

	UPROPERTY(EditAnywhere)
		ARogueState* MyRogueState;

	UPROPERTY(EditAnywhere)
		UParticleSystem* HitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIPerceptionStimuliSourceValue)
		class UAIPerceptionStimuliSourceComponent* RoguePerceptionStimuliSource;
	UPROPERTY(EditAnywhere)
		UAudioComponent* BeepSound;
	UPROPERTY(EditAnywhere)
		UAudioComponent* DialogueSound;
	
	UMediaSource* DialogueSource;
	UMediaPlayer* DialoguePlayer;
	UMediaTexture* DialogueTexture;
	UMediaPlaylist* DialogueList;
	bool BeepOn = false;
};
