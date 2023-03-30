#include "SkillLauncherComponent.h"


USkillLauncherComponent::USkillLauncherComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USkillLauncherComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->GetWorldTimerManager().SetTimer(spawnTimerTest, this, &USkillLauncherComponent::InvokeSkill, 5, true);
}


void USkillLauncherComponent::InvokeSkill()
{
	const int _index = FMath::RandRange(0, skills.Num() - 1);
	USkill* _skill = skills[_index];
	if (!_skill)
		return;
	_skill->Spawn(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation().Yaw);
}

