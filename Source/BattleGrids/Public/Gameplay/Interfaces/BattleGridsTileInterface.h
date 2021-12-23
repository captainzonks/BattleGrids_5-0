// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleGridsTileInterface.generated.h"

class UBattleGridsGameplayAbility;

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UBattleGridsTileInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface used by Tiles to spawn Actors or Characters
 */
class BATTLEGRIDS_API IBattleGridsTileInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ActivateAbility(TSubclassOf<UBattleGridsGameplayAbility> AbilityToActivate);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SpawnActorOnTile(TSubclassOf<AActor> ActorToSpawn);
};
