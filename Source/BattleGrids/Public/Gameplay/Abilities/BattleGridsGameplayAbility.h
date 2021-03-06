// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BattleGrids.h"
#include "Abilities/GameplayAbility.h"
#include "BattleGridsGameplayAbility.generated.h"

/**
 * BattleGrids parent Gameplay Ability class
 */
UCLASS()
class BATTLEGRIDS_API UBattleGridsGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBattleGridsGameplayAbility();

	// Abilities will activate when input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EBattleGridsAbilityInputID AbilityInputID{EBattleGridsAbilityInputID::None};
};
