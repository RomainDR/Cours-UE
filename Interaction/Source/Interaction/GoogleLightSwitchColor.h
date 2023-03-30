// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoogleItem.h"
#include "GoogleLamp.h"
#include <Components/BillboardComponent.h>
#include "GoogleLightSwitchColor.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTION_API AGoogleLightSwitchColor : public AGoogleItem
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UBillboardComponent> icon = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<AGoogleLamp> connectedLamp = nullptr;

	FTimerHandle switchTimer;

public:
	AGoogleLightSwitchColor();
	virtual void Enable() override;
	virtual void Disable() override;
	void Switch();
};
