#pragma once

#include "EdMode.h"

class FVoxelMeshEdMode : public FEdMode
{
public:
	static const FEditorModeID EditorModeID;

	// beg FEdMode
	virtual void Enter() override;
	virtual void Exit() override;
	// end FEdMode

	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;

	virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;

	//virtual bool Select(AActor* InActor, bool bInSelected);

	// pointer proxy render
	// Then in cpp file, we use macro IMPLEMENT_HIT_PROXY to implement the proxy. 
	// In Render we simply loops through all ExampleTargetPoint actor and draw all the points 
	// (and a line to the actor itself), we choose a different color if this is the current selected point.
	// We set hit proxy for each point before drawing and clears it immediately afterwards 
	// (this is important so the proxy doesn’t leak through to other draws). 
	// In HandleClick, we test hit proxy and select point if we have a valid hit. 
	// We don’t check mouse button here, so you can select with left/right/middle click.
	// pointer
	// void AddPoint();
	// bool CanAddPoint() const;
	// void RemovePoint();
	// bool CanRemovePoint() const;
	// bool HasValidSelection() const;
	// void SelectPoint(AExampleTargetPoint* actor, int32 index);
	// TWeakObjectPtr<AExampleTargetPoint> currentSelectedTarget;
	// int32 currentSelectedIndex = -1;

	// pointer proxy render
	// Then in cpp file, we use macro IMPLEMENT_HIT_PROXY to implement the proxy. In Render we simply loops through all ExampleTargetPoint actor and draw all the points (and a line to the actor itself), we choose a different color if this is the current selected point. We set hit proxy for each point before drawing and clears it immediately afterwards (this is important so the proxy doesn’t leak through to other draws). In HandleClick, we test hit proxy and select point if we have a valid hit. We don’t check mouse button here, so you can select with left/right/middle click.
	// virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	// virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;

	// pointer transform widget	
	// virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;
	// virtual bool ShowModeWidgets() const override;
	// virtual bool ShouldDrawWidget() const override;
	// virtual bool UsesTransformWidget() const override;
	// virtual FVector GetWidgetLocation() const override;

	// pointer command
	// FExampleEdMode();
	// virtual ~FExampleEdMode() override;
	// TSharedPtr<FUICommandList> ExampleEdModeActions;
	// void MapCommands();
	// virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;
	// TSharedPtr<SWidget> GenerateContextMenu(FEditorViewportClient* InViewportClient) const;

	// other useful overrides
	/*
	virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	virtual bool CapturedMouseMove(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 InMouseX, int32 InMouseY) override;
	virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;
	virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;
	virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;
	virtual void PostUndo() override;
	virtual void ActorsDuplicatedNotify(TArray<AActor*>& PreDuplicateSelection, TArray<AActor*>& PostDuplicateSelection, bool bOffsetLocations) override;
	virtual void ActorMoveNotify() override;
	virtual void ActorSelectionChangeNotify() override;
	virtual void MapChangeNotify() override;
	virtual void SelectionChanged() override;
	*/
};
