// © 2021, Matthew Barham. All rights reserved.


#include "Gameplay/Actors/BattleGridsTile.h"

ABattleGridsTile::ABattleGridsTile()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(StaticMeshComponent);

	SpawnPoint->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
}

void ABattleGridsTile::BeginPlay()
{
	Super::BeginPlay();
	
}
