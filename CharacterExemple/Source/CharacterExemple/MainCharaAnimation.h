// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacter.h"

#include "MainCharaAnimation.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTEREXEMPLE_API UMainCharaAnimation : public UAnimInstance
{
	GENERATED_BODY()

		UPROPERTY()
		TObjectPtr<AMainCharacter> mainPawn = nullptr;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
		float speed = 0;

		virtual void NativeBeginPlay() override;
		//virtual void NativeUpdateAnimation(float deltaSeconds) override;
		//float GetSpeed() const;
		UFUNCTION() void SetSpeed(float _speed);
};
