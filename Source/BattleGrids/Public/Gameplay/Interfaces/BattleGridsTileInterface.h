// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleGrids.h"
#include "BattleGridsTileInterface.generated.h"

class ABattleGridsBoard;
class UBattleGridsGameplayAbility;

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
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ActivateAbility(TSubclassOf<UBattleGridsGameplayAbility> AbilityToActivate);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SpawnActorOnTile(TSubclassOf<AActor> ActorToSpawn);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ABattleGridsBoard* GetBoard();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FBattleGridsTileInfo GetTileInfo();
};
