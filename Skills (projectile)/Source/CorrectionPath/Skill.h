// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Projectile.h"


#include "Skill.generated.h"

/**
 * 
 */
UCLASS()
class CORRECTIONPATH_API USkill : public UDataAsset
{
	GENERATED_BODY()
protected: 
    UPROPERTY(EditAnywhere)
        TSubclassOf<AProjectile> projectileType;

    UPROPERTY(EditAnywhere, meta = (UIMin = 1, ClampMin = 1))
        float lifeSpan = 5;
    UPROPERTY(EditAnywhere, meta = (UIMin = 1, ClampMin = 1))
        float radius = 100;
    UPROPERTY(EditAnywhere, meta = (UIMin = 1, ClampMin = 1))
        float number = 5;

    FVector GetSpawnLocation(const int& _angle, const float& _radius) const;
    FORCEINLINE float GetRadiusPart() const {
        return radius / number;
    } FORCEINLINE float GetRadiusProgress(const int& _part) const {
        return (GetRadiusPart() * _part/radius) * 100;
    }
public:
    virtual void Spawn(UWorld* _world, const FVector& _origin, const float& _yaw);

};
