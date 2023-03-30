// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBoxChangeColor.h"
#include "Components/PointLightComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATriggerBoxChangeColor::ATriggerBoxChangeColor()
{
	PrimaryActorTick.bCanEverTick = true;
	trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	RootComponent = trigger;

}
void ATriggerBoxChangeColor::Tick(float DeltaSeconds)
{
	ChangeColor();
}
void ATriggerBoxChangeColor::NotifyActorBeginOverlap(AActor* _other)
{
	UPointLightComponent* pointLight = light->PointLightComponent;
	baseColor = pointLight->GetLightColor();

	GetWorld()->GetTimerManager().SetTimer(timerLight, secondToChange, true);


}
void ATriggerBoxChangeColor::NotifyActorEndOverlap(AActor* _other)
{
	UPointLightComponent* pointLight = light->PointLightComponent;
	GetWorld()->GetTimerManager().ClearTimer(timerLight);
	pointLight->SetLightColor(baseColor);
}

void ATriggerBoxChangeColor::ChangeColor()
{
	UPointLightComponent* pointLight = light->PointLightComponent;
	float timeElapsed = GetWorld()->GetTimerManager().GetTimerElapsed(timerLight) / secondToChange;

	int _index = selectIndexColor % colors.Num();
	FLinearColor color = UKismetMathLibrary::LinearColorLerp(colors[_index], colors[_index + 1], timeElapsed);
	pointLight->SetLightColor(color);
	if (timeElapsed >= 1) selectIndexColor++;
}

