// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include <Kismet/KismetMathLibrary.h>

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	icon = CreateDefaultSubobject< UBillboardComponent>("Icon");
	RootComponent = icon;
	spawnLocation = CreateAbstractDefaultSubobject<USceneComponent>("SpawnLocation");
	RootComponent->SetupAttachment(spawnLocation);

}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	onSpawn.AddDynamic(this, &ASpawner::Spawn);
	StartSpawner();
	
}
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugBox(GetWorld(), GetSpawnLocation(), FVector(10), FColor::Green, false, -1, 0, 2);
	DrawDebugLine(GetWorld(), GetSpawnLocation(), GetActorLocation(), FColor::Green, false, -1, 0, 2);
	DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 15, isStarted ? spawnerDebugColor : FColor::Red, false, -1, 0, 2);
	DrawDebugSphere(GetWorld(), GetSpawnLocation() + FVector(0, 0, 50), 10 * GetTimerRatio(), 15, UKismetMathLibrary::LinearColorLerp(FLinearColor::Red, FLinearColor::Green, GetTimerRatio()).ToFColor(true));

}


void ASpawner::StartSpawner()
{
	if (!settings) return;
	GetWorldTimerManager().SetTimer(spawnerTimer, this, &ASpawner::RunSpawner, settings->GetMaxTimer(), true);
	onStartSpawn.Broadcast();
	isStarted = true;
}

void ASpawner::StopSpawner()
{
	GetWorldTimerManager().ClearTimer(spawnerTimer);
	onStopSpawn.Broadcast();
	isStarted = false;

}

void ASpawner::RestartSpawner()
{
	StopSpawner();
	StartSpawner();
}

void ASpawner::RunSpawner()
{
	onSpawn.Broadcast();
}

void ASpawner::Spawn()
{
	if (!settings || !settings->GetItem())
		return;
	GetWorld()->SpawnActor<AActor>(settings->GetItem(), GetSpawnLocation(), FRotator::ZeroRotator);
	spawnCount++;
	if (settings->IsClamped() && spawnCount >= settings->GetMaxSpawnSize())
	{
		StopSpawner();
		return;
	}
}
