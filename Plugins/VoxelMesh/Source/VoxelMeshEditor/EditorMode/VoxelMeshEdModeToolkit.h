#pragma once

#include "UnrealEd.h"

class FVoxelMeshEdModeToolkit: public FModeToolkit
{
public:
	FVoxelMeshEdModeToolkit();

	// beg FModeToolkit
	virtual FName GetToolkitFName() const override;

	virtual FEdMode* GetEditorMode() const override;

	virtual TSharedPtr<SWidget> GetInlineContent() const override;
	// end FModeToolkit
	
private:
	TSharedPtr<class SVoxelMeshEdModeWidget> VoxelMeshEdModeWidget;
};
