// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>	
#include "Engine/PointLight.h"
#include "TriggerboxActor.generated.h"

UCLASS()
class INTERACTION_API ATriggerboxActor : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UBoxComponent> trigger = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<APointLight> light = nullptr;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
		float lightIntensity = 500;
	UPROPERTY(EditAnywhere)
		bool interpolationColor = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "interpolationColor"))
		TArray<FColor> colors;



public:
	ATriggerboxActor();

protected:
	virtual void NotifyActorBeginOverlap(AActor* _other) override;
	virtual void NotifyActorEndOverlap(AActor* _other) override;
};
