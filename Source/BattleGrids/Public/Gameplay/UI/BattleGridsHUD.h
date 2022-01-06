// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleGrids/Public/Core/BattleGridsData.h"
#include "BattleGridsHUD.generated.h"

class ABattleGridsGamePlayerController;
class UComboBoxString;

/**
 * BattleGrids HUD for gameplay
 */
UCLASS()
class BATTLEGRIDS_API UBattleGridsHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UBattleGridsHUD(const FObjectInitializer& ObjectInitializer);

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ChangeBuildMode(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UComboBoxString> BuildModeMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))
	TObjectPtr<ABattleGridsGamePlayerController> GamePlayerControllerReference;

	FOnBuildModeChanged OnBuildModeChanged;
	FOnBuildModeChangedNative OnBuildModeChangedNative;
};
