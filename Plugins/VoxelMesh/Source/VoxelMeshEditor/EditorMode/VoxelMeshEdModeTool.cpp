#include "VoxelMeshEdModeTool.h"

#include "UnrealEd.h"
#include "VoxelMeshEdMode.h"

#define IMAGE_BRUSH(RelativePath, ...) \
	FSlateImageBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<FSlateStyleSet> FVoxelMeshEdModeTool::StyleSet = nullptr;

void FVoxelMeshEdModeTool::OnStartupModule()
{
	RegisterStyleSet();
	RegisterEditorMode();
}

void FVoxelMeshEdModeTool::OnShutdownModule()
{
	UnregisterStyleSet();
	UnregisterEditorMode();
}

// FTabToolInitParam FVoxelMeshEdModeTool::GetInitParams()
// {
// 	FTabToolInitParam Init
// 	{
// 		//nullptr,
// 		FName(TEXT("")),
// 		FText::FromString(TEXT("")),
// 		FText::FromString(TEXT("")),
// 	};
// 	
// 	return Init;
// }

void FVoxelMeshEdModeTool::RegisterStyleSet()
{
	// Const icon sizes
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet("VoxelMeshEdModeToolStyle"));
	StyleSet->SetContentRoot(FPaths::ProjectPluginsDir() /
		TEXT("VoxelMesh/Content/EditorResources"));
	StyleSet->SetCoreContentRoot(FPaths::ProjectPluginsDir() /
		TEXT("VoxelMesh/Content/EditorResources"));

	UE_LOG(LogTemp, Log, TEXT("%s"), *(FPaths::ProjectPluginsDir() /
		TEXT("VoxelMesh/Content/EditorResources")));
	
	// Spline editor
	{
		StyleSet->Set("VoxelMeshEdMode",
			new IMAGE_BRUSH(TEXT("IconExampleEditorMode"), Icon40x40));
		StyleSet->Set("VoxelMeshEdMode.Small",
			new IMAGE_BRUSH(TEXT("IconExampleEditorMode"), Icon20x20));
	}

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FVoxelMeshEdModeTool::UnregisterStyleSet()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

void FVoxelMeshEdModeTool::RegisterEditorMode()
{
	FEditorModeRegistry::Get().RegisterMode<FVoxelMeshEdMode>(
		FVoxelMeshEdMode::EM_VoxelMesh,
		FText::FromString("Example Editor Mode"),
		FSlateIcon(StyleSet->GetStyleSetName(),
			"VoxelMeshEdMode",
			"VoxelMeshEdMode.Small"),
		true, 500
		);
}

void FVoxelMeshEdModeTool::UnregisterEditorMode()
{
	FEditorModeRegistry::Get().UnregisterMode(FVoxelMeshEdMode::EM_VoxelMesh);
}

#undef IMAGE_BRUSH
