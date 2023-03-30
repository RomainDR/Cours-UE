#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GridActorCorr.h"
#include "DemoModeComponentCorr.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GridPawnCorr.generated.h"

UCLASS()
class GLACONCORRECTION_API AGridPawnCorr : public APawn
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> springArm = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> camera = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<AGridActorCorr> grid = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UDemoModeComponentCorr> demo = nullptr;
	UPROPERTY(EditAnywhere)
		bool useDemoMode = false;

public:
	AGridPawnCorr();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitPawn();
	TObjectPtr<AGridActorCorr> GetGrid() const;

public:
	UFUNCTION(BlueprintCallable) void UpMove();
	UFUNCTION(BlueprintCallable) void DownMove();
	UFUNCTION(BlueprintCallable) void LeftMove();
	UFUNCTION(BlueprintCallable) void RightMove();
	UFUNCTION(BlueprintCallable) void SelectGridCell();
};
