// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMovement.h"
#include "Utils.h"


ALocalMovement::ALocalMovement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	RootComponent = mesh;

	mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Engine/BasicShapes/Cube.Cube'")));
	mesh->SetMaterial(0, LoadObject<UMaterialInterface>(this, TEXT("'/Engine/BufferVisualization/WorldNormal.WorldNormal'")));
}
void ALocalMovement::BeginPlay()
{
	Super::BeginPlay();
	initScale = GetActorScale();
	onEndTimer.AddDynamic(this, &ALocalMovement::StopMovement);
	onEndTimer.AddDynamic(this, &ALocalMovement::StopRotation);
}
void ALocalMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugAxis();
	Move(GetActorForwardVector(), speed);
	Rotate(FRotator(0, 1, 0), rotateSpeed);
	UpdateTimer(timer);
	BreathOfTheScale(scaleSpeed);

	DRAW_TEXT(GetActorLocation(), FString::Printf(TEXT("%d s /%d s"), (int)timer, (int)maxTimeDelay), COLOR(White), 2);
	const FColor _lerpColor = LERP_COLOR(COLOR(Red), COLOR(Green), GetTimerProgress());
	DRAW_BOX(GetActorLocation() + GetActorUpVector() * 300, FVector(100) * GetTimerProgress(), _lerpColor, 2);
	DRAW_LINE(GetActorLocation(), GetActorLocation() + GetActorUpVector() * 300, COLOR(White), 2);
		
}
void ALocalMovement::DrawDebugAxis()
{
	const FVector _location = GetActorLocation();
	//Forward
	const FVector _forward = GetActorForwardVector().GetSafeNormal();
	DRAW_LINE(_location, _location + _forward * 150, COLOR(Red), 1);
	DRAW_SPHERE(_location + _forward * 150, 20, COLOR(Red), 1);

	//RIGHT
	const FVector _right = GetActorRightVector().GetSafeNormal();
	DRAW_LINE(_location, _location + _right * 150, COLOR(Green), 1);
	DRAW_SPHERE(_location + _right * 150, 20, COLOR(Green), 1);

	//UP
	const FVector _up = GetActorUpVector().GetSafeNormal();
	DRAW_LINE(_location, _location + _up * 150, COLOR(Blue), 1);
	DRAW_SPHERE(_location + _up * 150, 20, COLOR(Blue), 1);
}
void ALocalMovement::Move(const FVector& _direction, const float& _speed)
{
	if (!canMove)
		return;
	AddActorLocalOffset((_direction.GetSafeNormal() * _speed)* DELTATIME);
	//const FVector _next = GetActorLocation() + ((_direction.GetSafeNormal() * _speed) * DELTATIME);
	//SetActorLocation(_next);
}
void ALocalMovement::Rotate(const FRotator& _rotation, const float& _speed)
{
	if (!canRotate)
		return;
	AddActorLocalRotation(_rotation * _speed * DELTATIME);
	//const FRotator _nextRotation = GetActorRotation() + _rotation * _speed * DELTATIME;
	//SetActorRotation(_nextRotation);
}
void ALocalMovement::BreathOfTheScale(const float& _speed)
{
	const float _breathValue = FMath::Sin(WORLD->TimeSeconds * _speed);
	SetActorScale3D(initScale + (initScale * FMath::Abs(_breathValue)));
}
void ALocalMovement::StopMovement()
{
	SetCanMove(false);
}
void ALocalMovement::StopRotation()
{
	SetCanRotate(false);
}
void ALocalMovement::UpdateTimer(float& _timer)
{
	if (!timerStarted)
		return;
	_timer += DELTATIME;
	if(GetEndTimer())
	{ 
		onEndTimer.Broadcast();
		timerStarted = false;
	}
}

