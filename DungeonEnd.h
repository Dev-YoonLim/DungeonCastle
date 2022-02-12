// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Item.h"
#include "DungeonEnd.generated.h"

UCLASS()
class CASTLE_IN_DUNGEON_API ADungeonEnd : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonEnd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable)
		void EnterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere)
		UBoxComponent* EndingBox;

	UPROPERTY(EditAnywhere)
		int32 DungeonNumber;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DungeonFinishMesh;

	UPROPERTY(EditAnywhere)
		UChildActorComponent* EndItem;
};
