// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstPawn.h"
#include "Util.h"
#include "InputUtils.h"

AMyFirstPawn::AMyFirstPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CREATE(UStaticMeshComponent, "Root");
	RootComponent = mesh;
	mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Engine/BasicShapes/Sphere.Sphere'")));

	springArm = CREATE(USpringArmComponent, "SpringArm");
	camera = CREATE(UCameraComponent, "Camera");

	movement = CREATE(UFloatingPawnMovement, "Movement");

	ATTACH_TO(springArm, RootComponent);
	ATTACH_TO(camera, springArm);

	AddOwnedComponent(movement);

	//bUseControllerRotationYaw = true;

}
void AMyFirstPawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	
}
void AMyFirstPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AMyFirstPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(VERTICAL, this, &AMyFirstPawn::MoveForward);
	PlayerInputComponent->BindAxis(HORIZONTAL, this, &AMyFirstPawn::MoveHorizontal);
	PlayerInputComponent->BindAxis(ROTATE, this, &AMyFirstPawn::RotateYaw);
}

void AMyFirstPawn::MoveForward(float _axis)
{
	AddMovementInput(GetActorForwardVector(), _axis);
}

void AMyFirstPawn::MoveHorizontal(float _axis)
{
	AddMovementInput(GetActorRightVector(), _axis);
}

void AMyFirstPawn::RotateYaw(float _axis)
{
	AddControllerYawInput(_axis * DELTATIME * 50);
}

