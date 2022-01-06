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
struct BATTLEGRIDS_API FBattleGridsTileInfo
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

UENUM(BlueprintType)
enum class EBuildMode : uint8
{
	Straight,
	Box
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildModeChanged, EBuildMode, BuildMode);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildModeChangedNative, EBuildMode);
