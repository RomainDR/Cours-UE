// Fill out your copyright notice in the Description page of Project Settings.

#include "ControlActor_Correction.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AControlActor_Correction::AControlActor_Correction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	icon = CreateDefaultSubobject<UBillboardComponent>("Root");
	RootComponent = icon;
}

// Called when the game starts or when spawned
void AControlActor_Correction::BeginPlay()
{
	Super::BeginPlay();
	onTimerReached.AddDynamic(this, &AControlActor_Correction::TakeControl);
	onTimerReached.AddDynamic(this, &AControlActor_Correction::TestAction);
	onActionParam.AddDynamic(this, &AControlActor_Correction::TestActionParam);
	//TakeControl();
}

// Called every frame
void AControlActor_Correction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebug();
	UpdateTimer(timer, maxTime);
		//TakeControl();
}

void AControlActor_Correction::UpdateTimer(float& _timer, const float& _max)
{
	if (!isStarted)
		return;

	if (!useTimer)
	{
		onTimerReached.Broadcast();
		return;
	}

	_timer += DELTATIME;

	if (_timer > _max)
	{
		_timer = 0.0f;

		if (!isLoopTimer)
		{
			isStarted = false;
		}
		onTimerReached.Broadcast();
		onActionParam.Broadcast(true);
	}
}

void AControlActor_Correction::DrawDebug()
{
	DRAW_BOX(GetActorLocation(), FVector(50), COLOR(Red), 2);
	DRAW_SPHERE(GetTargetLocation(), 50, COLOR(Cyan), 2);
	DRAW_LINE(GetActorLocation(), GetTargetLocation(), COLOR(Magenta), 2);
	const FLinearColor _progressColor = UKismetMathLibrary::LinearColorLerp(FLinearColor::Red, FLinearColor::Green, GetTimerProgressNormalized());
	DRAW_BOX(GetActorLocation() + FVector(0, 0, 100), (FVector(25) * GetTimerProgressNormalized()) + FVector(10), _progressColor.ToFColor(true), 2);
	DRAW_TEXT(GetActorLocation(), FString::Printf(TEXT("timer %f -> progress %f"), timer, GetTimerProgressPercent()), FColor::Red, 1.2f);
}

void AControlActor_Correction::TakeControl()
{
	if (!target)
		return;
	target->SetCanMove(true);
	target->SetUseVector(true);
	target->MoveToLocation();
}

void AControlActor_Correction::TestAction()
{
	LOG_W(LogTemp, "test");
}

void AControlActor_Correction::TestActionParam(bool _param)
{
	LOG_W(LogTemp, "%b", _param);
}

