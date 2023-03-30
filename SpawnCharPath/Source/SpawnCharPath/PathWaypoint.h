// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BillboardComponent.h>
#include "PathWaypoint.generated.h"

UCLASS()
class SPAWNCHARPATH_API APathWaypoint : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr< UBillboardComponent> icon = nullptr;

	
public:	
	APathWaypoint();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
