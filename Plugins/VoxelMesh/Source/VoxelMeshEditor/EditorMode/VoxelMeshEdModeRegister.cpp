#include "VoxelMeshEdModeRegister.h"

#include "UnrealEd.h"
#include "VoxelMeshEdMode.h"

#define IMAGE_BRUSH(RelativePath, ...) \
	FSlateImageBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

void FVoxelMeshEdModeRegister::OnStartupModule()
{
	RegisterStyleSet();
	RegisterEditorMode();
}

void FVoxelMeshEdModeRegister::OnShutdownModule()
{
	UnregisterStyleSet();
	UnregisterEditorMode();
}

void FVoxelMeshEdModeRegister::RegisterStyleSet()
{
	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet("VoxelMeshEdModeStyleSet"));
	{
		// Const icon sizes
		const FVector2D Icon20x20(20.0f, 20.0f);
		const FVector2D Icon40x40(40.0f, 40.0f);
		
		// set path
		StyleSet->SetContentRoot(FPaths::ProjectPluginsDir() /
			TEXT("VoxelMesh/Content/EditorResources"));
		StyleSet->SetCoreContentRoot(FPaths::ProjectPluginsDir() /
			TEXT("VoxelMesh/Content/EditorResources"));
	
		// set image
		StyleSet->Set("IconVMEdMode",
			new IMAGE_BRUSH(TEXT("IconExampleEditorMode"), Icon40x40));
		StyleSet->Set("IconVMEdMode.Small",
			new IMAGE_BRUSH(TEXT("IconExampleEditorMode"), Icon20x20));
	}
	
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FVoxelMeshEdModeRegister::UnregisterStyleSet()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

void FVoxelMeshEdModeRegister::RegisterEditorMode() const
{
	FEditorModeID ModeID = FVoxelMeshEdMode::EditorModeID;
	FText ModeName = FText::FromString(TEXT("VMEditorMode"));
	FSlateIcon Icon(StyleSet->GetStyleSetName(),
		"IconVMEdMode",
		"IconVMEdMode.Small");  
	
	FEditorModeRegistry::Get().RegisterMode<FVoxelMeshEdMode>(
		MoveTemp(ModeID),
		MoveTemp(ModeName),
		MoveTemp(Icon),
		true,
		500);
}

void FVoxelMeshEdModeRegister::UnregisterEditorMode() const
{
	FEditorModeRegistry::Get().UnregisterMode(FVoxelMeshEdMode::EditorModeID);
}

#undef IMAGE_BRUSH
