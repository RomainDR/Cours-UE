// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

}

void AProjectile::InitProjectile(const float& _lifespawn)
{
	SetLifeSpan(_lifespawn);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Behaviour();

}

void AProjectile::Behaviour()
{
	AddActorWorldOffset(GetActorForwardVector() * GetWorld()->DeltaTimeSeconds * projectileSpeed);
}

