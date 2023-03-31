// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "DestructibleBlock.generated.h"

/**
 * 
 */
UCLASS()
class MARIOPROTOCORRECTION_API ADestructibleBlock : public ABlock
{
	GENERATED_BODY()

protected:
	virtual void DownBehaviour(AMarioCharacter* _mario) override;
	
};
