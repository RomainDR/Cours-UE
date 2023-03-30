// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MyFirstActor.generated.h"



UCLASS()
class MYFIRSTPROJECT_API AMyFirstActor : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = "Location")
		bool useVector = true;

	UPROPERTY(EditAnywhere, Category = "Location")
		bool isInstantSpawn = true;

	UPROPERTY(EditAnywhere, Category = "Location")
		bool useOffset = true;

	UPROPERTY(EditAnywhere, Category = "Location|Controller")
		bool isControlledBy = false;

	UPROPERTY(EditAnywhere, Category = "Location", meta = (EditCondition = "useVector"))
		FVector originLocation = FVector();

	UPROPERTY(EditAnywhere, Category = "Location", meta = (EditCondition = "!useVector"))
		TObjectPtr<AActor> targetSpawn = nullptr;

	UPROPERTY(EditAnywhere, Category = "Location", meta = (EditCondition = "useOffset"))
		FVector offset = FVector();

	UPROPERTY(EditAnywhere, Category = "Location|Movement", meta = (EditCondition = "!isInstantSpawn", 
		UIMin = 0, UIMax = 200, ClampMin = 0, ClampMax = 200))
			float speed = 100;
	
	UPROPERTY(EditAnywhere, Category = "Location|Movement", meta = (EditCondition = "!isInstantSpawn"))
			bool canMove = false;

		UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;

		UPROPERTY(EditAnywhere, Category = "Debug") bool drawDebug = true;

		FVector fromLocation = FVector();
public:	
	AMyFirstActor();
	/// <summary>
	/// Get the location target of actor
	/// </summary>
	/// <returns></returns>
	FORCEINLINE FVector GetSpawnLocation() const
	{
		if (useVector)
			return originLocation + GetOffset();
		else if (!useVector && targetSpawn)
			return targetSpawn->GetActorLocation() + GetOffset();
		else
			return GetActorLocation();
	}
	FORCEINLINE FVector GetOffset() const { return useOffset ? offset : FVector(0); }
	FORCEINLINE void SetSpeed(const float& _speed) { speed = _speed;  }
	FORCEINLINE void SetInstantSpawn(const bool& _value) { isInstantSpawn = _value;  }
	FORCEINLINE void SetUseVector(const bool& _value) { useVector = _value;  }
	FORCEINLINE void SetOffset(const bool& _value) { useOffset = _value;  }
	FORCEINLINE void SetTarget(const TObjectPtr<AActor> _target) { targetSpawn = _target;  }

	FORCEINLINE void SetControlled(const bool& _value) { isControlledBy = _value; }
	FORCEINLINE void SetCanMove(const bool& _value) { canMove = _value; }
	void MoveToLocation(const FVector& _target);
	void MoveToLocation();

private:
	void MoveToLocation_Interp(const float& _speed);
	FVector GetFromPoint() const;
	void DrawDebug();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
