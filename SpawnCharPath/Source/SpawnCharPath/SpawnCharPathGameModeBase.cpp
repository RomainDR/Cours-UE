// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpawnCharPathGameModeBase.h"

void ASpawnCharPathGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	pathManager = NewObject<UPathManager>(this);
	pawnSwitcher = GetWorld()->SpawnActor<APawnSwitcher>();
}
