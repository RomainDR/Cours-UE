// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterPath.h"
#include "GameFramework/Actor.h"
#include <Components/BillboardComponent.h>
#include "PawnSwitcher.generated.h"

UCLASS()
class SPAWNCHARPATH_API APawnSwitcher : public AActor
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelect);

	FOnSelect onSelect;


	UPROPERTY(EditAnywhere)
		TObjectPtr< UBillboardComponent> icon = nullptr;
		UPROPERTY(VisibleAnywhere)
		TArray<ACharacterPath*> movablePawns;
		UPROPERTY(VisibleAnywhere)
			TObjectPtr<ACharacterPath> current = nullptr;

	int selectIndex = 0;
	
public:	
	APawnSwitcher();

	void AddPawn(ACharacterPath* _pawn);
	void RemovePawn(ACharacterPath* _pawn);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void DrawDebug();

	void SelectNext();
	void Switch();
	void Release();
	void SelectPrevious();
	UFUNCTION() void SwitchView();
};
