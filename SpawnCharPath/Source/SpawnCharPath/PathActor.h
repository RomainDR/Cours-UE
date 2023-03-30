// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathWaypoint.h"
#include "SpawnCharPathGameModeBase.h"
#include <Components/BillboardComponent.h>
#include "PathActor.generated.h"

UCLASS()
class SPAWNCHARPATH_API APathActor : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr< UBillboardComponent> icon = nullptr;
	UPROPERTY(EditAnywhere)
		TArray<APathWaypoint*> waypoints;
	UPROPERTY(EditAnywhere)
		FColor pathColor = FColor::Green;
	UPROPERTY(EditAnywhere)
		FString pathName = "Path";

	bool isConnected = false;

public:	
	APathActor();
	FORCEINLINE FString GetPathName() const {
		return pathName;
	}
	FORCEINLINE FVector GetNextWaypoint(const int& _index) {
		if (_index < 0 || _index > waypoints.Num() - 1) return GetActorLocation();
		return waypoints[_index] ? waypoints[_index]->GetActorLocation() : GetActorLocation();
	}
	FORCEINLINE int GetWaypointsCount() const {
		return waypoints.Num();
	}
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void DrawPath();
	TObjectPtr<UPathManager> GetPathManager();
};
