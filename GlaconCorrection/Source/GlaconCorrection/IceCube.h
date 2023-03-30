// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Util.h"
#include "InputUtils.h"
#include "ActorMovementComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "IceCube.generated.h"


USTRUCT()
struct FIceCubeSettings
{
	GENERATED_BODY()
		FVector initSize = FVector(1);
	FVector startScale;

	UPROPERTY(EditAnywhere, meta = (UIMin = 1, ClampMin = 1))
		float divideSizeBy = 3;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
		float meltingTime = 30;
private:
	float currentTime = 0;
public:
	FORCEINLINE float ScaleRatio() const {
		return currentTime / meltingTime;
	}
	FORCEINLINE void UpdateScaleTimer(const UWorld* _world)
	{
		currentTime += _world->DeltaTimeSeconds;
		if (currentTime > meltingTime)
		{
			currentTime = meltingTime;
			return;
		}
	}
	FORCEINLINE FVector TargetSize() const {
		return initSize / divideSizeBy;
	}
	FORCEINLINE  void UpdateScale(AActor* _target){

		_target->SetActorScale3D(FMath::Lerp(initSize, TargetSize(), ScaleRatio()));
	}

	FORCEINLINE void ResetScale(AActor* _target, float _factor) {
		currentTime = 0;
		_target->SetActorScale3D(FMath::Lerp(startScale, initSize, _factor));
	}
};

UCLASS()
class GLACONCORRECTION_API AIceCube : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> springArm = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> camera = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr<UActorMovementComponent> movement = nullptr;
		UPROPERTY(EditAnywhere)
			FIceCubeSettings settings;
	
public:	
	AIceCube();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void InitIceCube();
	void BindInputs();
	void ScaleBehaviour();
	void StartResetIce();
	UFUNCTION() void ResetIceSizeBehaviour(float _scale);

};
