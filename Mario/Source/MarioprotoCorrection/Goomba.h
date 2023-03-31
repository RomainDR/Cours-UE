// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Goomba.generated.h"

/**
 * 
 */
UCLASS()
class MARIOPROTOCORRECTION_API AGoomba : public AEnemy
{
	GENERATED_BODY()

protected:
	virtual void GlobalBehaviour(AMarioCharacter* _mario) override;
	virtual void UpBehaviour(AMarioCharacter* _mario) override;
	virtual void Die() override;
	
};
