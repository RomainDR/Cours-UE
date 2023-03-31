// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyMovingComponent.h"
#include "MarioCharacter.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "Enemy.generated.h"

UCLASS()
class MARIOPROTOCORRECTION_API AEnemy : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> root = nullptr;

		UPROPERTY(EditAnywhere)
		TObjectPtr<UBoxComponent> globalTrigger = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UBoxComponent> upTrigger = nullptr;

		UPROPERTY(EditAnywhere)
		TObjectPtr<UEnemyMovingComponent> moveComponent = nullptr;

		bool isDead = false;
	
public:	
	AEnemy();

protected:
	void Init();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GlobalBehaviour(AMarioCharacter* _mario);
	virtual void UpBehaviour(AMarioCharacter* _mario);
	virtual void Die();
private:
	UFUNCTION() void OnGlobalTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnUpTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
