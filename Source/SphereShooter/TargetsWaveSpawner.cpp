// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/WeakObjectPtrTemplates.h"
#include "Components/ActorComponent.h"
#include "SphereShooterCharacter.h"
#include "TargetsWaveSpawner.h"

// Sets default values for this component's properties
UTargetsWaveSpawner::UTargetsWaveSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTargetsWaveSpawner::BeginPlay()
{
	Super::BeginPlay();

	FVector actorPosition = GetOwner()->GetActorLocation();
	World = GetWorld();

	SpawnWave(actorPosition, TotalTargetsSpawnCount);

}

//event for destroyed target. Invokes next wave if it was a last primary target 
void UTargetsWaveSpawner::OnTargetDestroyed()
{
	ASphereShooterCharacter* character = Cast<ASphereShooterCharacter>(GetOwner());

	if (character->killCount == 10)
	{
		PrepareNextWave();
		character->killCount = 0;
	}
}

//complex logic for wave spawn
void UTargetsWaveSpawner::SpawnWave(FVector center, int targetsCount)
{
	if (TargetSubclass == nullptr || World == nullptr)
	{
		return;
	}

	const FVector CharacterLocation = GetOwner()->GetActorLocation();

	for (int i = 0; i < targetsCount; i++) {

		FVector SpawnLocation;

		do {
			const float xPos = FMath::RandRange(CharacterLocation.X - TargetSpawnRange, CharacterLocation.X + TargetSpawnRange);
			const float yPos = FMath::RandRange(CharacterLocation.Y - TargetSpawnRange, CharacterLocation.Y + TargetSpawnRange);
			const float zPos = CharacterLocation.Z + 50;

			SpawnLocation = FVector(xPos, yPos, zPos);
		} while (!HasEnoughSpaceToSpawnIn(SpawnLocation));

		SpawnLocations.Add(SpawnLocation);

	}

	for (FVector SpawnPoint : SpawnLocations)
	{
		const FRotator Rotation = FRotator::ZeroRotator;
		ATarget* target = World->SpawnActor<ATarget>(TargetSubclass, SpawnPoint, Rotation);

		//this struct separates primary and optional targets
		FTargetType type;
		type.Target = target;
		Targets.Add(type);
	}
}

//check if position is too close to existing targets
bool UTargetsWaveSpawner::HasEnoughSpaceToSpawnIn(FVector Location)
{
	for (FVector SpawnLocation : SpawnLocations)
	{
		float distance = FVector::Distance(SpawnLocation, Location);
		if (distance < MinimalDistanceBetweenTargets)
		{
			return false;
		}
	}

	return true;
}

//clear array, add modification to radius 
void UTargetsWaveSpawner::PrepareNextWave()
{
	for (FTargetType OldTarget : Targets)
	{
		OldTarget.Target->Destroy();
	}

	SpawnLocations.Empty();
	Targets.Empty();

	TargetSpawnRange = (TargetSpawnRange + NewWaveRadiusFactor) + TotalTargetsSpawnCount;
	TotalTargetsSpawnCount = (TotalTargetsSpawnCount * NewWaveTargetCountFactor) + TotalTargetsSpawnCount;

	FVector actorPosition = GetOwner()->GetActorLocation();
	SpawnWave(actorPosition, (int)TotalTargetsSpawnCount);
}

// Called every frame
void UTargetsWaveSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
