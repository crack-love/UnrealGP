using UnrealBuildTool;
using System.IO;

public class EditorTool : ModuleRules
{
	public EditorTool(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePaths.AddRange(new string[] { });

        PrivateIncludePaths.AddRange(new string[] { });

        PublicDependencyModuleNames.AddRange(
	        new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                //"UMG",
                "UnrealEd",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "SlateCore",
                "Slate",
                "UnrealEd",
                "EditorStyle",
                "EditorFramework",
                "InputCore",
            }
        );
    }
}
