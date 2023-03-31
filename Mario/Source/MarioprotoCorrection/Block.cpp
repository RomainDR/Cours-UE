// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	blockMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	downTrigger = CreateDefaultSubobject<UBoxComponent>("Trigger");

	RootComponent = blockMesh;
	downTrigger->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

void ABlock::Init()
{
	if (!downTrigger) return;
	downTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABlock::OnDownTrigger);
}

void ABlock::OnDownTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMarioCharacter* _mario = Cast<AMarioCharacter>(OtherActor);
	if (!_mario) return;
	DownBehaviour(_mario);
}

void ABlock::DownBehaviour(AMarioCharacter* _mario)
{
}
