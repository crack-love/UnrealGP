using UnrealBuildTool;
using System.Collections.Generic;

public class GpEditorTarget : TargetRules
{
	public GpEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Gp");
	}
}
