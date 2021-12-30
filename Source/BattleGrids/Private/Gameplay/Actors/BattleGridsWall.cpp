// © 2021, Matthew Barham. All rights reserved.


#include "Gameplay/Actors/BattleGridsWall.h"

ABattleGridsWall::ABattleGridsWall()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent.Get());
	
}

void ABattleGridsWall::BeginPlay()
{
	Super::BeginPlay();
	
}
