// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridActorCorr.h"

#include "MoveToGridComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLACONCORRECTION_API UMoveToGridComponent : public UActorComponent
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<AGridActorCorr>  grid = nullptr;
	UPROPERTY(EditAnywhere)
		FVector offset = FVector(0, 0, 100);

	FVector targetLocation;

public:	
	UMoveToGridComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init();
	UFUNCTION() void SetLocation(FVector _location);
	void MoveToLocation();
	void LookAtDirection();

		
};
