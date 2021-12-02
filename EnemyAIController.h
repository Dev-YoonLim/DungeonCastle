// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyRogue.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CASTLE_IN_DUNGEON_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	//AI Component 참조
	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;
	AEnemyRogue* EnemyRogue;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AISightRadiusValue)
		float AISightRadius = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AISightAgeValue)
		float AISightAge = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AILoseSightRadiusValue)
		float AILoseSightRadius = AISightRadius + 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIFOWValue)
		float AIFOW = 120.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SightConfigValue)
		class UAISenseConfig_Sight* SightConfig;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SightConfigValue)
		class UAISenseConfig_Touch* TouchConfig;


public:
	AEnemyAIController();
	//virtual void BeginPlay() override;
	//컨트롤러가 Pawn/Character 를 소유할때 호출
	virtual void OnPossess(APawn* InPawn) override;

	FBlackboard::FKey RogueKeyID;
	FBlackboard::FKey EnemyRogueKeyID;
	FBlackboard::FKey PrePosKeyID;
	FBlackboard::FKey NextPosKeyID;
	static const FName PrePosKeyName;
	static const FName NextPosKeyName;
	static const FName NextForm;
	static const FName RollDirection;

public:
	void DoWalk();
	void DoAttack();
	void DoIdle();
	void DoStay();
	void DoConfused();
	void DoSideWalk();
	void DoOrbitingWalk();
	void DoAllAnimStop();
	void DoRoll(int32 RollDirection);

public:
	bool CheckAnyDoing();
	bool CheckHit();
	bool CheckDie();
	bool CheckSense();
	bool CheckAttackState();

public:
	UFUNCTION(BlueprintCallable)	void FindSenseRogue(const TArray<AActor*>& myRogues);
	UFUNCTION(BlueprintCallable)	void FindSenseRogueTarget(AActor* myRogue, FAIStimulus Stimul);

public:
	bool SenseRogue = false;
	bool Confused = false;
	bool Wait = false;
};
