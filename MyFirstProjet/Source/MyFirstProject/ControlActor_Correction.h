// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFirstActor.h"
#include "Utils.h"
#include <Components/BillboardComponent.h>
#include "ControlActor_Correction.generated.h"


UCLASS()
class MYFIRSTPROJECT_API AControlActor_Correction : public AActor
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerReached);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActionParam, bool, _param);

		UPROPERTY(EditAnywhere)
		TObjectPtr<UBillboardComponent> icon = nullptr;

		UPROPERTY(EditAnywhere, Category = Control)
		TObjectPtr<AMyFirstActor> target = nullptr;

	UPROPERTY(EditAnywhere, Category = Timer)
		bool useTimer = true;
	
	UPROPERTY(EditAnywhere, Category = Timer, meta = (EditCondition = "useTime", UIMin = 0, ClampMin = 0))
		float maxTime = 5;

	UPROPERTY(EditAnywhere, Category = Timer, meta = (EditCondition = "useTime"))
		bool isLoopTimer = false;
	UPROPERTY(EditAnywhere, Category = Timer, meta = (EditCondition = "useTime"))
		bool isStarted = true;

	FOnTimerReached onTimerReached;
	FActionParam onActionParam;

	float timer = 0;

public:	
	AControlActor_Correction();
	FORCEINLINE FVector GetTargetLocation() const { return target ? target->GetActorLocation() : GetActorLocation(); }
	FORCEINLINE float GetTimerProgressPercent() const { return (timer / maxTime) * 100.f; }
	FORCEINLINE float GetTimerProgressNormalized() const { return timer / maxTime; }
	FORCEINLINE FOnTimerReached& OnTimerReached() { return onTimerReached; }

private:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void UpdateTimer(float& _timer, const float& _max);
	void DrawDebug();
	UFUNCTION() void TakeControl();
	UFUNCTION() void TestAction();
	UFUNCTION() void TestActionParam(bool _param);

};
