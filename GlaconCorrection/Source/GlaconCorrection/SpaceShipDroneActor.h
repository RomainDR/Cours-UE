// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceShipDroneActor.generated.h"

class ASpaceShip;

USTRUCT()
struct FDroneSettings
{
	GENERATED_BODY()

public:
		UPROPERTY(EditAnywhere)
		float speed = 1.0f;
		UPROPERTY(EditAnywhere)
		float timeBeforeStart = 2.0f;

};
UCLASS()
class GLACONCORRECTION_API ASpaceShipDroneActor : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)
		FVector positionOffsetByPawn = FVector();

	UPROPERTY(EditAnywhere)
		FDroneSettings settings;

	float timer = 0.f;
	bool isStarted = false;
	
public:	
	ASpaceShipDroneActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void StartTimer() {
		timer = 0.f;
		isStarted = true;
	}
	FORCEINLINE void StopTimer() {
		isStarted = false;
	}
	FORCEINLINE float GetTimeBeforeMove() const {
		return settings.timeBeforeStart;
	}

public:
	void SetInitPosition(ASpaceShip* _pawn);
	void SetTargetPosition(ASpaceShip* _pawn);

};
