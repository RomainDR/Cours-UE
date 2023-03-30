// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "ArceusSkill.generated.h"

/**
 * 
 */
UCLASS()
class CORRECTIONPATH_API UArceusSkill : public USkill
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		int angleOffset = 90;
		UPROPERTY(EditAnywhere)
		int angleDefinition = 10;

public:
	virtual void Spawn(UWorld* _world, const FVector& _origin, const float& _yaw);
	
};
