// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpawnerSettings.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNCHARPATH_API USpawnerSettings : public UDataAsset
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> spawnItem = nullptr;
	UPROPERTY(EditAnywhere, meta = (UIMin = .1f, ClampMin = .1f))
		float timer = 1;
	UPROPERTY(EditAnywhere)
		bool clampSpawnLimit = false;
	UPROPERTY(EditAnywhere, meta = (UIMin = 1, ClampMin = 1, EditCondition = clampSpawnLimit))
		int maxSpawnSize = 10;

public:
	FORCEINLINE float GetMaxTimer() const {
		return timer;
	}
	FORCEINLINE int GetMaxSpawnSize() const {
		return maxSpawnSize;
	}
	FORCEINLINE bool IsClamped() const {
		return clampSpawnLimit;
	}
	FORCEINLINE TSubclassOf<AActor> GetItem() const {
		return spawnItem;
	}
};
