// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
// Sets default values
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	arm = CreateDefaultSubobject<USpringArmComponent>("Arm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	arm->SetupAttachment(RootComponent);
	camera->SetupAttachment(arm);

	bUseControllerRotationYaw = true;

}
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Rotate", this, &AMainCharacter::Rotate);

}

void AMainCharacter::MoveForward(float _axis)
{
	AddMovementInput(GetActorForwardVector() * _axis);
	onMoveForward.Broadcast(_axis);

	//GetCharacterMovement()->MaxWalkSpeed = ...;
	//la speed est dans son movement -> maxWalk
}

void AMainCharacter::Rotate(float _axis)
{
	AddControllerYawInput(_axis);

	
}

