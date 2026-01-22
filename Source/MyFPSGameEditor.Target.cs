using UnrealBuildTool;
using System.Collections.Generic;

public class MyFPSGameEditorTarget : TargetRules
{
	public MyFPSGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("MyFPSGame");
	}
}