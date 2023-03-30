// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "SpaceShipDroneActor.h"

#include "SpaceShip.generated.h"

USTRUCT()
struct FShipSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, UIMin = 0))
		float verticalWeight = 1.0f;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, UIMin = 0))
		float horizontalWeight = 1.0f;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, UIMin = 0))
		float rotateWeight = 1.0f;
	
	UPROPERTY(VisibleAnywhere)
	float forwardAxis;
	UPROPERTY(VisibleAnywhere)
	float rightAxis;
	UPROPERTY(VisibleAnywhere)
	float rotateAxis;
};

UCLASS()
class GLACONCORRECTION_API ASpaceShip : public APawn
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> springArm = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> camera = nullptr;
		UPROPERTY(EditAnywhere)
			TObjectPtr<UFloatingPawnMovement> movement = nullptr;
		UPROPERTY(EditAnywhere)
			TArray<TSubclassOf<ASpaceShipDroneActor>> drones;
		
		UPROPERTY(EditAnywhere, Category = "Movement")
			FShipSettings settings;

public:
	ASpaceShip();

protected:	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetVelocity() const;
	void MoveForward(float _axis);
	void MoveHorizontal(float _axis);
	void Rotate(float _axis);
	void UpdateMovement();
	void UpdateRotation();
};
