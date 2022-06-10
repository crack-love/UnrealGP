#include "VoxelMeshEditorModule.h"

#include "EditorMode/VoxelMeshEdModeEntry.h"

// TSharedRef<FWorkspaceItem> FVoxelMeshEditorModule::MenuRoot =
// 	FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

void FVoxelMeshEditorModule::StartupModule()
{

	
	FListenableModule::StartupModule();
}

void FVoxelMeshEditorModule::ShutdownModule()
{
	
	
	FListenableModule::ShutdownModule();
}

void FVoxelMeshEditorModule::AddModuleListeners()
{
	ModuleListeners.Add(MakeShareable(new FVoxelMeshEdModeEntry));
}


IMPLEMENT_MODULE(FVoxelMeshEditorModule, VoxelMeshEditor)
