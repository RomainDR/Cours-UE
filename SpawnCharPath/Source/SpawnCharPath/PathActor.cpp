// Fill out your copyright notice in the Description page of Project Settings.


#include "PathActor.h"

// Sets default values
APathActor::APathActor()
{
	PrimaryActorTick.bCanEverTick = true;
	icon = CreateDefaultSubobject< UBillboardComponent>("Icon");
	RootComponent = icon;

}

void APathActor::BeginPlay()
{
	Super::BeginPlay();
	UPathManager* _manager = GetPathManager();
	if (!_manager) return;
	_manager->AddPath(this);
	isConnected = true;
	
}
void APathActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawPath();

}

void APathActor::DrawPath()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), 10, 3, isConnected ? FColor::Green : FColor::Red, false, -1, 0, 2);
	for (size_t i = 0; i < waypoints.Num() - 1; i++)
	{
		if(waypoints[i] && waypoints[i+1])
		DrawDebugLine(GetWorld(), waypoints[i]->GetActorLocation(), waypoints[i + 1]->GetActorLocation(), pathColor, false, -1, 0, 2);
	}
}

TObjectPtr<UPathManager> APathActor::GetPathManager()
{
	ASpawnCharPathGameModeBase* _gm = GetWorld()->GetAuthGameMode<ASpawnCharPathGameModeBase>();
	if (!_gm)
		return nullptr;
	return _gm->GetPathManager();
}

