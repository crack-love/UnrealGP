#include "VoxelMeshEdModeToolkit.h"

#include "CoreMinimal.h"
#include "VoxelMeshEdMode.h"
#include "VoxelMeshEdModeWidget.h"
#include "VoxelMesh/VoxelMeshActor.h"

FVoxelMeshEdModeToolkit::FVoxelMeshEdModeToolkit()
{
	SAssignNew(VoxelMeshEdModeWidget, SVoxelMeshEdModeWidget);
}

FName FVoxelMeshEdModeToolkit::GetToolkitFName() const
{
	UE_LOG(LogTemp, Log, TEXT("GetToolkitFName"));

	return FName("VoxelMeshEdModeToolkit");
}

FEdMode* FVoxelMeshEdModeToolkit::GetEditorMode() const
{
	UE_LOG(LogTemp, Log, TEXT("GetEditorMode"));

	return GLevelEditorModeTools().GetActiveMode(FVoxelMeshEdMode::EditorModeID);
}

TSharedPtr<SWidget> FVoxelMeshEdModeToolkit::GetInlineContent() const
{
	UE_LOG(LogTemp, Log, TEXT("GetInlineContent"));

	return VoxelMeshEdModeWidget;
}

void FVoxelMeshEdModeToolkit::OnModeRender(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	/*if (SelectedTarget.IsValid())
	{
		
	}*/
}

bool FVoxelMeshEdModeToolkit::OnModeHandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click)
{
	if (HitProxy)
	{
		if (HitProxy->IsA(HActor::StaticGetType()))
		{
			HActor* hactor = static_cast<HActor*>(HitProxy);
			AVoxelMeshActor* vm = Cast<AVoxelMeshActor, AActor>(hactor->Actor);
			if (vm)
			{
				// Select new actor
				if (vm != SelectedTarget)
				{
					return SelectNewTarget(vm);
				}

				// Click event
				OnClick(vm, Click);
			}
		}
	}

	return false;
}

bool FVoxelMeshEdModeToolkit::SelectNewTarget(AVoxelMeshActor* Target)
{
	if (Target == nullptr)
	{
		SelectedTarget = Target;
		return false;
	}
	else
	{
		SelectedTarget = Target;
		return true;
	}

	return false;
}

void FVoxelMeshEdModeToolkit::OnClick(AVoxelMeshActor* Target, const FViewportClick& Click)
{
	if (Target == nullptr) return;

	if (CurrentToolMode == EToolMode::None)
	{
		return;
	}
	else if (CurrentToolMode == EToolMode::EditVolume)
	{
		auto cursorLoc = Click.GetViewportClient()->GetCursorWorldLocationFromMousePos();
		UE_LOG(LogTemp, Log, TEXT("%s"), *cursorLoc.GetOrigin().ToString());
		
	}
	else if (CurrentToolMode == EToolMode::EditTexture)
	{

	}
}
