// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerboxActor.h"
#include "InteractionCharacter.h"
#include "Components/PointLightComponent.h"

// Sets default values
ATriggerboxActor::ATriggerboxActor()
{
	PrimaryActorTick.bCanEverTick = false;
	trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	RootComponent = trigger;


}

void ATriggerboxActor::NotifyActorBeginOverlap(AActor* _other)
{
	AInteractionCharacter* _char = Cast<AInteractionCharacter>(_other);
	if (!_char) return;
	UE_LOG(LogTemp, Warning, TEXT("Ok Enter -> %s"), *_other->GetName());
	if (!light) {
		UE_LOG(LogTemp, Warning, TEXT("Pas de light !"));
		return;
	}
	TObjectPtr<UPointLightComponent> pointLight = light->PointLightComponent;
	pointLight->SetIntensity(lightIntensity);	
}

void ATriggerboxActor::NotifyActorEndOverlap(AActor* _other)
{
	UE_LOG(LogTemp, Warning, TEXT("Ok Exit -> %s"), *_other->GetName());
	if (!light) UE_LOG(LogTemp, Warning, TEXT("Pas de light"));
	light->PointLightComponent->SetIntensity(0);
}

