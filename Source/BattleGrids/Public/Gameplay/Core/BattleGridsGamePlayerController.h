// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/BattleGridsData.h"
#include "Core/BattleGridsPlayerController.h"
#include "BattleGridsGamePlayerController.generated.h"

/**
 * BattleGrids Gameplay Player Controller class
 */
UCLASS()
class BATTLEGRIDS_API ABattleGridsGamePlayerController : public ABattleGridsPlayerController
{
	GENERATED_BODY()
public:
	ABattleGridsGamePlayerController();

	UFUNCTION()
	void ChangeBuildMode(FString SelectedItem, ESelectInfo::Type SelectionType);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = true))
	EBuildMode BuildMode{EBuildMode::Straight};
};
