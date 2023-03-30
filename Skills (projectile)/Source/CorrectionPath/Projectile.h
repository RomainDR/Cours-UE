// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class CORRECTIONPATH_API AProjectile : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		float projectileSpeed = 500;
	
public:	
	AProjectile();
	virtual void InitProjectile(const float& _lifespawn);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Behaviour();

};
