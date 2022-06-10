#include "VoxelMeshEdMode.h"

#include "VoxelMeshEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"

const FEditorModeID FVoxelMeshEdMode::EditorModeID(TEXT("EM_VoxelMesh"));

void FVoxelMeshEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid())
	{
		Toolkit = MakeShareable(new FVoxelMeshEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FVoxelMeshEdMode::Exit()
{
	FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
	Toolkit.Reset();

	FEdMode::Exit();
}
