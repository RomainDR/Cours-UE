// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planet.h"
#include "Galaxy.generated.h"

class ASpaceCraft;

UCLASS()
class MYFIRSTPROJECT_API AGalaxy : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = "Planet")
		TArray<APlanet*> allPlanets;
	UPROPERTY()
		TObjectPtr<class ASpaceCraft> currentShip = nullptr;
	
public:	
	AGalaxy();
	void InitGalaxy(ASpaceCraft* _ship);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void DrawDebugGalaxy();
	void UpdatePlanetSize(ASpaceCraft* _ship);

};
