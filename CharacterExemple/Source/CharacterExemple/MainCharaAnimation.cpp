// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharaAnimation.h"

void UMainCharaAnimation::NativeBeginPlay()
{
	mainPawn = Cast<AMainCharacter>(TryGetPawnOwner());
	if (!mainPawn)
		return;
	mainPawn->OnMoveForward().AddDynamic(this, &UMainCharaAnimation::SetSpeed);
}

//void UMainCharaAnimation::NativeUpdateAnimation(float deltaSeconds)
//{
//	speed = GetSpeed();
//}
//
//float UMainCharaAnimation::GetSpeed() const
//{	
//	if (!mainPawn) return 0;
//	return mainPawn->GetVelocity().GetSafeNormal().Size();
//}

void UMainCharaAnimation::SetSpeed(float _speed)
{
	speed = _speed;
}