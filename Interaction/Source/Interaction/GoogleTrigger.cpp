// Fill out your copyright notice in the Description page of Project Settings.


#include "GoogleTrigger.h"
#include "InteractionCharacter.h"

// Sets default values
AGoogleTrigger::AGoogleTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	RootComponent = trigger;

}

void AGoogleTrigger::NotifyActorBeginOverlap(AActor* _other)
{
	AInteractionCharacter* _char = Cast<AInteractionCharacter>(_other);
	if (!_char) return;
	Execute();
}

void AGoogleTrigger::NotifyActorEndOverlap(AActor* _other)
{
	AInteractionCharacter* _char = Cast<AInteractionCharacter>(_other);
	if (!_char) return;
		ResetAll();
}

void AGoogleTrigger::Execute()
{
	for(AGoogleItem* _item : connectedItems)
		if (_item)
			_item->Enable();
}

void AGoogleTrigger::ResetAll()
{
	for (AGoogleItem* _item : connectedItems)
		if (_item)
			_item->Disable();
}
