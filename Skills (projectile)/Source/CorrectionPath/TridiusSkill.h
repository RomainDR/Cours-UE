// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "TridiusSkill.generated.h"

/**
 * 
 */
UCLASS()
class CORRECTIONPATH_API UTridiusSkill : public USkill
{
	GENERATED_BODY()

public:
	virtual void Spawn(UWorld* _world, const FVector& _origin, const float& _yaw) override;
	
};
