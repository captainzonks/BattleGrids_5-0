// © 2021, Matthew Barham. All rights reserved.


#include "Gameplay/Actors/BattleGridsBoard.h"

#include "Gameplay/Actors/BattleGridsTile.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ABattleGridsBoard::ABattleGridsBoard()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABattleGridsBoard::BuildBoard_Implementation(FVector const& CenteredLocation, int const& X, int const& Y)
{
	// Do not execute if BoardTiles contains Tiles already
	if (BoardTiles.Num() == 0)
	{
		BoardSize.X = X;
		BoardSize.Y = Y;

		// 2D Grid Execution Macro, rewritten in C++
		for (auto OuterIndex{0}; OuterIndex <= Y - 1; ++OuterIndex)
		{
			for (auto InnerIndex{0}; InnerIndex <= X - 1; ++InnerIndex)
			{
				float constexpr SectorSize = 100.f;
				// Prepare a fresh Transform
				FVector SpawnLocation =
					FVector(static_cast<float>(InnerIndex) - static_cast<float>(X) / 2.f,
					        static_cast<float>(OuterIndex) - static_cast<float>(Y) / 2.f,
					        0.f)
					* SectorSize
					* 1.f
					+ CenteredLocation;

				FTransform SpawnTransform;
				SpawnTransform.SetLocation(SpawnLocation);

				if (TileClass)
				{
					auto TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
						this, TileClass.LoadSynchronous(),
						SpawnTransform);

					ABattleGridsTile* Tile = Cast<ABattleGridsTile>(TileToSpawn);
					if (Tile)
					{
						Tile->SetTileInfo(FBattleGridsTileInfo(InnerIndex, OuterIndex, 0));
					}
					
					TileToSpawn->FinishSpawning(SpawnTransform);
					// Spawn the new Tile and add it to the board's array
					BoardTiles.Add(TileToSpawn);
					TileToSpawn->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
				}
			}
		}
	}
}

void ABattleGridsBoard::BeginPlay()
{
	Super::BeginPlay();
}

void ABattleGridsBoard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleGridsBoard, BoardTiles);
	DOREPLIFETIME(ABattleGridsBoard, BoardSize);
}
