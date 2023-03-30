// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPLink.generated.h"

UCLASS()
class GLACONCORRECTION_API ABPLink : public AActor
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTest);

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
		float life = 0;

		UPROPERTY(BlueprintAssignable, BlueprintCallable, meta = (AllowPrivateAccess))
		FOnTest onTest;
	
public:	
	ABPLink();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable) void Test();
	UFUNCTION(BlueprintCallable) void TestParam(float _value);

};
