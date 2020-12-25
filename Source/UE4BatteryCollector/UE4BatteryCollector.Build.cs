// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE4BatteryCollector : ModuleRules
{
	public UE4BatteryCollector(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG" });

        PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});

    }
}
