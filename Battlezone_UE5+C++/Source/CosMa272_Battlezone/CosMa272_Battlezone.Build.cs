// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CosMa272_Battlezone : ModuleRules
{
	public CosMa272_Battlezone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG"});

        PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
    }
}
