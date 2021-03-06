// © 2021, Matthew Barham. All rights reserved.


#include "Gameplay/Core/BattleGridsGamePlayerController.h"

#define STRAIGHT FString("Straight")
#define BOX FString("Box")

ABattleGridsGamePlayerController::ABattleGridsGamePlayerController()
{
}

void ABattleGridsGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABattleGridsGamePlayerController::ChangeBuildMode(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem.Equals(STRAIGHT))
	{
		BuildMode = EBuildMode::Straight;
	}
	if (SelectedItem.Equals(BOX))
	{
		BuildMode = EBuildMode::Box;
	}
}
