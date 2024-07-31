// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Mutliplayer_Tutorial : ModuleRules
{
	public Mutliplayer_Tutorial(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
