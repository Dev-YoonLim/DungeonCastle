// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DataTableBase.generated.h"

USTRUCT(BlueprintType)
struct FRogueWeaponDataBase : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		int32 WeaponNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		FString WeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		float HitEffectScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		float WeaponDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		float WeaponSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		float ElementSynergy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		float AttackCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		FVector ElementEffectSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		float FormSynergyX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		float FormSynergyY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RogueWeapon")
		float FormSynergyZ;
	
};

UCLASS()
class CASTLE_IN_DUNGEON_API ADataTableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataTableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
