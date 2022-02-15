// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "Components/SceneComponent.h"
#include "TargetsWaveSpawner.generated.h"

USTRUCT(BlueprintType)
struct FTargetType
{
	GENERATED_BODY()
	
	AActor* Target;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPHERESHOOTER_API UTargetsWaveSpawner : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTargetsWaveSpawner();

protected:
	UPROPERTY()
	UWorld* World;

	UPROPERTY()
	TArray<FTargetType> Targets;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SpawnWave(FVector center, int targetsCount);
	bool HasEnoughSpaceToSpawnIn(FVector position);
	
public:
	UPROPERTY(EditAnywhere, Category = "Target")
		TSubclassOf<AActor> TargetSubclass;

	//max spawn radius from player for optional targets
	UPROPERTY(EditAnywhere, Category = "Target")
		float TargetSpawnRange;

	//total count of all types of targets 
	UPROPERTY(EditAnywhere, Category = "Target")
		float TotalTargetsSpawnCount;

	//multiplier for TargetsSpawnRange. Applies after any new wave. 100% - 1.0
	UPROPERTY(EditAnywhere, Category = "Target")
		float NewWaveRadiusFactor;

	//multiplier for TotalTargetsSpawnCount. Applies after any new wave. 100% - 1.0
	UPROPERTY(EditAnywhere, Category = "Target")
		float NewWaveTargetCountFactor;

	//minimal distance between each spawned target 
	UPROPERTY(EditAnywhere, Category = "Target")
		float MinimalDistanceBetweenTargets;

	//primary targets count. New wave starts after all of these destroyed
	UPROPERTY(EditAnywhere, Category = "Primary Targets")
		float PrimaryTargetsCount;

	//spawn radius from player of primary targets
	UPROPERTY(EditAnywhere, Category = "Primary Targets")
		float PrimaryTargetsSpawnRadius;

	void PrepareNextWave();
	void OnTargetDestroyed();

	//spheres spawn locations
	UPROPERTY()
		TArray<FVector> SpawnLocations;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

