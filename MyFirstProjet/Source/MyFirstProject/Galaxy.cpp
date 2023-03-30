// Fill out your copyright notice in the Description page of Project Settings.


#include "Galaxy.h"
#include "SpaceCraft.h"
#include "Utils.h"

// Sets default values
AGalaxy::AGalaxy()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>("Root");

}

void AGalaxy::InitGalaxy(ASpaceCraft* _ship)
{
	//GetWorld()->GetFirstPlayerController()->SetViewTarget(_ship);
	currentShip = _ship;
	for (APlanet* _planet : allPlanets)
	{
		if (!_planet)
			continue;
		_planet->SetInitDistance(_ship->GetActorLocation());
	}
}

void AGalaxy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGalaxy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugGalaxy();
	UpdatePlanetSize(currentShip);

}

void AGalaxy::DrawDebugGalaxy()
{
	if (!currentShip)
		return;

	for (APlanet* _planet : allPlanets)
	{
		if (!_planet)
			continue;
		const FVector _pLoc = _planet->GetActorLocation(), _shipLocation = currentShip->GetActorLocation();
		DRAW_BOX(_pLoc, FVector(100), COLOR(Green), 2);
		DRAW_LINE(_pLoc, GetActorLocation(), COLOR(Green), 2);
		DRAW_LINE(_pLoc, _shipLocation, COLOR(Red), 2);
		DRAW_TEXT(FMath::Lerp(_pLoc, _shipLocation, .5f), 
			FString::Printf(TEXT("%f/%f"), _planet->GetCurrentDistanceTo(_shipLocation), _planet->GetMaxDistance()), 
				COLOR(White), 1.2f);
	}

	DRAW_TEXT(GetActorLocation(), FString::Printf(TEXT("Galaxy center %s"), TO_CHAR_STR(GetActorLocation())), COLOR(White), 1.2f);
	DRAW_BOX(GetActorLocation(), FVector(20), COLOR(Yellow), 2);
}

void AGalaxy::UpdatePlanetSize(ASpaceCraft* _ship)
{
	if (!currentShip)
		return;
	for (APlanet* _planet : allPlanets)
	{
		if (!_planet)
			continue;
		_planet->UpdateSize(_ship->GetActorLocation());
	}
}

