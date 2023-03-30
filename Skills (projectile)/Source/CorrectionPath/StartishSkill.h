// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "StartishSkill.generated.h"

/**
 * 
 */
UCLASS()
class CORRECTIONPATH_API UStartishSkill : public USkill
{
	GENERATED_BODY()
	
public:
	virtual void Spawn(UWorld* _world, const FVector& _origin, const float& _yaw) override;
};
