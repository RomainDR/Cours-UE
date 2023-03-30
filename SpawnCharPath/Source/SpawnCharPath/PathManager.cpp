// Fill out your copyright notice in the Description page of Project Settings.


#include "PathManager.h"
#include "PathActor.h"

void UPathManager::AddPath(APathActor* _path)
{
	allPaths.Add(_path);
	UE_LOG(LogTemp, Warning, TEXT("new path register -> %s"), *_path->GetPathName())
}

APathActor* UPathManager::GetPath() const
{
	const int _randIndex = FMath::RandRange(0, allPaths.Num() - 1);
	if (_randIndex < 0) return nullptr;
	return allPaths[_randIndex];
}
