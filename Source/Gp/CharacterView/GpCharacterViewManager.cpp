#include "GpCharacterViewManager.h"
#include "CoreMinimal.h"
#include "GpCharacterView.h"
#include "Camera/CameraComponent.h"

AGpCharacterViewManager::AGpCharacterViewManager() : Super()
{
	bFindCameraComponentWhenViewTarget = true;

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BaseCamera"));
	BaseCamera->SetupAttachment(RootComponent);	
}

void AGpCharacterViewManager::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;

	for (TSubclassOf<AGpCharacterView> ViewClass : ViewClasses)
	{
		AGpCharacterView* View = World->SpawnActor<AGpCharacterView>(ViewClass, SpawnInfo);
		View->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

		Views.Add(View);
	}
}

void AGpCharacterViewManager::SetView(const FName& InName, AActor* Target)
{
	for (AGpCharacterView* View : Views)
	{
		if (View->GetViewName().IsEqual(InName))
		{
			if (CurrentView)
			{
				CurrentView->Disable();
			}

			View->Enable(Target, BaseCamera);
			CurrentView = View;

			break;
		}
	}
}