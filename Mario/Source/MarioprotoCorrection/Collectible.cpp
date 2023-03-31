// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"

// Sets default values
ACollectible::ACollectible()
{
	PrimaryActorTick.bCanEverTick = true;
	trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = trigger;
	mesh->SetupAttachment(RootComponent);

}

void ACollectible::BeginPlay()
{
	Super::BeginPlay();	
}

void ACollectible::NotifyActorBeginOverlap(AActor* _other)
{
	AMarioCharacter* _mario = Cast<AMarioCharacter>(_other);
	if (!_mario) return;
	CollectibleBehaviour(_mario);
}

void ACollectible::CollectibleBehaviour(AMarioCharacter* _mario)
{

}

