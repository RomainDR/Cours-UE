// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowPathComponent.h"
#include <Kismet/KismetMathLibrary.h>

UFollowPathComponent::UFollowPathComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UFollowPathComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

void UFollowPathComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!currentPath) return;
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), currentPath->GetActorLocation(), FColor::Blue);
	MoveAlongPath();

}
void UFollowPathComponent::MoveAlongPath()
{
	if (!canFollowPath) return;
	const FVector _next = currentPath->GetNextWaypoint(navIndex);
	DrawDebugLine(GetWorld(), GetOwnerLocation(), _next, FColor::White);
	if (IsAtLocation(_next))
		return;
	const FVector _location = FMath::VInterpConstantTo(GetOwnerLocation(), _next, GetWorld()->DeltaTimeSeconds, moveSpeed);
	GetOwner()->SetActorLocation(_location);
	const FRotator _rotation = UKismetMathLibrary::FindLookAtRotation(GetOwnerLocation(), _next);
	GetOwner()->SetActorRotation(_rotation);
	if (IsAtLocation(_next))
	{
		navIndex++;
		navIndex = navIndex == currentPath->GetWaypointsCount() ? -1 : navIndex;
		if (navIndex < 0)
			GetOwner()->Destroy();
	}

}

void UFollowPathComponent::StartFollow()
{
	canFollowPath = true;
}

void UFollowPathComponent::StopFollow()
{
	canFollowPath = false;
}

void UFollowPathComponent::Init()
{
	UPathManager* _pathManager = GetPathManager();
	if (!_pathManager)return;
	currentPath = _pathManager->GetPath();
}

TObjectPtr<UPathManager> UFollowPathComponent::GetPathManager()
{
	ASpawnCharPathGameModeBase* _gm = GetWorld()->GetAuthGameMode<ASpawnCharPathGameModeBase>();
	if (!_gm)
		return nullptr;
	return _gm->GetPathManager();
}

