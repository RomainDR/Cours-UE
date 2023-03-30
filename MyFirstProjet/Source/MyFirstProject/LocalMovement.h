// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocalMovement.generated.h"

UCLASS()
class MYFIRSTPROJECT_API ALocalMovement : public AActor
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndTimer);
		UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (UIMin = 0, ClampMin = 0))
		int speed = 0;
	UPROPERTY(EditAnywhere, Category = Movement, meta = (UIMin = -360, UIMax = 360, ClampMin = -360, ClampMax = 360))
		int rotateSpeed = 1;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (UIMin = 0, ClampMin = 0))
		float scaleSpeed = 1;

	
	UPROPERTY(EditAnywhere, Category = Movement)
		bool canMove = true;
	UPROPERTY(EditAnywhere, Category = Movement)
		bool canRotate = true;

	UPROPERTY(EditAnywhere, Category = Timer, meta = (UIMin = 0, ClampMin = 0))
		int maxTimeDelay = 10;

	FOnEndTimer onEndTimer;
	float timer = 0;
	bool timerStarted = true;
	FVector initScale = FVector();
	
public:		
	ALocalMovement();
	FORCEINLINE void SetCanMove(const bool& _value) { canMove = _value; }
	FORCEINLINE void SetCanRotate(const bool& _value) { canRotate = _value; }
	FORCEINLINE bool GetEndTimer() const { return timer > maxTimeDelay; }
	FORCEINLINE float GetTimerProgress() const { return timer / maxTimeDelay; }

protected:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void DrawDebugAxis();
	void Move(const FVector& _direction, const float& _speed);
	void Rotate(const FRotator& _rotation, const float& _speed);
	void BreathOfTheScale(const float& _speed);
	UFUNCTION() void StopMovement();
	UFUNCTION() void StopRotation();
	void UpdateTimer(float& _timer);
};
