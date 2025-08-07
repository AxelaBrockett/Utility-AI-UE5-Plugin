// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AxelaJimbobUtilityAI : ModuleRules
{
	public AxelaJimbobUtilityAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"AxelaJimbobUtilityAI",
			"AxelaJimbobUtilityAI/Variant_Strategy",
			"AxelaJimbobUtilityAI/Variant_TwinStick",
			"AxelaJimbobUtilityAI/Variant_TwinStick/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
