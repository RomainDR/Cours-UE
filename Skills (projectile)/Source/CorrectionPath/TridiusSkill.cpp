// Fill out your copyright notice in the Description page of Project Settings.


#include "TridiusSkill.h"

void UTridiusSkill::Spawn(UWorld* _world, const FVector& _origin, const float& _yaw)
{
	for (size_t i = 0; i < 90; i+=30)
	{
		const int _angle = (i + _yaw) - 30;
		for (size_t n = 0; n < number; n++)
		{
			const FVector _location = GetSpawnLocation(_angle, GetRadiusProgress(n)) + _origin;
			AProjectile* _projectile = _world->SpawnActor<AProjectile>(projectileType, _location, FRotator(0, _yaw, 0));
			_projectile->InitProjectile(lifeSpan);
		}
	}
}
