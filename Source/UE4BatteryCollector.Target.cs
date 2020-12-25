// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UE4BatteryCollectorTarget : TargetRules
{
	public UE4BatteryCollectorTarget(TargetInfo Target): base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("UE4BatteryCollector");
	}

	// //
	// // TargetRules interface.
	// //

	// public override void SetupBinaries(
	// 	TargetInfo Target,
	// 	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	// 	ref List<string> OutExtraModuleNames
	// 	)
	// {
	// 	OutExtraModuleNames.Add("UE4BatteryCollector");
	// }
}
