// Fill out your copyright notice in the Description page of Project Settings.


#include "GoogleLightSwitchColor.h"

AGoogleLightSwitchColor::AGoogleLightSwitchColor()
{
	icon = CreateDefaultSubobject<UBillboardComponent>("Icon");
	RootComponent = icon;
}

void AGoogleLightSwitchColor::Enable()
{
	GetWorldTimerManager().SetTimer(switchTimer, this, &AGoogleLightSwitchColor::Switch, 1, true);
	//if (!connectedLamp) return;
	//connectedLamp->SwitchColor();

}

void AGoogleLightSwitchColor::Disable()
{
	if (!connectedLamp) return;
	GetWorldTimerManager().ClearTimer(switchTimer);
}

void AGoogleLightSwitchColor::Switch()
{
	if (!connectedLamp) return;
	connectedLamp->SwitchColor();
}
