// Fill out your copyright notice in the Description page of Project Settings.


#include "GridActorCorr.h"
#include "Util.h"

// Sets default values
AGridActorCorr::AGridActorCorr()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CREATE(USceneComponent, "Root");
}

void AGridActorCorr::SnapToStart(AActor* _toSnap)
{
	if (!_toSnap)
		return;
	_toSnap->SetActorLocation(settings.gridPoints[0]);
}

void AGridActorCorr::MoveToCellDirection(AActor* _toMove, const FVector& _direction)
{
	if (!_toMove)
		return;
	FVector _next = _toMove->GetActorLocation() + _direction * settings.gap;
	_next.X = FMath::Clamp(_next.X, settings.minX, settings.maxX);
	_next.Y = FMath::Clamp(_next.Y, settings.minY, settings.maxY);
	_toMove->SetActorLocation(_next);
}

void AGridActorCorr::BeginPlay()
{
	Super::BeginPlay();
	Generate();
	
}
void AGridActorCorr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawGrid();

}

void AGridActorCorr::Generate()
{
	for (size_t x = 0; x < settings.size; x++)
	{
		for (size_t y = 0; y < settings.size; y++)
		{
			const FVector _point = FVector(x * settings.gap, y * settings.gap, 0) + GetActorLocation();
			settings.gridPoints.Add(_point);
		}
	}
	settings.minY = GetActorLocation().Y;
	settings.maxY = settings.minY + ((settings.size - 1) * settings.gap);
	settings.minX = GetActorLocation().X;
	settings.maxX = settings.minX + ((settings.size - 1) * settings.gap);

	onGridGenerated.Broadcast(this);
}

void AGridActorCorr::DrawGrid()
{
	for (size_t i = 0; i < settings.gridPoints.Num(); i++)
	{
		const FVector _point = settings.gridPoints[i];
		DRAW_BOX(_point, FVector(5), COLOR(Red), 2);
		//DRAW_TEXT(_point + FVector(0, 0, 100), FString::Printf(TEXT("%s"), *_point.ToString()), COLOR(Red), 1.2f);
	}
	//DRAW_TEXT(GetActorLocation() + FVector(0, 0, 150), FString::Printf(TEXT("X: %f\n -X : %f\nY: %f\n -Y : %f\n"), settings.minX, settings.maxX, settings.minY, settings.maxY), COLOR(Red), .8f);
}

void AGridActorCorr::PickLocation(AActor* _target)
{
	onGridLocation.Broadcast(_target->GetActorLocation());
}
