// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinCollectible.h"

void ACoinCollectible::RotateCoin()
{
	AddActorWorldRotation(FRotator(0, rotateSpeed, 0));
}

void ACoinCollectible::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	RotateCoin();
}

void ACoinCollectible::CollectibleBehaviour(AMarioCharacter* _mario)
{
	SetLifeSpan(.1f);
}
