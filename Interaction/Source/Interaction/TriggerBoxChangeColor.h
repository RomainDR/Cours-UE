// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/PointLight.h"
#include <Components/BoxComponent.h>
#include "TriggerBoxChangeColor.generated.h"

UCLASS()
class INTERACTION_API ATriggerBoxChangeColor : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UBoxComponent> trigger = nullptr;
		UPROPERTY(EditAnywhere)
		TArray<FColor> colors;
	UPROPERTY(EditAnywhere)
		TObjectPtr<APointLight> light = nullptr;
	UPROPERTY(EditAnywhere)
		float secondToChange = 5;

	FLinearColor baseColor;
	FTimerHandle timerLight;

	int selectIndexColor = 0;
	
public:	
	ATriggerBoxChangeColor();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyActorBeginOverlap(AActor* _other) override;
	virtual void NotifyActorEndOverlap(AActor* _other) override;

	void ChangeColor();

};
