// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Touch.h"
#include "RogueAnimInstance.h"
#include "Perception/AIPerceptionComponent.h"

const FName AEnemyAIController::PrePosKeyName(TEXT("PrePos"));
const FName AEnemyAIController::NextPosKeyName(TEXT("NextPos"));
const FName AEnemyAIController::NextForm(TEXT("NextForm"));
const FName AEnemyAIController::RollDirection(TEXT("RollDirection"));

AEnemyAIController::AEnemyAIController() {
	BehaviorComp =
		CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorComp");
	BlackboardComp =
		CreateDefaultSubobject<UBlackboardComponent>("BlackboardComp");

	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_Perception")));
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight_Config"));
	TouchConfig = CreateOptionalDefaultSubobject< UAISenseConfig_Touch>(TEXT("Touch_Config"));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFOW;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->SetDominantSense(*TouchConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->ConfigureSense(*TouchConfig);
	//GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::FindSenseRogue);
}

void AEnemyAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (PerceptionComponent != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("PerceptionCheck"));
		GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::FindSenseRogue);
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::FindSenseRogueTarget);
	}

	EnemyRogue = Cast<AEnemyRogue>(InPawn);

	if (EnemyRogue && EnemyRogue->EnemyBehaviorTree) {
		BlackboardComp->InitializeBlackboard(*EnemyRogue->EnemyBehaviorTree->BlackboardAsset);
		RogueKeyID = BlackboardComp->GetKeyID("RogueKey");
		EnemyRogueKeyID = BlackboardComp->GetKeyID("EnemyRogueKey");
		PrePosKeyID = BlackboardComp->GetKeyID("PrePosKey");
		NextPosKeyID = BlackboardComp->GetKeyID("NextPosKey");
		BehaviorComp->StartTree(*EnemyRogue->EnemyBehaviorTree);
	}
}

bool AEnemyAIController::CheckAnyDoing() {
	if (EnemyRogue->DoAnyThing() == true)
		return true;
	else
		return false;
}

bool AEnemyAIController::CheckHit() {
	if (EnemyRogue->CheckHit() == true)
		return true;
	else
		return false;
}

bool AEnemyAIController::CheckDie() {
	if (EnemyRogue->EnemyDead == true)
		return true;
	else
		return false;
}

bool AEnemyAIController::CheckSense() {
	if (SenseRogue == true)
		return true;
	else
		return false;
}

bool AEnemyAIController::CheckAttackState() {
	if (EnemyRogue->CheckAttack() == true)
		return true;
	else
		return false;

}

void AEnemyAIController::FindSenseRogue(const TArray<AActor*>& myRogues) {
	/*for (int i = 0; i != myRogues.Num(); i++) {
		if (myRogues[i] == GetWorld()->GetFirstPlayerController()->GetPawn()) {
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("FindRogue???"));
			SenseRogue = true;
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("FindRogue???"));
	/*for (int32 Index = 0; Index != Rogue.Num(); Index++) {
		if (Rogue[Index] == GetWorld()->GetFirstPlayerController()->GetPawn()) {
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("FindRogue!!!"));
			SenseRogue = true;
		}
	}*/
}

void AEnemyAIController::FindSenseRogueTarget(AActor* myRogue, FAIStimulus Stimul) {
	ARogue* Rogue = Cast<ARogue>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if ((myRogue == GetWorld()->GetFirstPlayerController()->GetPawn()
		&& Stimul.WasSuccessfullySensed() == true)) {
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, TEXT("FindRogue???"));
		SenseRogue = true;
	}
	/*else {
		if (SenseRogue == true) {
			//DoConfused();
			SightConfig->PeripheralVisionAngleDegrees = 180;
			//Confused = true;
			SenseRogue = false;
		}
		/*else {
			if(EnemyRogue->DoConfused() == false)
				SightConfig->PeripheralVisionAngleDegrees = 120;
		}
	}*/
}

void AEnemyAIController::DoOrbitingWalk() {
	int32 SideDirection = FMath::FRandRange(1, 2);
	EnemyRogue->DoWalk(SideDirection);
}

void AEnemyAIController::DoSideWalk() {
	EnemyRogue->DoWalk(2);
	for (int i = 0; i < 100; i++)
		EnemyRogue->AddMovementInput(EnemyRogue->GetActorRightVector(), 50.f);
}

void AEnemyAIController::DoWalk(){
	EnemyRogue->DoWalk(0);
}

void AEnemyAIController::DoConfused() {
	EnemyRogue->DoConfused();
}

void AEnemyAIController::DoAttack() {
	Wait = false;
	EnemyRogue->DoAttack();
}

void AEnemyAIController::DoIdle() {
	EnemyRogue->DoIdle(EnemyRogue->EnemyForm);
}

void AEnemyAIController::DoAllAnimStop() {
	if (EnemyRogue->EnemyForm <= 6) {
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::Printf(TEXT("NormalStop")));
		EnemyRogue->EnemyAnimInst->Montage_Stop(1.f, EnemyRogue->EnemyAnimInst->EnemyForwardWalk);
	}
	else if (EnemyRogue->EnemyForm <= 8) {
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::Printf(TEXT("CombatStop")));
		EnemyRogue->EnemyAnimInst->Montage_Stop(1.f, EnemyRogue->EnemyAnimInst->EnemyCombatForwardWalk);
	}
	else if (EnemyRogue->EnemyForm <= 10) {
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::Printf(TEXT("SadStop")));
		EnemyRogue->EnemyAnimInst->Montage_Stop(1.f, EnemyRogue->EnemyAnimInst->EnemySadForwardWalk);
	}
	
}

void AEnemyAIController::DoRoll(int32 RollDirections) {
	EnemyRogue->DoRoll(RollDirections);
}