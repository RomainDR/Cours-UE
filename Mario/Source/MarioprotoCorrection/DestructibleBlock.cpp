// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleBlock.h"

void ADestructibleBlock::DownBehaviour(AMarioCharacter* _mario)
{
	SetLifeSpan(0.1);
}
