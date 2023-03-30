// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Util.h"
#include "InputUtils.h"

ASpaceShip::ASpaceShip()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CREATE(UStaticMeshComponent, "Mesh");
	RootComponent = mesh;

	mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Game/Meshes/Ship/source.source'")));

	camera = CREATE(UCameraComponent, "Camera");
	springArm = CREATE(USpringArmComponent, "SpringArm");

	movement = CREATE(UFloatingPawnMovement, "Movement");
	AddOwnedComponent(movement);

	ATTACH_TO(springArm, RootComponent);
	ATTACH_TO(camera, springArm);


}

void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	//for (TSubclassOf<ASpaceShipDroneActor> _droneBP : drones) {
	//	TObjectPtr<ASpaceShipDroneActor> _drone = _droneBP->GetDefaultObject();
	
}

void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement();
	UpdateRotation();

	DRAW_SPHERE(GetActorLocation() + GetVelocity() * 200, 20, COLOR(Green), 2);
	DRAW_LINE(GetActorLocation(), GetActorLocation() + GetVelocity() * 200, COLOR(Green), 2);

	//LOG_W(LogTemp, "Bank: %f", settings.bank);
}

void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(VERTICAL, this, &ASpaceShip::MoveForward);
	PlayerInputComponent->BindAxis(HORIZONTAL, this, &ASpaceShip::MoveHorizontal);
	//PlayerInputComponent->BindAxis(ROTATE, this, &ASpaceShip::Rotate);

}

void ASpaceShip::MoveForward(float _axis)
{
		settings.forwardAxis = FMath::Lerp(settings.forwardAxis,_axis, DELTATIME * settings.verticalWeight);
}
void ASpaceShip::Rotate(float _axis)
{
	settings.rotateAxis = FMath::Lerp(settings.rotateAxis, _axis, DELTATIME * settings.rotateWeight);
}
void ASpaceShip::MoveHorizontal(float _axis)
{
	settings.rightAxis = FMath::Lerp(settings.rightAxis, _axis, DELTATIME * settings.horizontalWeight);
	//Rotate(_axis);
	//if (FMath::Abs(GetActorRotation().Roll) >= settings.bankAngle) return;

	//settings.bank = FMath::Lerp(settings.bank, _axis, DELTATIME * settings.bankWeight);
}


FVector ASpaceShip::GetVelocity() const
{
	return GetActorForwardVector() * settings.forwardAxis + GetActorRightVector() * settings.rightAxis;
}

void ASpaceShip::UpdateMovement()
{
	AddMovementInput(GetVelocity());
}
void ASpaceShip::UpdateRotation()
{
	AddControllerYawInput(settings.rotateAxis);
	//AddControllerRollInput(settings.bank);
}

