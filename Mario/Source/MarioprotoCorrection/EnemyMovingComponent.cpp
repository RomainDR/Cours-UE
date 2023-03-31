// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovingComponent.h"

// Sets default values for this component's properties
UEnemyMovingComponent::UEnemyMovingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UEnemyMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

void UEnemyMovingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Move();
	DrawDebugBox(GetWorld(), initLocation, FVector(10), FColor::Red, false, -1, 0, 2);
	DrawDebugBox(GetWorld(), targetLocation, FVector(10), FColor::Green, false, -1, 0, 2);
	DrawDebugLine(GetWorld(), targetLocation, initLocation, FColor::Blue, false, -1, 0, 2);
}

void UEnemyMovingComponent::Move()
{
	if (!canMove) return;
	const FVector _next = FMath::VInterpConstantTo(GetOwnerLocation(), currentLocation, GetWorld()->DeltaTimeSeconds, speed);
	SetOwnerLocation(_next);
	if (IsAtLocation())
	{		
		toTarget = !toTarget;
		currentLocation = toTarget ? targetLocation : initLocation;
	}
}
void UEnemyMovingComponent::Stop()
{
	canMove = false;
}
void UEnemyMovingComponent::Init()
{
	initLocation = GetOwnerLocation();
	targetLocation = initLocation + GetOwner()->GetActorForwardVector() * sizeMovement;
	currentLocation = targetLocation;
}

bool UEnemyMovingComponent::IsAtLocation() const
{
	return FVector::Distance(GetOwnerLocation(), currentLocation) < 10;
}

