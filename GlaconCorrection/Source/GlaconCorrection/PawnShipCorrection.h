
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GridComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


#include "PawnShipCorrection.generated.h"


USTRUCT()
struct FShipControlSettings
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
		float forwardWeight = 1;
		UPROPERTY(EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
		float rollWeight = 1;
		UPROPERTY(EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
		float yawWeight = 1;
		UPROPERTY(EditAnywhere, meta = (UIMin = -60, ClampMin = 0, UIMax = 65, ClampMax = 65))
		float maxAngle = 60;

		float forwardAxis, rollAxis, yawAxis;

};
UCLASS()
class GLACONCORRECTION_API APawnShipCorrection : public APawn
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> camera = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UFloatingPawnMovement> movement = nullptr;

	UPROPERTY(EditAnywhere)
		FShipControlSettings settings;

public:
	APawnShipCorrection();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float _axis);
	void RollMovement(float _axis);
	void YawMovement(float _axis);
};
