// Fill out your copyright notice in the Description page of Project Settings.


#include "Goomba.h"

void AGoomba::GlobalBehaviour(AMarioCharacter* _mario)
{
	if (isDead || !_mario || _mario->IsDead()) return;
	_mario->Die();
}

void AGoomba::UpBehaviour(AMarioCharacter* _mario)
{
	if (isDead || _mario && _mario->IsDead()) return;
	Die();
}

void AGoomba::Die()
{
	Super::Die();
	if (isDead) return;
	isDead = true;
	SetActorScale3D(GetActorScale() * FVector(1.3f, 1.3f, .2f));
	SetLifeSpan(1);
}
