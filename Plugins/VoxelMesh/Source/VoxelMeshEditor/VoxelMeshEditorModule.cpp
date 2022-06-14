#include "VoxelMeshEditorModule.h"

#include "EditorMode/VoxelMeshEdModeRegister.h"

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
	ModuleListeners.Add(MakeShareable(new FVoxelMeshEdModeRegister));
}


IMPLEMENT_MODULE(FVoxelMeshEditorModule, VoxelMeshEditor)
