// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BattleGrids : ModuleRules
{
	public BattleGrids(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		// Core
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		// Paper2D
		PublicDependencyModuleNames.AddRange(new string[] { "Paper2D" });

		// Gameplay Ability System
		PublicDependencyModuleNames.AddRange(new string[] {"GameplayAbilities", "GameplayTags", "GameplayTasks"});

		// Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Online
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
