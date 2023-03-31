// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/BoxComponent.h>
#include "MarioCharacter.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

UCLASS()
class MARIOPROTOCORRECTION_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectible();
	UPROPERTY(EditAnywhere)
		TObjectPtr<UBoxComponent> trigger = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;

private:
	virtual void BeginPlay() override;
	void NotifyActorBeginOverlap(AActor* _other);

protected:
	virtual void CollectibleBehaviour(AMarioCharacter* _mario);

};
