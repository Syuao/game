using UnrealBuildTool;
using System.Collections.Generic;

public class MyFPSGameTarget : TargetRules
{
	public MyFPSGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("MyFPSGame");
	}
}