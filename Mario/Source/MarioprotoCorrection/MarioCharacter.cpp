// Fill out your copyright notice in the Description page of Project Settings.


#include "MarioCharacter.h"

// Sets default values
AMarioCharacter::AMarioCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



void AMarioCharacter::BeginPlay()
{
	Super::BeginPlay();
	marioSnap = FSnapshot(GetTransform());
	
}
void AMarioCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMarioCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Right/Left", this, &AMarioCharacter::MoveForward);
	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &AMarioCharacter::Jump);

}
void AMarioCharacter::MoveForward(float _axis)
{
	AddMovementInput(GetActorForwardVector() * _axis);
	if (_axis == 0) return;
	GetMesh()->SetRelativeRotation(FRotator(0, -90 * _axis, 0));

}

void AMarioCharacter::Jump()
{
	Super::Jump();

}
void AMarioCharacter::OnRespawnDelay()
{
	marioSnap.Reload(this);
	EnableInput(GetWorld()->GetFirstPlayerController());
	isDead = false;
}
void AMarioCharacter::Die()
{
	isDead = true;
	DisableInput(GetWorld()->GetFirstPlayerController());
	GetWorldTimerManager().SetTimer(respawnDelay, this, &AMarioCharacter::OnRespawnDelay, 2, false);
	
	
}

