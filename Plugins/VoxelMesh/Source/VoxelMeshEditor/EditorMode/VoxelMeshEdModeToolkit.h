#pragma once

#include "UnrealEd.h"

enum EToolMode
{
	None = 0,
	EditVolume,
	EditTexture,
};

// �޽� �ٿ���� ��
// ���ؽ� ���� (����, �ؽ���)
class FVoxelMeshEdModeToolkit: public FModeToolkit
{
	friend class SVoxelMeshEdModeWidget;

public:
	FVoxelMeshEdModeToolkit();

	// beg FModeToolkit
	virtual FName GetToolkitFName() const override;

	virtual FEdMode* GetEditorMode() const override;

	virtual TSharedPtr<SWidget> GetInlineContent() const override;
	// end FModeToolkit
	
	void OnModeRender(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);

	bool OnModeHandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click);

private:
	bool SelectNewTarget(class AVoxelMeshActor* Target);
	void OnClick(class AVoxelMeshActor* Target, const FViewportClick& Click);

	TSharedPtr<class SVoxelMeshEdModeWidget> VoxelMeshEdModeWidget;
	TWeakObjectPtr<class AVoxelMeshActor> SelectedTarget;
	EToolMode CurrentToolMode;
	float ToolStrength;
	float ToolRange;
};
