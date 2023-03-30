// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Util.h"

#include "GridComponent.generated.h"

USTRUCT()
struct FGridSettings
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
		int row = 0;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
		int column = 0;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
		float axisWeight = 1;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
		float horizontalWeight = 1;

	float targetAxis = 0, targetHorizontal = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLACONCORRECTION_API UGridComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FGridSettings settings;

	UPROPERTY(EditAnywhere)
		TObjectPtr<AActor> target = nullptr;

public:	
	UGridComponent();

	FORCEINLINE FVector GetActorLocation() const {
		return OWNER->GetActorLocation();
	}

	FORCEINLINE FVector GetTargetLocation() const {
		return target->GetActorLocation();
	}
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ShowGrid();
	void MoveToTarget();
	void SetTargetTo();
};