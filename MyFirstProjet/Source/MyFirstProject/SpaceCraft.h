// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Galaxy.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TimerComponent.h"
#include "SpaceCraft.generated.h"

USTRUCT()
struct FSpringArmMemory
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
		float armLength = 0;
	UPROPERTY(VisibleAnywhere)
		FVector initLocation;

	FSpringArmMemory() {

	}
	FSpringArmMemory(USpringArmComponent* _spring)
	{
		armLength = _spring->TargetArmLength;
		initLocation = _spring->SocketOffset;
	}
	FORCEINLINE void ResetValues(USpringArmComponent* _toWrite)
	{
		_toWrite->TargetArmLength = armLength;
		_toWrite->SocketOffset = initLocation;
	}
};

USTRUCT()
struct FPassiveModeSettings
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, Category = "Passive settings", meta = (UIMin = 100, ClampMin = 100, ClampMax = 1000, UIMax = 1000))
		float minArmLength = 300;
	UPROPERTY(EditAnywhere, Category = "Passive settings", meta = (UIMin = 100, ClampMin = 100, ClampMax = 2000, UIMax = 2000))
		float maxArmLength = 500;

	UPROPERTY(EditAnywhere, Category = "Passive settings", meta = (UIMin = -200, ClampMin = -200, ClampMax = 2000, UIMax = 2000))
		float minHeight = 0;
	UPROPERTY(EditAnywhere, Category = "Passive settings", meta = (UIMin = -200, ClampMin = -200, ClampMax = 2000, UIMax = 2000))
		float maxHeight = 500;

	FORCEINLINE float GetRandomArmLength() const
	{
		return FMath::FRandRange(minArmLength, maxArmLength);
	}
	FORCEINLINE float GetRandomHeight() const
	{
		return FMath::FRandRange(minHeight, maxHeight);
	}
};


UCLASS()
class MYFIRSTPROJECT_API ASpaceCraft : public AActor
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShipInputAxis);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShipMovement, float, _axis);

	FOnShipMovement onShipMovement;
	FOnShipInputAxis onShipAxis;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> shipMesh = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<AGalaxy> currentGalaxy = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> camera = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UTimerComponent> customTimer = nullptr;


	UPROPERTY(EditAnywhere)
		float fwdWeight = 1;
	UPROPERTY(EditAnywhere)
		float rotateWeight = 1;
	UPROPERTY(EditAnywhere)
		float pitchWeight = 1;
	UPROPERTY(EditAnywhere)
		float bankAngle = 45;

	UPROPERTY(EditAnywhere)
		float passiveModeYawSpeed = 1;
	UPROPERTY(EditAnywhere)
		float passiveModeResetSpeed = 1;

	UPROPERTY(EditAnywhere)
		FPassiveModeSettings passiveModeSettings;
	UPROPERTY(EditAnywhere)
		FSpringArmMemory springSnapshot;

	FVector shipVelocity;
	bool passiveModeEnable = false, isMoving = false;
	float forwardVelocity, rotateAxis, pitchAxis; //(0,y)
	FRotator initRotation;

public:
	ASpaceCraft();
private:
	void InitShip();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void InitInput();
	void MoveForward(float _axis);
	void RotateShip(float _axis);
	void AddPitch(float _axis);
	void AddFloatingBehaviour();
	void SetRandomPassiveValues();
#pragma region PassiveMode
	void RotateAroundCamera();
	void ResetCameraRotation();
	UFUNCTION() void PassiveModeEnable();
	UFUNCTION() void PassiveModeDisable();
	UFUNCTION() void MovingDetection(float _value);
#pragma endregion

};
