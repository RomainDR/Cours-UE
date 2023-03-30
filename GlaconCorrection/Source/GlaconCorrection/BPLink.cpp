// Fill out your copyright notice in the Description page of Project Settings.


#include "BPLink.h"
#include "Util.h"

ABPLink::ABPLink()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABPLink::BeginPlay()
{
	Super::BeginPlay();
	onTest.Broadcast();
	
}

void ABPLink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABPLink::Test()
{
	LOG_W(LogTemp, "Test");
}

void ABPLink::TestParam(float _value)
{
	LOG_W(LogTemp, "Test %f", _value);
}

