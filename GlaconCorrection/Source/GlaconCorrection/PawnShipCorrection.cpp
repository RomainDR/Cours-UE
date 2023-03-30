// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnShipCorrection.h"
#include "Util.h"
#include "InputUtils.h"

// Sets default values
APawnShipCorrection::APawnShipCorrection()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	mesh = CREATE(UStaticMeshComponent, "Mesh");
	RootComponent = mesh;

	//mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Game/Meshes/Ship/source.source'")));

	camera = CREATE(UCameraComponent, "Camera");
	springArm = CREATE(USpringArmComponent, "SpringArm");

	ATTACH_TO(springArm, RootComponent);
	ATTACH_TO(camera, springArm);

	movement = CREATE(UFloatingPawnMovement, "Movement");

	AddOwnedComponent(movement);


}

void APawnShipCorrection::BeginPlay()
{
	Super::BeginPlay();

}
void APawnShipCorrection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DRAW_SPHERE(GetActorLocation() + GetVelocity().GetClampedToMaxSize(200), 10, COLOR(Yellow), 2);
	DRAW_LINE(GetActorLocation(), GetActorLocation() + GetVelocity().GetClampedToMaxSize(200), COLOR(Yellow), 2);

}
void APawnShipCorrection::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(VERTICAL, this, &APawnShipCorrection::MoveForward);
	PlayerInputComponent->BindAxis(HORIZONTAL, this, &APawnShipCorrection::RollMovement);
	PlayerInputComponent->BindAxis(HORIZONTAL, this, &APawnShipCorrection::YawMovement);

}

void APawnShipCorrection::MoveForward(float _axis)
{
	if (_axis < 0)
		return;
	settings.forwardAxis = FMath::Lerp(settings.forwardAxis, _axis, DELTATIME * (1/settings.forwardWeight));
	AddMovementInput(GetActorForwardVector(), settings.forwardAxis);
}

void APawnShipCorrection::RollMovement(float _axis)
{
	settings.rollAxis = FMath::Lerp(settings.rollAxis, _axis, DELTATIME * (1 / settings.rollWeight));
	SetActorRotation(FRotator(0, 0, settings.rollAxis * settings.maxAngle));
}

void APawnShipCorrection::YawMovement(float _axis)
{
	settings.yawAxis = FMath::Lerp(settings.yawAxis, _axis, DELTATIME * (1 / settings.yawWeight));
	AddControllerYawInput(settings.yawAxis);
}