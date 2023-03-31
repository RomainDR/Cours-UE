// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);

	globalTrigger = CreateDefaultSubobject<UBoxComponent>("Global_Trigger");
	globalTrigger->SetupAttachment(RootComponent);

	upTrigger = CreateDefaultSubobject<UBoxComponent>("Up_Trigger");
	upTrigger->SetupAttachment(RootComponent);

	moveComponent = CreateDefaultSubobject<UEnemyMovingComponent>("MoveComponent");
	AddOwnedComponent(moveComponent);

}


// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEnemy::Init()
{
	if (!globalTrigger || !upTrigger) return;
	globalTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnGlobalTrigger);
	upTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnUpTrigger);

}

void AEnemy::OnGlobalTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMarioCharacter* _mario = Cast<AMarioCharacter>(OtherActor);
	if (!_mario) return;
	GlobalBehaviour(_mario);
}

void AEnemy::OnUpTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMarioCharacter* _mario = Cast<AMarioCharacter>(OtherActor);
	if (!_mario) return;
	UpBehaviour(_mario);

}
void AEnemy::GlobalBehaviour(AMarioCharacter* _mario)
{
}

void AEnemy::UpBehaviour(AMarioCharacter* _mario)
{
}

void AEnemy::Die()
{
	if (moveComponent)
		moveComponent->Stop();
}


