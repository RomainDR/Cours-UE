// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActorCorr.generated.h"

USTRUCT()
struct FGridSettingsCorr
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, meta = (UIMin = 2, ClampMin = 2))
		int size = 4;
	UPROPERTY(EditAnywhere, meta = (UIMin = 1, ClampMin = 1))
		int gap = 100;

	TArray<FVector> gridPoints;
	float minX, maxX, minY, maxY;
};

UCLASS()
class GLACONCORRECTION_API AGridActorCorr : public AActor
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGridGenerated, AGridActorCorr*, _grid);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGridLocation, FVector, _location);
	
	UPROPERTY(EditAnywhere)
		FGridSettingsCorr settings;

	FOnGridGenerated onGridGenerated;
	FOnGridLocation onGridLocation;
	
public:	
	AGridActorCorr();

	FORCEINLINE FOnGridGenerated& OnGridGenerated() {
		return onGridGenerated;
	}FORCEINLINE FOnGridLocation& OnGridLocation() {
		return onGridLocation;
	}
	void SnapToStart(AActor* _toSnap);
	void MoveToCellDirection(AActor* _toMove, const FVector& _direction);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Generate();
	void DrawGrid();

public:
	void PickLocation(AActor* _target);
};
