// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MarioCharacter.generated.h"

USTRUCT()
struct FSnapshot
{
	GENERATED_BODY()
		FVector  location;
	FRotator rotation;
	FSnapshot()
	{
	}
	FSnapshot(FTransform _transform)
	{
		location = _transform.GetLocation();
		rotation = _transform.GetRotation().Rotator();
	}
	void Reload(AActor* _actor)
	{
		_actor->SetActorLocationAndRotation(location, rotation);
	}
};

UCLASS()
class MARIOPROTOCORRECTION_API AMarioCharacter : public ACharacter
{
	GENERATED_BODY()
		bool isDead = false;
	FSnapshot marioSnap;
	FTimerHandle respawnDelay;
public:
	AMarioCharacter();

	FORCEINLINE bool IsDead() const {
		return isDead;
	}
	void Die();
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float _axis);

	void Jump() override;
	void OnRespawnDelay();

};
