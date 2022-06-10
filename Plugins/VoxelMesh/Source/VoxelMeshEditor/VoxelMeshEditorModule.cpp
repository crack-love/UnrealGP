#include "VoxelMeshEditorModule.h"

#include "EditorMode/VoxelMeshEdModeTool.h"

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
	ModuleListeners.Add(MakeShareable(new FVoxelMeshEdModeTool));
}


IMPLEMENT_GAME_MODULE(FVoxelMeshEditorModule, VoxelMeshEditor)
