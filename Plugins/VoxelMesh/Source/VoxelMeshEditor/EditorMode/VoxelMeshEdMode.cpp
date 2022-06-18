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

void FVoxelMeshEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	auto VmTk = static_cast<FVoxelMeshEdModeToolkit*>(Toolkit.Get());
	if (VmTk)
	{
		VmTk->OnModeRender(View, Viewport, PDI);
	}
}

bool FVoxelMeshEdMode::HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click)
{
	auto VmTk = static_cast<FVoxelMeshEdModeToolkit*>(Toolkit.Get());
	if (VmTk)
	{
		return VmTk->OnModeHandleClick(InViewportClient, HitProxy, Click);
	}
	return false;
}

//bool FVoxelMeshEdMode::Select(AActor* InActor, bool bInSelected)
//{
//	/*auto VmTk = static_cast<FVoxelMeshEdModeToolkit*>(Toolkit.Get());
//	if (VmTk)
//	{
//		return VmTk->OnModeSelect(InActor, bInSelected);
//	}*/
//	return false;
//}

//RendeR()
//{
//	ToolKit.Render();
//}
//
//handleclick
//{
//
//}