// © 2021, Matthew Barham. All rights reserved.


#include "Gameplay/Characters/BattleGridsPlayerCharacter.h"
#include "BattleGrids.h"

ABattleGridsPlayerCharacter::ABattleGridsPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UBattleGridsAbilityComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void ABattleGridsPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABattleGridsPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server GAS init
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}

void ABattleGridsPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	// called in SetupPlayerInputComponent() for redundancy
	if (AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			"Confirm",
			"Cancel",
			"EBattleGridsAbilityInputID",
			static_cast<int32>(EBattleGridsAbilityInputID::Confirm),
			static_cast<int32>(EBattleGridsAbilityInputID::Cancel));
	
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

UAbilitySystemComponent* ABattleGridsPlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void ABattleGridsPlayerCharacter::AddStartupGameplayAbilities()
{
	check(AbilitySystemComponent);

	if (GetLocalRole() == ROLE_Authority && !bAbilitiesInitialized)
	{
		// Grant abilities, but only on the server	
		for (TSubclassOf<UBattleGridsGameplayAbility>& StartupAbility : GameplayAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		}

		// Now apply passives
		for (const TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);
		
			FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(
				GameplayEffect, 1, EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*NewHandle.Data.Get(), AbilitySystemComponent);
			}
		}

		bAbilitiesInitialized = true;
	}
}

void ABattleGridsPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// called in OnRep_PlayerState() for redundancy
	if (AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			"Confirm",
			"Cancel",
			"EBattleGridsAbilityInputID",
			static_cast<int32>(EBattleGridsAbilityInputID::Confirm),
			static_cast<int32>(EBattleGridsAbilityInputID::Cancel));
	
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}
