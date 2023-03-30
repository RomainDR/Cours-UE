// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DemoModeComponentCorr.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLACONCORRECTION_API UDemoModeComponentCorr : public UActorComponent
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDemoAction);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDemoStop);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDemoStart);

	UPROPERTY(BlueprintCallable, BlueprintAssignable, meta = (AllowPrivateAccess))
	FOnDemoAction onDemoAction;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, meta = (AllowPrivateAccess))
		FOnDemoStop onDemoStop;	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, meta = (AllowPrivateAccess))
		FOnDemoStart onDemoStart;

		FTimerHandle demoTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, UIMin = 0, ClampMin = 0))
		float demoRate = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, UIMin = 0, ClampMin = 0, UIMax = 100, ClampMax = 100))
		float demoCallShipRange = 70;

public:	
	UDemoModeComponentCorr();
	FORCEINLINE FOnDemoAction& OnDemoAction() {
		return onDemoAction;
	}
	FORCEINLINE FOnDemoStop& OnDemoStop() {
		return onDemoStop;
	}
	FORCEINLINE FOnDemoStart& OnDemoStart() {
		return onDemoStart;
	}
	void StartDemo();
	UFUNCTION(BlueprintCallable) void StartDemo(const float& _delay);
	UFUNCTION(BlueprintCallable) void StopDemo();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DemoAction();
	UFUNCTION(BlueprintCallable) void RunDemo();
		
};
