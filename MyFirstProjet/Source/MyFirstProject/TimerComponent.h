// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils.h"
#include "Components/ActorComponent.h"
#include "TimerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTPROJECT_API UTimerComponent : public UActorComponent
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerEnd);

		FOnTimerEnd onTimerEnd;

		UPROPERTY(EditAnywhere, Category = "Timer", meta = (UIMin = 0, ClampMin = 0))
			float maxTimer = 5;


		float timer = 0;

		bool isStarted = false;

public:	
	UTimerComponent();

	FORCEINLINE FOnTimerEnd& OnTimerEnd() { return onTimerEnd; }
	FORCEINLINE void StartTimer() { isStarted = true; LOG_W(LogTemp, "Je démarre le timer"); }
	FORCEINLINE void StopTimer() { isStarted = false; }
	UFUNCTION() void ResetTimer();

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void UpdateTimer(float& _timer, const float& _max);


		
};
