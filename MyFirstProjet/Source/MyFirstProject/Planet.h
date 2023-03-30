// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"

UCLASS()
class MYFIRSTPROJECT_API APlanet : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Planet")
		bool useRandomScale = true;

	UPROPERTY(EditAnywhere, Category = "Planet", meta = (EditCondition = "useRandomScale", UIMin = 2, UIMax = 5, ClampMin = 2, ClampMax = 5))
		int maxSize = 5;

	float initDistance = 1000;
	FVector initScale;


public:
	APlanet();
	FORCEINLINE float GetCurrentDistanceTo(const FVector& _from) { return FVector::Distance(_from, GetActorLocation()); }
	FORCEINLINE float GetMaxDistance() const { return initDistance; }
	FORCEINLINE void SetInitDistance(const FVector& _shipLocation) { initDistance = GetCurrentDistanceTo(_shipLocation); }
	void UpdateSize(const FVector& _location);

protected:
	void InitPlanet();
	virtual void BeginPlay() override;

};
