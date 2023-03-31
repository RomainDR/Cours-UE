// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "Collectible.h"
#include "BonusBlock.generated.h"

/**
 * 
 */
UCLASS()
class MARIOPROTOCORRECTION_API ABonusBlock : public ABlock
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TSubclassOf<ACollectible> bonusItem = nullptr;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> bonusBlockGraphcis = nullptr;
	UPROPERTY(EditAnywhere)
		FVector offsetSpawnBonus = FVector(0, 0, 150);
	

protected:
	virtual void DownBehaviour(AMarioCharacter* _mario) override;
};
