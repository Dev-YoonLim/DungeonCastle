// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Trap.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void TrapDown();
	virtual void TrapStart();
	virtual UStaticMeshComponent* GetTriggerMesh() { return TrapTriggerMesh; }
	virtual UStaticMeshComponent* GetPlaceMesh() { return TrapPlaceMesh; }
	virtual UStaticMeshComponent* GetWorkMesh() { return TrapWorkMesh; }
	UFUNCTION()
		void EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void TrapInit();
public:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TrapTriggerMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TrapPlaceMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TrapWorkMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* TrapTriggerBox;
	UPROPERTY(EditAnywhere)
		UBoxComponent* TrapHitBox;
	UPROPERTY(EditAnywhere)
		UParticleSystem* TrapFire;

	FTimerHandle TrapCountDown;



};
