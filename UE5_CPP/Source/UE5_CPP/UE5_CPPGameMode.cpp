// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_CPPGameMode.h"
#include "UE5_CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5_CPPGameMode::AUE5_CPPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
