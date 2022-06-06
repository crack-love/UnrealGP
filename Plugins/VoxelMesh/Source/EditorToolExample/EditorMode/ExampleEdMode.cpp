#include "ExampleEdMode.h"
#include "ScopedTransaction.h"
#include "ExampleEdModeToolkit.h"

#include "Toolkits/ToolkitManager.h"

IMPLEMENT_HIT_PROXY(HExamplePointProxy, HHitProxy);

const FEditorModeID FExampleEdMode::EM_Example(TEXT("EM_Example"));

void FExampleEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	const FColor normalColor(200, 200, 200);
	const FColor selectedColor(255, 128, 0);

	UWorld* World = GetWorld();
	for (TActorIterator<AExampleTargetPoint> It(World); It; ++It)
	{
		AExampleTargetPoint* actor = (*It);
		if (actor)
		{
			FVector actorLoc = actor->GetActorLocation();
			for (int i = 0; i < actor->Points.Num(); ++i)
			{
				bool bSelected = (actor == currentSelectedTarget && i == currentSelectedIndex);
				const FColor& color = bSelected ? selectedColor : normalColor;
				// set hit proxy and draw
				PDI->SetHitProxy(new HExamplePointProxy(actor, i));
				PDI->DrawPoint(actor->Points[i], color, 15.f, SDPG_Foreground);
				PDI->DrawLine(actor->Points[i], actorLoc, color, SDPG_Foreground);
				PDI->SetHitProxy(NULL);
			}
		}
	}

	FEdMode::Render(View, Viewport, PDI);
}

bool FExampleEdMode::HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click)
{
	bool isHandled = false;

	if (HitProxy)
	{
		if (HitProxy->IsA(HExamplePointProxy::StaticGetType()))
		{
			isHandled = true;
			HExamplePointProxy* examplePointProxy = (HExamplePointProxy*)HitProxy;
			AExampleTargetPoint* actor = Cast<AExampleTargetPoint>(examplePointProxy->RefObject);
			int32 index = examplePointProxy->Index;
			if (actor && index >= 0 && index < actor->Points.Num())
			{
				SelectPoint(actor, index);
			}
		}
	}

	return isHandled;
}

void FExampleEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid())
	{
		Toolkit = MakeShareable(new FExampleEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
	
	// reset pointer
	currentSelectedTarget = nullptr;
	currentSelectedIndex = -1;
}

void FExampleEdMode::Exit()
{
	FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
	Toolkit.Reset();

	FEdMode::Exit();
}

AExampleTargetPoint* GetSelectedTargetPointActor()
{
	TArray<UObject*> selectedObjects;
	GEditor->GetSelectedActors()->GetSelectedObjects(selectedObjects);
	if (selectedObjects.Num() == 1)
	{
		return Cast<AExampleTargetPoint>(selectedObjects[0]);
	}
	return nullptr;
}

// Note that we put FScopedTransaction, and called Modify() function whenever we modify data we need to save. This will make sure undo/redo is properly handled.
void FExampleEdMode::AddPoint()
{
	AExampleTargetPoint* actor = GetSelectedTargetPointActor();
	if (actor)
	{
		const FScopedTransaction Transaction(FText::FromString("Add Point"));

		// add new point, slightly in front of camera
		FEditorViewportClient* client = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
		FVector newPoint = client->GetViewLocation() + client->GetViewRotation().Vector() * 50.f;
		actor->Modify();
		actor->Points.Add(newPoint);
		// auto select this new point
		SelectPoint(actor, actor->Points.Num() - 1);
	}
}

bool FExampleEdMode::CanAddPoint() const
{
	return GetSelectedTargetPointActor() != nullptr;
}

void FExampleEdMode::RemovePoint()
{
	if (HasValidSelection())
	{
		const FScopedTransaction Transaction(FText::FromString("Remove Point"));

		currentSelectedTarget->Modify();
		currentSelectedTarget->Points.RemoveAt(currentSelectedIndex);
		// deselect the point
		SelectPoint(nullptr, -1);
	}
}

bool FExampleEdMode::CanRemovePoint() const
{
	return HasValidSelection();
}

bool FExampleEdMode::HasValidSelection() const
{
	return currentSelectedTarget.IsValid() && currentSelectedIndex >= 0 && currentSelectedIndex < currentSelectedTarget->Points.Num();
}

void FExampleEdMode::SelectPoint(AExampleTargetPoint* actor, int32 index)
{
	currentSelectedTarget = actor;
	currentSelectedIndex = index;

	// select this actor only
	if (currentSelectedTarget.IsValid())
	{
		GEditor->SelectNone(true, true);
		GEditor->SelectActor(currentSelectedTarget.Get(), true, true);
	}
}
