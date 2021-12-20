// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackRotation.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_AttackRotation::UBTTask_AttackRotation() {
	WaitTime = 10.f;
	RandomDeviation = 0.;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_AttackRotation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	myRogue =
		Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));
	EnemyRogue = Cast<AEnemyRogue>(EnemyController->GetPawn());

	Direction = myRogue->GetActorForwardVector() - EnemyRogue->GetActorForwardVector();
	Direction.Normalize();
	if (EnemyController->CheckDie() == true || EnemyController->CheckHit() == true)
		return EBTNodeResult::Failed;
	
	return EBTNodeResult::InProgress;
}

void UBTTask_AttackRotation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	EnemyController =
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	myRogue =
		Cast<ARogue>(Blackboard->GetValue<UBlackboardKeyType_Object>(EnemyController->RogueKeyID));
	
	EnemyRogue = Cast<AEnemyRogue>(EnemyController->GetPawn());
	
	if (EnemyRogue->EnemyAnimInst->Montage_IsPlaying(EnemyRogue->EnemyAnimInst->EnemyRoll) == false) {
		EnemyRogue->GetCharacterMovement()->MaxWalkSpeed = EnemyRogue->GetSpeedValue() - 20.f;
	}
	/*else if(EnemyRogue->EnemyAnimInst->Montage_IsPlaying(EnemyRogue->EnemyAnimInst->EnemyRoll) == false
		&& (EnemyRogue->EnemyForm <= 6)){
		EnemyRogue->GetCharacterMovement()->MaxWalkSpeed = EnemyRogue->GetSpeedValue() - 20.f;
	}
	else if (EnemyRogue->EnemyAnimInst->Montage_IsPlaying(EnemyRogue->EnemyAnimInst->EnemyRoll) == false
		&& (EnemyRogue->EnemyForm <= 8)) {
		EnemyRogue->GetCharacterMovement()->MaxWalkSpeed = EnemyRogue->GetSpeedValue() - 20.f;
	}*/

	if (EnemyController->CheckAttackState() == false) {
		//EnemyController->SetFocus(myRogue);
		//EnemyController->SetControlRotation(Direction.Rotation());
		EnemyRogue->SetActorRotation(FMath::RInterpTo(
			EnemyRogue->GetActorRotation(), (-(myRogue->GetActorForwardVector())).Rotation(), DeltaSeconds, 4.f));
		if (myRogue->GetActorRotation().Vector() ==
			- (EnemyRogue->GetActorRotation().Vector())) {
			
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}

	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	if (EnemyController->CheckDie() == true || EnemyController->CheckHit() == true)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
}