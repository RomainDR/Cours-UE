// Fill out your copyright notice in the Description page of Project Settings.


#include "GridComponent.h"
#include "InputUtils.h"
#include "PawnShipCorrection.h"

UGridComponent::UGridComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGridComponent::BeginPlay()
{
	Super::BeginPlay();
	OWNER->InputComponent->BindAction(MOVE_TO, EInputEvent::IE_Pressed, this, &UGridComponent::SetTargetTo);
	
	
}

void UGridComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ShowGrid();
	MoveToTarget();

	DRAW_SPHERE(GetActorLocation(), 50, COLOR(Red), 2);
}

void UGridComponent::ShowGrid()
{
	for (int row = 0; row < settings.row + 1; row++)
	{
		for (int column = 0; column < settings.column + 1; column++)
		{
			FVector _position = FVector(row * 100, column * 100, 0);
			DRAW_SPHERE(_position, 20, COLOR(Green), 2);
			/*if(column != 0)
				DRAW_LINE(FVector(row, (column-1) * 100, 0), _position, COLOR(Green), 2);
			if(row != 0)
				DRAW_LINE(FVector((row - 1) * 100, column, 0), _position, COLOR(Green), 2);*/
		}
	}
}

void UGridComponent::MoveToTarget()
{
	if (!target) return;
	const FVector _loc = OWNER->GetActorLocation();
	//target->SetActorLocation(FMath::Lerp(GetTargetLocation(), FVector(settings.targetAxis, settings.targetHorizontal, _loc.Z), DELTATIME * settings.axisWeight));
	target->SetActorLocation(FVector(settings.targetAxis, settings.targetHorizontal, _loc.Z));
	DRAW_SPHERE(GetTargetLocation(), 150, COLOR(Blue), 2);
}

void UGridComponent::SetTargetTo()
{
	APawnShipCorrection* _ship = Cast<APawnShipCorrection>(OWNER);
	if (!_ship) return;
	LOG_W(LogTemp, "Je passe");
	//settings.targetAxis = _ship->GetForwardTarget();
	//settings.targetHorizontal = _ship->GetRightTarget();
	LOG_W(LogTemp, "TargetAxis: %f", settings.targetAxis);
	LOG_W(LogTemp, "TargetHorizontal: %f", settings.targetHorizontal);
	DRAW_TEXT(GetActorLocation(), GetTargetLocation().ToCompactString(), COLOR(Red), 2);
}

