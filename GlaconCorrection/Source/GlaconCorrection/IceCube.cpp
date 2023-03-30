// Fill out your copyright notice in the Description page of Project Settings.


#include "IceCube.h"

// Sets default values
AIceCube::AIceCube()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CREATE(UStaticMeshComponent, "Mesh");
	camera = CREATE(UCameraComponent, "Camera");
	springArm = CREATE(USpringArmComponent, "SpringArm");
	movement = CREATE(UActorMovementComponent, "Movement");

	RootComponent = mesh;

	mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Engine/BasicShapes/Cube.Cube'")));
	mesh->SetMaterial(0, LoadObject<UMaterialInterface>(this, TEXT("'/Engine/BufferVisualization/WorldNormal.WorldNormal'")));

	ATTACH_TO(springArm, RootComponent);
	ATTACH_TO(camera, springArm);

	AddOwnedComponent(movement);

}

void AIceCube::BeginPlay()
{
	Super::BeginPlay();
	InitIceCube();
	BindInputs();
	
}

void AIceCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	settings.UpdateScaleTimer(WORLD);
	settings.UpdateScale(this);

	DRAW_BOX(GetActorLocation(), settings.TargetSize() * 50, COLOR(Blue), 2);
	DRAW_BOX(GetActorLocation(), settings.initSize * 50, COLOR(Red), 2);

	ScaleBehaviour();

}

void AIceCube::InitIceCube()
{
	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	settings.initSize = GetActorScale();
	if(movement)
	movement->OnResetMovement().AddDynamic(this, &AIceCube::ResetIceSizeBehaviour);
}

void AIceCube::BindInputs()
{
	BIND_AXIS(VERTICAL, movement.Get(), UActorMovementComponent::MoveForward);
	BIND_AXIS(HORIZONTAL, movement.Get(), UActorMovementComponent::MoveHorizontal);
	BIND_AXIS(ROTATE, movement.Get(), UActorMovementComponent::Rotate);
	BIND_ACTION(RESET, EInputEvent::IE_Pressed, movement.Get(), UActorMovementComponent::CallReset);
	BIND_ACTION(RESET, EInputEvent::IE_Pressed, this, AIceCube::StartResetIce);
}

void AIceCube::ScaleBehaviour()
{
	if (!movement)
		return;
	movement->UpdateForwardWeight(1 - settings.ScaleRatio() + .1f);
	movement->UpdateHorizontalWeight(1 - settings.ScaleRatio() + .1f);
	movement->UpdateRotateWeight(1 - settings.ScaleRatio() + .1f);
}

void AIceCube::StartResetIce()
{
	settings.startScale = GetActorScale();
}

UFUNCTION() void AIceCube::ResetIceSizeBehaviour(float _scale)
{
	settings.ResetScale(this, _scale);
}

