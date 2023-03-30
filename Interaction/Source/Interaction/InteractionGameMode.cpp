// Copyright Epic Games, Inc. All Rights Reserved.

#include "InteractionGameMode.h"
#include "InteractionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInteractionGameMode::AInteractionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
