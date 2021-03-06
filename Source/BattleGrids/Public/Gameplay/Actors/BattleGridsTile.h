// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleGrids.h"
#include "BattleGridsTile.generated.h"

class ABattleGridsBoard;
UCLASS()
class BATTLEGRIDS_API ABattleGridsTile : public AActor, public IAbilitySystemInterface, public IBattleGridsTileInterface
{
	GENERATED_BODY()

public:
	ABattleGridsTile();

	void SetTileInfo(FBattleGridsTileInfo InTileInfo);

	void SetParentBoard(const TObjectPtr<ABattleGridsBoard> InBoard) { ParentBoard = InBoard; }
	TObjectPtr<ABattleGridsBoard> GetParentBoard() const { return ParentBoard; }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**************************
     *    ABILITY SYSTEM
     *************************/

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void AddStartupGameplayAbilities();

private:
	void SpawnActorOnTile(TSubclassOf<AActor> ActorClassToSpawn, const FTransform InTransform) const;

	/**************************
	 *    TILE INTERFACE
	 *************************/

	virtual ABattleGridsBoard* GetBoard_Implementation() override { return ParentBoard; }
	virtual FBattleGridsTileInfo GetTileInfo_Implementation() override { return TileInfo; }

	/**************************
	 *      COMPONENTS
	 *************************/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> SpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBattleGridsAbilityComponent> AbilitySystemComponent;

	/**************************
	 *    VARIABLES
	 *************************/

	/** Passive gameplay effects applied on creation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	// Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UBattleGridsGameplayAbility>> GameplayAbilities;

	/** If true we have initialized our abilities */
	UPROPERTY()
	uint8 bAbilitiesInitialized:1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMesh> TileStaticMesh;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = true))
	FBattleGridsTileInfo TileInfo;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = true))
	TObjectPtr<ABattleGridsBoard> ParentBoard;
};
