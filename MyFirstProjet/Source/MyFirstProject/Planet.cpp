// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"
#include "Utils.h"

APlanet::APlanet()
{
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	RootComponent = mesh;

	mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Game/Meshes/Planet/EArth/planet.planet'")));
	mesh->SetMaterial(0, LoadObject<UMaterialInterface>(this, TEXT("'/Game/Meshes/Planet/EArth/Material_001_Inst.Material_001_Inst'")));

}

void APlanet::UpdateSize(const FVector& _location)
{
	const float _currentDistance = GetCurrentDistanceTo(_location);
	const float _size = 1 - (_currentDistance / initDistance);
	SetActorScale3D(initScale * (_size < 0 ? 0 : _size));
}

void APlanet::InitPlanet()
{
	const float _randSizeScale = useRandomScale ? FMath::FRandRange(.5f, 3) : 1;
	initScale = GetActorScale() * _randSizeScale;
	SetActorScale3D(initScale);
}

void APlanet::BeginPlay()
{
	Super::BeginPlay();
	InitPlanet();
	
}

