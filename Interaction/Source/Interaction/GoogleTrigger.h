// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoogleItem.h"
#include <Components/BoxComponent.h>
#include "GoogleTrigger.generated.h"

UCLASS()
class INTERACTION_API AGoogleTrigger : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UBoxComponent> trigger = nullptr;
		UPROPERTY(EditAnywhere)
		TArray<AGoogleItem*> connectedItems;
	
public:	
	AGoogleTrigger();

private:
	virtual void NotifyActorBeginOverlap(AActor* _other) override;
	 virtual void NotifyActorEndOverlap(AActor* _other) override;
	 void Execute();
	 void ResetAll();

};
