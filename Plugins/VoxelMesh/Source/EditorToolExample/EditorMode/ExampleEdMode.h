#pragma once
#include "EditorModes.h"
#include "EdMode.h"
#include "ExampleTargetPoint.h"

struct HExamplePointProxy : public HHitProxy
{
	DECLARE_HIT_PROXY();

	HExamplePointProxy(UObject* InRefObject, int32 InIndex)
		: HHitProxy(HPP_UI), RefObject(InRefObject), Index(InIndex)
	{}

	UObject* RefObject;
	int32 Index;
};

class FExampleEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_Example;

	// FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;

	// pointer
	void AddPoint();
	bool CanAddPoint() const;
	void RemovePoint();
	bool CanRemovePoint() const;
	bool HasValidSelection() const;
	void SelectPoint(AExampleTargetPoint* actor, int32 index);
	TWeakObjectPtr<AExampleTargetPoint> currentSelectedTarget;
	int32 currentSelectedIndex = -1;

	// pointer proxy render
	// Then in cpp file, we use macro IMPLEMENT_HIT_PROXY to implement the proxy. In Render we simply loops through all ExampleTargetPoint actor and draw all the points (and a line to the actor itself), we choose a different color if this is the current selected point. We set hit proxy for each point before drawing and clears it immediately afterwards (this is important so the proxy doesn’t leak through to other draws). In HandleClick, we test hit proxy and select point if we have a valid hit. We don’t check mouse button here, so you can select with left/right/middle click.
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;


};
