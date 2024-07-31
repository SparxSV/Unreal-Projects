// Copyright Epic Games, Inc. All Rights Reserved.

#include "Mutliplayer_TutorialGameMode.h"
#include "Mutliplayer_TutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMutliplayer_TutorialGameMode::AMutliplayer_TutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
