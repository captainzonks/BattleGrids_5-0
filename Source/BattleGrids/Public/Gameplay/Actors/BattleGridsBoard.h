// © 2021, Matthew Barham. All rights reserved.

#pragma once

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

	/* Build out a new grid of tiles.
	 * Will not execute if BoardTiles array is not empty.
	 */
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void BuildBoard(FVector const& CenteredLocation, int const& X, int const& Y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Config")
	FVector2D BoardSize;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Config")
	TArray<TObjectPtr<AActor>> BoardTiles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSoftClassPtr<ABattleGridsTile> TileClass;
};
