// Fill out your copyright notice in the Description page of Project Settings.


#include "InputActor.h"
#include "Utils.h"
#include "InputUtils.h"

// Sets default values
AInputActor::AInputActor()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;

	mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Engine/BasicShapes/Cube.Cube'")));
	mesh->SetMaterial(0, LoadObject<UMaterialInterface>(this, TEXT("'/Engine/BufferVisualization/WorldNormal.WorldNormal'")));
}

void AInputActor::BeginPlay()
{
	Super::BeginPlay();
	initScale = GetActorScale();
	initLocation = GetActorLocation();
	initRotation = GetActorRotation();
	SetupInput();
}

void AInputActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateScale(scaleSpeed);
	DRAW_SPHERE(GetActorLocation() + GetActorForwardVector().GetSafeNormal() * 250, 20, COLOR(Red), 2);
	DRAW_LINE(GetActorLocation() + GetActorForwardVector().GetSafeNormal() * 250, GetActorLocation(), COLOR(Red), 2);

	DRAW_SPHERE(GetActorLocation() + GetActorRightVector().GetSafeNormal() * 250, 20, COLOR(Red), 2);
	DRAW_LINE(GetActorLocation() + GetActorRightVector().GetSafeNormal() * 250, GetActorLocation(), COLOR(Red), 2);

	DRAW_SPHERE(GetActorLocation() + GetActorUpVector().GetSafeNormal() * 250, 20, COLOR(Red), 2);
	DRAW_LINE(GetActorLocation() + GetActorUpVector().GetSafeNormal() * 250, GetActorLocation(), COLOR(Red), 2);

	DRAW_SPHERE(initLocation, 50, COLOR(Cyan), 2);
	DRAW_LINE(initLocation, GetActorLocation(), COLOR(Red), 2);
}

void AInputActor::SetupInput()
{
	BIND_AXIS(HORIZONTAL, this, AInputActor::SetRotation)
		BIND_AXIS(VERTICAL, this, AInputActor::SetVertical)
		BIND_AXIS(ROTATE, this, AInputActor::SetRotation)
		BIND_AXIS(SCALE, this, AInputActor::SetDynamicScale)
		BIND_ACTION(RESPAWN, INPUT(IE_Pressed), this, AInputActor::Respawn);

	//DECLARE_DELEGATE_TwoParams(FInputDelegateCustom, bool, float);
	//BIND_ACTION_PARAMS(FInputDelegateCustom, RESPAWN, INPUT(IE_Pressed), this, AInputActor::Other, true, 1.0f);

}

void AInputActor::SetHorizontal(float _axis)
{
	const FVector _direction = GetActorRightVector().GetSafeNormal() * horizontalSpeed;
	SetActorLocation(GetActorLocation() + (_direction * _axis * DELTATIME));
}
void AInputActor::SetVertical(float _axis)
{
	const FVector _direction = GetActorForwardVector().GetSafeNormal() * horizontalSpeed;
	SetActorLocation(GetActorLocation() + (_direction * _axis * DELTATIME));
}
void AInputActor::SetRotation(float _axis)
{
	AddActorLocalRotation(FRotator(0, rotateSpeed * _axis * DELTATIME, 0));
}
void AInputActor::SetDynamicScale(float _axis)
{
	if (_axis == 0)
		targetScale = initScale;
	else if (_axis > 0)
		targetScale = initScale * 2;
	else if (_axis < 0)
		targetScale = initScale / 2;
}
void AInputActor::UpdateScale(const float& _scaleSpeed)
{
	const FVector _scale = FMath::Lerp(GetActorScale(), targetScale, DELTATIME * _scaleSpeed);
	SetActorScale3D(_scale);
}

void AInputActor::Respawn()
{
	SetActorLocation(initLocation);
	SetActorRotation(initRotation);
}
/*
void AInputActor::Other(bool _value, float _b)
{
}*/