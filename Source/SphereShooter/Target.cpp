// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetsWaveSpawner.h" 
#include "SphereShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Target.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.f;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(StaticMeshComp);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//damage dealt 
void ATarget::DamageTarget(float Damage)
{
	Health -= Damage;

	if (Health == 0)
	{
		ASphereShooterCharacter* sphereCharacter = Cast<ASphereShooterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		sphereCharacter->OnTargetDestroyed();

		Destroy();
	}
}
