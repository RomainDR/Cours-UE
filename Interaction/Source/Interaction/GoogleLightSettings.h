// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GoogleLightSettings.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTION_API UGoogleLightSettings : public UDataAsset
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		float maxIntensity = 5000;
	UPROPERTY(EditAnywhere)
		TArray<FLinearColor> allColors;

public:
	FORCEINLINE float MaxIntensity() const {
		return maxIntensity;
	}
	FORCEINLINE int MaxColors() const {
		return allColors.Num();
	}
	FORCEINLINE FLinearColor GetColor(int& _index) const {
		return allColors[_index];
	}

	
};
