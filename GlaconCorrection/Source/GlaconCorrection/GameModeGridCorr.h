// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridActorCorr.h"

#include "GameModeGridCorr.generated.h"

/**
 * 
 */
UCLASS()
class GLACONCORRECTION_API AGameModeGridCorr : public AGameModeBase
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TSoftObjectPtr<AGridActorCorr> grid = nullptr;

public:
	FORCEINLINE TObjectPtr<AGridActorCorr> GetGrid() const
	{
		return grid.Get();
	}
};
