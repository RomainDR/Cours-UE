// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnSwitcher.h"

APawnSwitcher::APawnSwitcher()
{
	PrimaryActorTick.bCanEverTick = true;
		icon = CreateDefaultSubobject< UBillboardComponent>("Icon");
	RootComponent = icon;
}


void APawnSwitcher::BeginPlay()
{
	Super::BeginPlay();
	onSelect.AddDynamic(this, &APawnSwitcher::SwitchView);
	APlayerController* _fpc = GetWorld()->GetFirstPlayerController();
	if (!_fpc) return;
	_fpc->InputComponent->BindAction("Previous", IE_Pressed, this, &APawnSwitcher::SelectPrevious);
	_fpc->InputComponent->BindAction("Next", IE_Pressed, this, &APawnSwitcher::SelectNext);
	_fpc->InputComponent->BindAction("Switch", IE_Pressed, this, &APawnSwitcher::Switch);
	_fpc->InputComponent->BindAction("Release", IE_Pressed, this, &APawnSwitcher::Release);
}

void APawnSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebug();

}

void APawnSwitcher::AddPawn(ACharacterPath* _pawn)
{
	movablePawns.Add(_pawn);
}

void APawnSwitcher::RemovePawn(ACharacterPath* _pawn)
{
	movablePawns.Remove(_pawn);
}


void APawnSwitcher::DrawDebug()
{
	for (ACharacter* _pawn : movablePawns)
	{
		if (!_pawn) continue;
		DrawDebugLine(GetWorld(), _pawn->GetActorLocation(), GetActorLocation(), FColor::Cyan, false, -1, 0, 5);
	}
}

void APawnSwitcher::SelectNext()
{
	if (current) current->FreeCharacter();
	if (movablePawns.Num() == 0) return;
	selectIndex++;
	selectIndex = FMath::Fmod(selectIndex, movablePawns.Num());
	onSelect.Broadcast();
}

void APawnSwitcher::Switch()
{
	if (current) {
		current->ControlCharacter();
		GetWorld()->GetFirstPlayerController()->Possess(current);
	}
}

void APawnSwitcher::Release()
{
	if (current) {
		if (current->IsControlled())
			GetWorld()->GetFirstPlayerController()->UnPossess();
		current->FreeCharacter();
		//current = nullptr;
	}
}

void APawnSwitcher::SelectPrevious()
{
	if (movablePawns.Num() == 0) return;
	selectIndex--;
	selectIndex = selectIndex < 0 ? movablePawns.Num() - 1 : selectIndex;
	onSelect.Broadcast();
}

 void APawnSwitcher::SwitchView()
{
	 if (selectIndex >= 0 && selectIndex <= movablePawns.Num() - 1)
	 {
		 current = movablePawns[selectIndex];
		 if (!current) return;
		 GetWorld()->GetFirstPlayerController()->SetViewTarget(current);
	 }
}

