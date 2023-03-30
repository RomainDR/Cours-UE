// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPath.h"
#include "SpawnCharPathGameModeBase.h"
#include "FollowPathComponent.h"

// Sets default values
ACharacterPath::ACharacterPath()
{
	PrimaryActorTick.bCanEverTick = true;
	followComponent = CreateDefaultSubobject<UFollowPathComponent>("Follower");
	AddOwnedComponent(followComponent);

	arm = CreateDefaultSubobject<USpringArmComponent>("Spring");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	arm->SetupAttachment(RootComponent);
	camera->SetupAttachment(arm);

}

void ACharacterPath::ControlCharacter()
{
	if (followComponent)
		followComponent->StopFollow();
	bUseControllerRotationYaw = true;
}

void ACharacterPath::FreeCharacter()
{
	if (followComponent)
		followComponent->StartFollow();
	bUseControllerRotationYaw = false;
}

void ACharacterPath::BeginPlay()
{
	Super::BeginPlay();
	GetPawnManager()->AddPawn(this);
	
}

void ACharacterPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterPath::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &ACharacterPath::MoveForward);
	PlayerInputComponent->BindAxis("Rotate", this, &ACharacterPath::Rotate);

}
void ACharacterPath::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetPawnManager()->RemovePawn(this);
}
TObjectPtr<APawnSwitcher> ACharacterPath::GetPawnManager()
{
	ASpawnCharPathGameModeBase* _gm = GetWorld()->GetAuthGameMode<ASpawnCharPathGameModeBase>();
	if (!_gm)
		return nullptr;
	return _gm->GetPawnSwitcher();
}

void ACharacterPath::MoveForward(float _axis)
{
	AddMovementInput(GetActorForwardVector(), _axis);
}

void ACharacterPath::Rotate(float _axis)
{
	AddControllerYawInput(_axis);
}

