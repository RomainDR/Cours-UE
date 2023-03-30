// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMovementComponent.h"
#include "Util.h"

UActorMovementComponent::UActorMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UActorMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	settings.initLocation = OWNER->GetActorLocation();
}

void UActorMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateMovement();
	UpdateRotation();
	ResetBehaviour();

	DRAW_BOX(settings.initLocation, FVector(10), COLOR(Cyan), 2);
	DRAW_LINE(OWNER->GetActorLocation(), settings.initLocation, COLOR(Cyan), 2);

	DRAW_SPHERE(OWNER->GetActorLocation() + GetVelocity() * 200, 5, COLOR(Green), 2);
	DRAW_LINE(OWNER->GetActorLocation() + GetVelocity() * 200, GetOwner()->GetActorLocation(), COLOR(Green), 2);
}

void UActorMovementComponent::MoveForward(float _axis)
{
	if (isInResetStatus) return;
	settings.forwardAxis = FMath::Lerp(settings.forwardAxis, _axis, DELTATIME * settings.forwardWeight);
}

void UActorMovementComponent::MoveHorizontal(float _axis)
{
	if (isInResetStatus) return;
	settings.horizontalAxis = FMath::Lerp(settings.horizontalAxis, _axis, DELTATIME * settings.horizontalWeight);
}

void UActorMovementComponent::Rotate(float _axis)
{
	if (isInResetStatus) return;
	settings.rotateAxis = FMath::Lerp(settings.rotateAxis, _axis, DELTATIME * settings.rotateWeight);
}

void UActorMovementComponent::UpdateMovement()
{
	if (isInResetStatus) return;
	OWNER->AddActorWorldOffset(GetVelocity());
}

void UActorMovementComponent::UpdateRotation()
{
	if (isInResetStatus) return;
	OWNER->AddActorLocalRotation(GetRotationVelocity());
}

void UActorMovementComponent::ResetBehaviour()
{
	if (!isInResetStatus) return;
	if (settings.UpdateTimer(WORLD))
	{
		OnEndReset();
		return;
	}
	onResetMovement.Broadcast(settings.GetResetRatio());
	OWNER->SetActorLocation(FMath::Lerp(settings.currentLocation, settings.initLocation, settings.GetResetRatio()));
}

void UActorMovementComponent::CallReset()
{
	if (isInResetStatus) return;
	settings.currentLocation = OWNER->GetActorLocation();
	settings.ResetValues();
	isInResetStatus = true;
}

void UActorMovementComponent::OnEndReset()
{
	isInResetStatus = false;
}

