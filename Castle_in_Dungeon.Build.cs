// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Castle_in_Dungeon : ModuleRules
{
	public Castle_in_Dungeon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "MediaAssets", "Core", "CoreUObject", 
			"Engine", "InputCore", "UMG"});

		PublicDependencyModuleNames.AddRange(new string[]{
			 "AIModule", "GameplayTasks", "NavigationSystem"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "MediaAssets" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

