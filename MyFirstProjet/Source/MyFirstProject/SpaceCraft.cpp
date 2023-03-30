// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceCraft.h"
#include "InputUtils.h"
#include "Utils.h"

ASpaceCraft::ASpaceCraft()
{
	PrimaryActorTick.bCanEverTick = true;
	shipMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	shipMesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Game/Meshes/Spaceship/source.source'")));
	shipMesh->SetMaterial(0, LoadObject<UMaterialInterface>(this, TEXT("'/Game/Meshes/Spaceship/Instance.Instance'")));

	RootComponent = shipMesh;
	springArm = CreateDefaultSubobject<USpringArmComponent>("CameraAnchor");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	//
	customTimer = CreateDefaultSubobject<UTimerComponent>("Timer");
	AddOwnedComponent(customTimer);
}
void ASpaceCraft::BeginPlay()
{
	Super::BeginPlay();
	InitShip();
}
void ASpaceCraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddFloatingBehaviour();
	DRAW_LINE(GetActorLocation() + shipVelocity * 100, GetActorLocation(), FColor::Cyan, 2);
	DRAW_SPHERE(GetActorLocation() + shipVelocity * 100, 10, FColor::Cyan, 2);
	RotateAroundCamera();
	ResetCameraRotation();
	}
void ASpaceCraft::InitShip()
{
	InitInput();
	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	if (!currentGalaxy) {
		LOG_E(LogTemp, "Ta pas de galaxy sale bouffon");
		return;
	}
	currentGalaxy->InitGalaxy(this);
	if (customTimer)
	{
		BIND(customTimer->OnTimerEnd(), this, ASpaceCraft::PassiveModeEnable);
		customTimer->StartTimer();
	}
	if (springArm)
		initRotation = springArm->GetRelativeRotation();
	BIND(onShipMovement, this, ASpaceCraft::MovingDetection);
	BIND(onShipAxis, this, ASpaceCraft::PassiveModeDisable);
	BIND(onShipAxis, customTimer.Get(), UTimerComponent::ResetTimer);
	springSnapshot = FSpringArmMemory(springArm);

}
void ASpaceCraft::InitInput()
{
	BIND_AXIS(VERTICAL, this, ASpaceCraft::MoveForward);
	BIND_AXIS(HORIZONTAL, this, ASpaceCraft::RotateShip);
	BIND_AXIS(VIEW, this, ASpaceCraft::AddPitch);
}
void ASpaceCraft::MoveForward(float _axis)
{
	INVOKE_PARAM(onShipMovement, _axis);
	forwardVelocity = FMath::Lerp(forwardVelocity, FMath::Abs(_axis), DELTATIME * fwdWeight);
	shipVelocity = GetActorForwardVector() * forwardVelocity;
	AddActorWorldOffset(shipVelocity);
}
void ASpaceCraft::RotateShip(float _axis)
{
	//if (forwardVelocity < 0.1f)
		//return;
	INVOKE_PARAM(onShipMovement, _axis);
	rotateAxis = FMath::Lerp(rotateAxis, _axis, DELTATIME * rotateWeight);
	AddActorLocalRotation(FRotator(0, rotateAxis * 10 * DELTATIME, 0));
	const FRotator _bank = FMath::Lerp(GetActorRotation(), FRotator(0, GetActorRotation().Yaw, bankAngle * rotateAxis), DELTATIME);
	SetActorRotation(_bank);
}
void ASpaceCraft::AddFloatingBehaviour()
{
	if (shipVelocity.Size() > .1f)
		return;
	SetActorLocation(GetActorLocation() + FVector(0, 0, FMath::Sin(WORLD->TimeSeconds) * DELTATIME * 10));
}
void ASpaceCraft::AddPitch(float _axis)
{
	INVOKE_PARAM(onShipMovement, _axis);
	pitchAxis = FMath::Lerp(pitchAxis, _axis, DELTATIME * pitchWeight);
	AddActorLocalRotation(FRotator(pitchAxis, 0, 0));
}

#pragma region PassiveMode
void ASpaceCraft::RotateAroundCamera()
{
	if (!springArm || !passiveModeEnable)
		return;
	springArm->AddRelativeRotation(FRotator(0, passiveModeYawSpeed * DELTATIME, 0));
}
void ASpaceCraft::ResetCameraRotation()
{
	if (!springArm || passiveModeEnable)
		return;
	springArm->SetRelativeRotation(LERP(springArm->GetRelativeRotation(), initRotation, DELTATIME * passiveModeResetSpeed));
}
void ASpaceCraft::PassiveModeEnable()
{
	passiveModeEnable = true;
	SetRandomPassiveValues();
}
void ASpaceCraft::SetRandomPassiveValues()
{
	const float _h = passiveModeSettings.GetRandomHeight();
	springArm->TargetArmLength = passiveModeSettings.GetRandomArmLength();
	springArm->SocketOffset += FVector(0, 0, _h);//

}
void ASpaceCraft::PassiveModeDisable()
{
	passiveModeEnable = false;
	springSnapshot.ResetValues(springArm);
}
void ASpaceCraft::MovingDetection(float _value)
{
	isMoving = FMath::Abs(_value) > 0;
	if (isMoving)
		INVOKE(onShipAxis);
}
#pragma endregion