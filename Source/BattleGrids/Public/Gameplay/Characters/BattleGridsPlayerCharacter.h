// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperCharacter.h"
#include "BattleGridsPlayerCharacter.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UBattleGridsGameplayAbility;
class UBattleGridsAbilityComponent;

/**
 * BattleGrids Player Character class
 */
UCLASS()
class BATTLEGRIDS_API ABattleGridsPlayerCharacter : public APaperCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABattleGridsPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/**************************
	 *    CLASS OVERRIDES
	 *************************/

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/**************************
	 *    ABILITY SYSTEM
	 *************************/

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void AddStartupGameplayAbilities();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBattleGridsAbilityComponent> AbilitySystemComponent;

	/** Passive gameplay effects applied on creation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	// Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UBattleGridsGameplayAbility>> GameplayAbilities;

	/** If true we have initialized our abilities */
	UPROPERTY()
	uint8 bAbilitiesInitialized:1;
};
