// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BattleGridsAbilityComponent.generated.h"

/**
 * BattleGrids Ability System Component
 */
UCLASS()
class BATTLEGRIDS_API UBattleGridsAbilityComponent : public UAbilitySystemComponent	
{
	GENERATED_BODY()

	UBattleGridsAbilityComponent();

	/** Version of function in AbilitySystemGlobals that returns correct type */
	static UBattleGridsAbilityComponent* GetAbilitySystemComponentFromActor(
		const AActor* Actor, bool LookForComponent = false);
};
