// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusBlock.h"

void ABonusBlock::DownBehaviour(AMarioCharacter* _mario)
{
	if (!bonusBlockGraphcis || !bonusItem) return;
	GetWorld()->SpawnActor<AActor>(bonusBlockGraphcis, GetActorLocation(), GetActorRotation());
	GetWorld()->SpawnActor<AActor>(bonusItem, GetActorLocation() + offsetSpawnBonus, GetActorRotation());
	SetLifeSpan(.1f);
}
