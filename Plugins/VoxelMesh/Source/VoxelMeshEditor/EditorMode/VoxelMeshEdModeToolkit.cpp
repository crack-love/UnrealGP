#include "VoxelMeshEdModeToolkit.h"

#include "VoxelMeshEdMode.h"
#include "VoxelMeshEdModeWidget.h"

FVoxelMeshEdModeToolkit::FVoxelMeshEdModeToolkit()
{
	SAssignNew(VoxelMeshEdModeWidget, SVoxelMeshEdModeWidget);
}

FName FVoxelMeshEdModeToolkit::GetToolkitFName() const
{
	return FName("VoxelMeshEdModeToolkit");
}

FEdMode* FVoxelMeshEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FVoxelMeshEdMode::EditorModeID);
}

TSharedPtr<SWidget> FVoxelMeshEdModeToolkit::GetInlineContent() const
{
	return VoxelMeshEdModeWidget;
}
