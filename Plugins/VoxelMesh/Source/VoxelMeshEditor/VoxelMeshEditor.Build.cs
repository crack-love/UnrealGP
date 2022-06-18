using UnrealBuildTool;
using System.IO;

public class VoxelMeshEditor : ModuleRules
{
	public VoxelMeshEditor(ReadOnlyTargetRules Target) : base(Target)
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
				"UnrealEd",
				"VoxelMesh",
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
				"ProceduralMeshComponent",
				"VoxelMesh",
			}
		);

		
	}
}
