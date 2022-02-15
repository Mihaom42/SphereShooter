// Copyright Epic Games, Inc. All Rights Reserved.

#include "SphereShooterGameMode.h"
#include "SphereShooterHUD.h"
#include "SphereShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASphereShooterGameMode::ASphereShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASphereShooterHUD::StaticClass();
}
