#pragma once

#include "VoxelMeshEditor/ListenableModule.h"

class FVoxelMeshEdModeRegister : public IModuleListener
{
public:
	virtual void OnStartupModule() override;
	
	virtual void OnShutdownModule() override;

private:
	TSharedPtr<FSlateStyleSet> StyleSet;
	
	void RegisterStyleSet();
	void UnregisterStyleSet();
	void RegisterEditorMode() const;
	void UnregisterEditorMode() const;
};
