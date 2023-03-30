// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipDroneActor.h"
#include "SpaceShip.h"
#include "Util.h"

// Sets default values
ASpaceShipDroneActor::ASpaceShipDroneActor()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CREATE(UStaticMeshComponent, "Mesh");
	RootComponent = mesh;

	mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Game/Meshes/Ship/source.source'")));

}

void ASpaceShipDroneActor::BeginPlay()
{
	Super::BeginPlay();

	
}

void ASpaceShipDroneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpaceShipDroneActor::SetInitPosition(ASpaceShip* _pawn)
{
	SetActorLocation(_pawn->GetActorLocation() + positionOffsetByPawn);
}

void ASpaceShipDroneActor::SetTargetPosition(ASpaceShip* _pawn)
{
	SetActorLocation(FMath::Lerp(GetActorLocation(), _pawn->GetActorLocation() + positionOffsetByPawn, DELTATIME * settings.speed));
}

