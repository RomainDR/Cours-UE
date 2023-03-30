// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnCharPathGameModeBase.h"
#include "PathActor.h"
#include "FollowPathComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPAWNCHARPATH_API UFollowPathComponent : public UActorComponent
{
	GENERATED_BODY()
		UPROPERTY(VisibleAnywhere)
		TObjectPtr<APathActor> currentPath = nullptr;
	UPROPERTY(EditAnywhere)
		float minimalRange = 100;
	UPROPERTY(EditAnywhere)
		float moveSpeed = 200;

	int navIndex = 0;
	bool canFollowPath = true;

public:	
	UFollowPathComponent();

	FORCEINLINE FVector GetOwnerLocation() const {
		return GetOwner()->GetActorLocation();
	}
	FORCEINLINE bool IsAtLocation(const FVector& _location) const {
		return FVector::Distance(GetOwnerLocation(), _location) < minimalRange;
	}
	void StartFollow();
	void StopFollow();
protected:
	void Init();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void MoveAlongPath();
	TObjectPtr<UPathManager> GetPathManager();
	
};
