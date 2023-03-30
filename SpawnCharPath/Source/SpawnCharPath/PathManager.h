// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PathManager.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNCHARPATH_API UPathManager : public UObject
{
	GENERATED_BODY()
		UPROPERTY()
		TArray<class APathActor*> allPaths;

public:
	void AddPath(APathActor* _path);
	APathActor* GetPath() const;
};
