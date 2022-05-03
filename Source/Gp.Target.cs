using UnrealBuildTool;
using System.Collections.Generic;

public class GpTarget : TargetRules
{
	public GpTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Gp");
	}
}
