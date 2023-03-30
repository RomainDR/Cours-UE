// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DemoComponent.generated.h"

USTRUCT()
struct FSettingsDemo
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		float timerBeforeLaunch = 5.0f;
	UPROPERTY(EditAnywhere)
		int minMove = 2;
		UPROPERTY(EditAnywhere)
			int maxMove = 10;
		UPROPERTY(EditAnywhere)
			int timeSpaceMove = 2;

	float timer;
	bool isDemo = false;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLACONCORRECTION_API UDemoComponent : public UActorComponent
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		FSettingsDemo settings;

public:	
	UDemoComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void UpdateTimer(float& _timer, float& _maxTimer);

public:
	void ResetTimer();
	bool IsDemoMode();
	void StopDemoMode();
	FORCEINLINE int GetMinMove() const {
		return settings.minMove;
	}
	FORCEINLINE int GetMaxMove() const {
		return settings.maxMove;
	}
	FORCEINLINE float GetTimer() const {
		return settings.timer;
	}
	FORCEINLINE float GetMaxTimer() const {
		return settings.timerBeforeLaunch;
	}
	FORCEINLINE float GetTimerMoveSpace() const {
		return settings.timeSpaceMove;
	}
};
