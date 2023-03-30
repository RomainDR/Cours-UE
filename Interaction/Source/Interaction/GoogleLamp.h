// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoogleItem.h"
#include "GoogleLightSettings.h"
#include <Components/PointLightComponent.h>
#include "GoogleLamp.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTION_API AGoogleLamp : public AGoogleItem
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UPointLightComponent> light = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr<UGoogleLightSettings> settings;

		int colorIndex = 0;
public:
	AGoogleLamp();
	virtual void Enable() override;
	virtual void Disable() override;
	void SwitchColor();
	
};
