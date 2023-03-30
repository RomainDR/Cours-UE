// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PathManager.h"
#include "PawnSwitcher.h"
#include "SpawnCharPathGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNCHARPATH_API ASpawnCharPathGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		UPROPERTY()
		TObjectPtr<UPathManager> pathManager = nullptr;
		UPROPERTY()
		TObjectPtr<APawnSwitcher> pawnSwitcher = nullptr;
public:
	FORCEINLINE TObjectPtr<UPathManager> GetPathManager() {
		return pathManager;
	}
	FORCEINLINE TObjectPtr<APawnSwitcher> GetPawnSwitcher() {
		return pawnSwitcher;
	}

private:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
};
