// Fill out your copyright notice in the Description page of Project Settings.


#include "PathWaypoint.h"

// Sets default values
APathWaypoint::APathWaypoint()
{
	PrimaryActorTick.bCanEverTick = true;
	icon = CreateDefaultSubobject< UBillboardComponent>("Icon");
	RootComponent = icon;

}

void APathWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void APathWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(5), FColor::Red, false, -1, 0, 2);
}

