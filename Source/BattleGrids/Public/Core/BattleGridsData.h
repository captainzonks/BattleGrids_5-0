// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "BattleGridsData.generated.h"

UENUM(BlueprintType)
enum class EBattleGridsAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel
};

USTRUCT(BlueprintType)
struct FBattleGridsTileInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int X{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Y{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Z{};

	FBattleGridsTileInfo() = default;

	FBattleGridsTileInfo(int const NewX, int const NewY, int const NewZ)
		: X(NewX), Y(NewY), Z(NewZ)
	{
	}
};
