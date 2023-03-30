// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputActor.generated.h"

UCLASS()
class MYFIRSTPROJECT_API AInputActor : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (UIMin = 0, ClampMin = 0))
		float horizontalSpeed = 0;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (UIMin = 0, ClampMin = 0))
		float verticalSpeed = 0;

	UPROPERTY(EditAnywhere, Category = "Movement|Rotation", meta = (UIMin = 0, ClampMin = 0))
		float rotateSpeed = 0;

	UPROPERTY(EditAnywhere, Category = "Movement|Rotation", meta = (UIMin = 0, ClampMin = 0))
		float scaleSpeed = 0;
	
	FVector initScale, targetScale = FVector();
	FVector initLocation = FVector();
	FRotator initRotation = FRotator();
	
public:
	AInputActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetupInput();
	void SetHorizontal(float _axis);
	void SetVertical(float _axis);
	void SetRotation(float _axis);
	void SetDynamicScale(float _axis);
	void UpdateScale(const float& _scaleSpeed);
	void Respawn();

};
