// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoComponent.h"
#include "Util.h"

// Sets default values for this component's properties
UDemoComponent::UDemoComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDemoComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDemoComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateTimer(settings.timer, settings.timerBeforeLaunch);
}

void UDemoComponent::ResetTimer()
{
	settings.timer = 0.0f;
}

bool UDemoComponent::IsDemoMode()
{
	return settings.isDemo;
}

void UDemoComponent::StopDemoMode()
{
	settings.isDemo = false;
	ResetTimer();
}

void UDemoComponent::UpdateTimer(float& _timer, float& _maxTimer)
{
	_timer += DELTATIME;
	if (_timer > _maxTimer)
		settings.isDemo = true;
	
}

