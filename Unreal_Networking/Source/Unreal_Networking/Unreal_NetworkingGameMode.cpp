// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_NetworkingGameMode.h"
#include "Unreal_NetworkingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_NetworkingGameMode::AUnreal_NetworkingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
