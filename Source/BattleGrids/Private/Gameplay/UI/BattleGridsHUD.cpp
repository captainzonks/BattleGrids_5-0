// © 2021, Matthew Barham. All rights reserved.


#include "Gameplay/UI/BattleGridsHUD.h"

#include "Components/ComboBoxString.h"
#include "Gameplay/Core/BattleGridsGamePlayerController.h"

#define STRAIGHT FString("Straight")
#define BOX FString("Box")

UBattleGridsHUD::UBattleGridsHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UBattleGridsHUD::NativeConstruct()
{
	Super::NativeConstruct();

	BuildModeMenu.Get()->AddOption(STRAIGHT);
	BuildModeMenu.Get()->AddOption(BOX);

	BuildModeMenu->OnSelectionChanged.AddDynamic(this, &UBattleGridsHUD::ChangeBuildMode);
}

void UBattleGridsHUD::ChangeBuildMode(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	GamePlayerControllerReference.Get()->ChangeBuildMode(SelectedItem, SelectionType);
}

