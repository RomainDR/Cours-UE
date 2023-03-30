// Fill out your copyright notice in the Description page of Project Settings.


#include "StartishSkill.h"

void UStartishSkill::Spawn(UWorld* _world, const FVector& _origin, const float& _yaw)
{
	for (size_t i = 0; i < 360; i += 45)
	{
		for (size_t n = 0; n < number; n++)
		{
			const FVector _location = GetSpawnLocation(i, GetRadiusProgress(n)) + _origin;
			AProjectile* _projectile = _world->SpawnActor<AProjectile>(projectileType, _location, FRotator(0, i, 0));
			_projectile->InitProjectile(lifeSpan);
		}
	}
}
