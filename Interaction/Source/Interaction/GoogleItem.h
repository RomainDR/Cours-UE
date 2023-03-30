// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoogleItem.generated.h"

UCLASS()
class INTERACTION_API AGoogleItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AGoogleItem();

protected:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Enable();
	virtual void Disable();

};
