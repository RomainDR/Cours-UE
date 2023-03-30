// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoModeComponentCorr.h"
#include "GridPawnCorr.h"

UDemoModeComponentCorr::UDemoModeComponentCorr()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UDemoModeComponentCorr::StartDemo()
{
	StartDemo(demoRate);
}

UFUNCTION(BlueprintCallable) void UDemoModeComponentCorr::StartDemo(const float& _delay)
{
	//InRate = temps refait
	//InLoop = Boucle ou pas
	//FirstDelay = temps avant premier  lancement
	GetWorld()->GetTimerManager().SetTimer(demoTimer, this, &UDemoModeComponentCorr::DemoAction, demoRate, true, _delay);
	onDemoStart.Broadcast();
}

UFUNCTION(BlueprintCallable) void UDemoModeComponentCorr::StopDemo()
{
	GetWorld()->GetTimerManager().ClearTimer(demoTimer);
	onDemoStop.Broadcast();
}

void UDemoModeComponentCorr::BeginPlay()
{
	Super::BeginPlay();	
	onDemoAction.AddDynamic(this, &UDemoModeComponentCorr::RunDemo);
}

void UDemoModeComponentCorr::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDemoModeComponentCorr::DemoAction()
{
	onDemoAction.Broadcast();
}

UFUNCTION(BlueprintCallable) void UDemoModeComponentCorr::RunDemo()
{
	AGridPawnCorr* _player = Cast<AGridPawnCorr>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!_player)
		return;

	int _randAction = FMath::RandRange(0, 4);
	switch (_randAction)
	{
	case 0: 
		_player->RightMove();
		break;
	case 1:
		_player->LeftMove();
		break;
	case 2: 
		_player->UpMove();
		break;
	case 3: 
		_player->DownMove();
		break;
	}
	_randAction = FMath::RandRange(0, 100);
	if (_randAction > demoCallShipRange)
		_player->SelectGridCell();
}

