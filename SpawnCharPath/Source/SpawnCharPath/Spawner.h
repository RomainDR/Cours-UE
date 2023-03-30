// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BillboardComponent.h>
#include "SpawnerSettings.h"

#include "Spawner.generated.h"

UCLASS()
class SPAWNCHARPATH_API ASpawner : public AActor
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawn);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartSpawn);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopSpawn);

	FOnSpawn onSpawn;
	FOnStartSpawn onStartSpawn;
	FOnStopSpawn onStopSpawn;

	bool isStarted = false;
	FTimerHandle spawnerTimer;
	int spawnCount = 0;


		UPROPERTY(EditAnywhere)
		TObjectPtr< UBillboardComponent> icon = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr< USpawnerSettings> settings = nullptr;
		UPROPERTY(EditAnywhere)
			TObjectPtr<USceneComponent> spawnLocation = nullptr;
		UPROPERTY(EditAnywhere)
			FColor spawnerDebugColor = FColor::Magenta;
	
public:	
	ASpawner();
	FORCEINLINE FVector GetSpawnLocation()const {
		return spawnLocation ? spawnLocation->GetComponentLocation() : GetActorLocation();
	}
	FORCEINLINE float GetTimerRatio()const {
		if (!settings) return -1;
		return GetWorldTimerManager().GetTimerElapsed(spawnerTimer) / settings->GetMaxTimer();
	}

	UFUNCTION(BlueprintCallable) void StartSpawner();
	UFUNCTION(BlueprintCallable) void StopSpawner();
	UFUNCTION(BlueprintCallable) void RestartSpawner();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void RunSpawner();
	UFUNCTION() void Spawn();
};
