// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowerCorrection.h"
#include "Util.h"

UFollowerCorrection::UFollowerCorrection()
{
	PrimaryComponentTick.bCanEverTick = true;

}
void UFollowerCorrection::BeginPlay()
{
	Super::BeginPlay();
	SetTarget(FPC->GetPawn());
	
}

void UFollowerCorrection::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DRAW_SPHERE(GetTargetLocation(), 50, FColor::Green, 2);
	DRAW_LINE(GetTargetLocation(), GetActorLocation(), FColor::Green, 2);
	DRAW_BOX(GetFinalLocation(), FVector(10), COLOR(Red), 2);
	DRAW_LINE(GetFinalLocation(), GetActorLocation(), FColor::Red, 2);

	FollowTarget();
	ReplicateRoll();
	LookAtTarget();

}

FVector UFollowerCorrection::GetFinalLocation() const
{
	if (!target) return GetTargetLocation();
	FVector _offset;
	switch (settings.axis)
	{
	case X:
		_offset = target->GetActorForwardVector();
		break;

	case Y:
		_offset = target->GetActorRightVector();
		break;

	case InvertX:
		_offset = -target->GetActorForwardVector();
		break;

	case InvertY:
		_offset = -target->GetActorRightVector();
		break;
	}
	return (GetTargetLocation() + _offset * settings.distance) + FVector(0, 0, settings.height);
}

void UFollowerCorrection::FollowTarget()
{
	GetOwner()->SetActorLocation(FMath::Lerp(GetActorLocation(), GetFinalLocation(), DELTATIME * settings.speed));
}

void UFollowerCorrection::ReplicateRoll()
{
	if (!settings.replicateRoll || !target)
		return;
	FRotator _rot = GetOwner()->GetActorRotation();
	_rot.Roll = target->GetActorRotation().Roll;
	GetOwner()->SetActorRotation(_rot);
}

void UFollowerCorrection::LookAtTarget()
{
	if (!settings.useLookAt)
		return;
	GetOwner()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetFinalLocation()));
}

