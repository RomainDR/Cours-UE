// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skill.h"
#include "SkillLauncherComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CORRECTIONPATH_API USkillLauncherComponent : public UActorComponent
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TArray<TObjectPtr<USkill>> skills;

	FTimerHandle spawnTimerTest;

public:	
	USkillLauncherComponent();

protected:
	virtual void BeginPlay() override;
	void InvokeSkill();
		
};
