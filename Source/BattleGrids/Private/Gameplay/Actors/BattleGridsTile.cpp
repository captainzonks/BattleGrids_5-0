// © 2021, Matthew Barham. All rights reserved.


#include "Gameplay/Actors/BattleGridsTile.h"

#include "Net/UnrealNetwork.h"

ABattleGridsTile::ABattleGridsTile()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent.Get());

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(StaticMeshComponent.Get());

	SpawnPoint->SetRelativeLocation(FVector(0.f, 0.f, 25.f));

	AbilitySystemComponent = CreateDefaultSubobject<UBattleGridsAbilityComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void ABattleGridsTile::SetTileInfo(const FBattleGridsTileInfo InTileInfo)
{
	TileInfo = InTileInfo;
}

void ABattleGridsTile::SpawnActorOnTile(const TSubclassOf<AActor> ActorClassToSpawn, const FTransform InTransform) const
{
	const auto SpawnActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ActorClassToSpawn, InTransform);
	SpawnActor->FinishSpawning(InTransform);
}

void ABattleGridsTile::BeginPlay()
{
	Super::BeginPlay();

	AddStartupGameplayAbilities();
}

void ABattleGridsTile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleGridsTile, ParentBoard);
	DOREPLIFETIME(ABattleGridsTile, TileInfo);
}

UAbilitySystemComponent* ABattleGridsTile::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void ABattleGridsTile::AddStartupGameplayAbilities()
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
