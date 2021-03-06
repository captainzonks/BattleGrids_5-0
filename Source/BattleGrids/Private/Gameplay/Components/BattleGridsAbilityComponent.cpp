// © 2021, Matthew Barham. All rights reserved.


#include "Gameplay/Components/BattleGridsAbilityComponent.h"
#include "AbilitySystemGlobals.h"

UBattleGridsAbilityComponent::UBattleGridsAbilityComponent()
{
}

UBattleGridsAbilityComponent* UBattleGridsAbilityComponent::GetAbilitySystemComponentFromActor(const AActor* Actor,
                                                                                               bool LookForComponent)
{
	return Cast<UBattleGridsAbilityComponent>(
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}
