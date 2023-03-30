// Fill out your copyright notice in the Description page of Project Settings.


#include "GoogleLamp.h"

AGoogleLamp::AGoogleLamp()
{
	light = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	RootComponent = light;
	light->SetIntensity(0);
}

void AGoogleLamp::Enable()
{
	if (!light || !settings) return;
	light->SetIntensity(settings->MaxIntensity());
}

void AGoogleLamp::Disable()
{
	if (!light) return;
	light->SetIntensity(0);
}

void AGoogleLamp::SwitchColor()
{
	UE_LOG(LogTemp, Warning, TEXT("Ok"));
	if (!light) return;
	colorIndex++;
	colorIndex = colorIndex > settings->MaxColors()-1 ? 0 : colorIndex;
	light->SetLightColor(settings->GetColor(colorIndex));

}
