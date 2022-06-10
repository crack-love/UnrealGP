#pragma once

#include "UnrealEd.h"
#include "VoxelMeshEdMode.h"
#include "VoxelMeshEdModeWidget.h"

class FVoxelMeshEdModeToolkit: public FModeToolkit
{
public:
	FVoxelMeshEdModeToolkit()
	{
		SAssignNew(VoxelMeshEdModeWidget, SVoxelMeshEdModeWidget);
	}

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override { return FName("ExampleEdMode"); }
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("BuilderModeToolkit", "DisplayName", "Builder"); }
	
	virtual class FEdMode* GetEditorMode() const override
	{
		return GLevelEditorModeTools().GetActiveMode(FVoxelMeshEdMode::EM_VoxelMesh);
	}
	
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return VoxelMeshEdModeWidget; }

private:
	TSharedPtr<SVoxelMeshEdModeWidget> VoxelMeshEdModeWidget;
};
