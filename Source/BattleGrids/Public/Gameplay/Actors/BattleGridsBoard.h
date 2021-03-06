// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "BattleGridsTile.h"
#include "GameFramework/Actor.h"
#include "BattleGridsBoard.generated.h"

UCLASS()
class BATTLEGRIDS_API ABattleGridsBoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABattleGridsBoard();

	/**
	 * Build out a new grid of tiles.
	 * Will not execute if BoardTiles array is not empty.
	 * @CenteredLocation Center of the board
	 * @X Total rows
	 * @Y Total columns
	 */
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void BuildBoard(const FVector& CenteredLocation, const int X = 8, const int Y = 8);

	/**
	 * Returns an array of tiles in a straight line, depending on X or Y equivalency
	 * @Start Starting coordinates
	 * @End Ending coordinates
	 */
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetLineOfTiles(FVector2D Start, FVector2D End);

	/**
	 * Returns an array of tiles in a square
	 * @Start Starting coordinates
	 * @End Ending coordinates
	 */
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetSquareOfTiles(FVector2D Start, FVector2D End);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	FVector2D BoardSize;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	TArray<TObjectPtr<AActor>> BoardTiles;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSoftClassPtr<ABattleGridsTile> TileClass;
};
