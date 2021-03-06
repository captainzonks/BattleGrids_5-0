// © 2021, Matthew Barham. All rights reserved.


#include "Gameplay/Actors/BattleGridsBoard.h"

#include "Gameplay/Actors/BattleGridsTile.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ABattleGridsBoard::ABattleGridsBoard()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABattleGridsBoard::BuildBoard_Implementation(const FVector& CenteredLocation, const int X, const int Y)
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

				if (TileClass.LoadSynchronous())
				{
					auto TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
						this, TileClass.LoadSynchronous(),
						SpawnTransform);

					ABattleGridsTile* Tile = Cast<ABattleGridsTile>(TileToSpawn);
					if (Tile)
					{
						Tile->SetTileInfo(FBattleGridsTileInfo(OuterIndex, InnerIndex, 0));
						Tile->SetParentBoard(this);
					}

					TileToSpawn->FinishSpawning(SpawnTransform);
					// Spawn the new Tile and add it to the board's array
					BoardTiles.Add(TileToSpawn);

					// Attach to Board
					TileToSpawn->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
				}
			}
		}
	}
}

TArray<AActor*> ABattleGridsBoard::GetLineOfTiles(FVector2D Start, FVector2D End)
{
	TArray<AActor*> Array;

	if (Start.X > BoardSize.X || Start.X < 0 || Start.X > BoardSize.X || Start.X < 0) return Array;
	if (Start.Y > BoardSize.Y || Start.Y < 0 || Start.Y > BoardSize.Y || Start.Y < 0) return Array;

	if (End.X == BoardSize.X)
		End.X--;
	if (End.Y == BoardSize.Y)
		End.Y--;

	if (Start.Y == End.Y && Start.X != End.X)
	{
		for (size_t Index{static_cast<size_t>(Start.X)}; Index <= End.X; ++Index)
		{
			Array.AddUnique(BoardTiles[BoardSize.Y * Index + Start.Y]);
		}
	}

	if (Start.X == End.X && Start.Y != End.Y)
	{
		for (size_t Index{static_cast<size_t>(Start.Y)}; Index <= End.Y; ++Index)
		{
			Array.AddUnique(BoardTiles[BoardSize.X * Start.X + Index]);
		}
	}

	return Array;
}

TArray<AActor*> ABattleGridsBoard::GetSquareOfTiles(FVector2D Start, FVector2D End)
{
	TArray<AActor*> Array;

	if (Start.X > BoardSize.X || Start.X < 0 || End.X > BoardSize.X || End.X < 0) return Array;
	if (Start.Y > BoardSize.Y || Start.Y < 0 || End.Y > BoardSize.Y || End.Y < 0) return Array;

	if (End.X == BoardSize.X)
		End.X--;
	if (End.Y == BoardSize.Y)
		End.Y--;

	for (size_t Index{static_cast<size_t>(Start.X)}; Index <= End.X; ++Index)
	{
		Array.AddUnique(BoardTiles[BoardSize.Y * Index + Start.Y]);
		Array.AddUnique(BoardTiles[BoardSize.Y * Index + End.Y]);
	}

	for (size_t Index{static_cast<size_t>(Start.Y)}; Index <= End.Y; ++Index)
	{
		Array.AddUnique(BoardTiles[BoardSize.X * Start.X + Index]);
		Array.AddUnique(BoardTiles[BoardSize.X * End.X + Index]);
	}

	return Array;
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
