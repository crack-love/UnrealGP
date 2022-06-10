#pragma once

#include "VoxelMeshEditor/ListenableModule.h"

class FVoxelMeshEdModeTool : public IModuleListener
{
public:
	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	// 	
// protected:
// 	virtual FTabToolInitParam GetInitParams() override;

private:
	static TSharedPtr<FSlateStyleSet > StyleSet;
	
	void RegisterStyleSet();
	void UnregisterStyleSet();
	void RegisterEditorMode();
	void UnregisterEditorMode();
};
