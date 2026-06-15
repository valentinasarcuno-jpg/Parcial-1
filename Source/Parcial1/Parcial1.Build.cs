// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Parcial1 : ModuleRules
{
	public Parcial1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Parcial1",
			"Parcial1/Variant_Platforming",
			"Parcial1/Variant_Platforming/Animation",
			"Parcial1/Variant_Combat",
			"Parcial1/Variant_Combat/AI",
			"Parcial1/Variant_Combat/Animation",
			"Parcial1/Variant_Combat/Gameplay",
			"Parcial1/Variant_Combat/Interfaces",
			"Parcial1/Variant_Combat/UI",
			"Parcial1/Variant_SideScrolling",
			"Parcial1/Variant_SideScrolling/AI",
			"Parcial1/Variant_SideScrolling/Gameplay",
			"Parcial1/Variant_SideScrolling/Interfaces",
			"Parcial1/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
