// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToGridComponent.h"
#include "Util.h"

UMoveToGridComponent::UMoveToGridComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMoveToGridComponent::BeginPlay()
{
	Super::BeginPlay();	
	Init();
}

void UMoveToGridComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MoveToLocation();
	LookAtDirection();

}

void UMoveToGridComponent::Init()
{
	if (!grid)
		return;
	grid->OnGridLocation().AddDynamic(this, &UMoveToGridComponent::SetLocation);
}

UFUNCTION() void UMoveToGridComponent::SetLocation(FVector _location)
{
	targetLocation = _location + offset;
}

void UMoveToGridComponent::MoveToLocation()
{
	const FVector _lerp = FMath::Lerp(GetOwner()->GetActorLocation(), targetLocation, DELTATIME * 5);
	GetOwner()->SetActorLocation(_lerp);
}

void UMoveToGridComponent::LookAtDirection()
{
	const FRotator _rot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), targetLocation);
	const FRotator _lerp = FMath::Lerp(GetOwner()->GetActorRotation(), _rot, DELTATIME * 5);
	GetOwner()->SetActorRotation(_lerp);
}

