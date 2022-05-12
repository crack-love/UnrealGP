#include "GpCharacterView.h"

#include "Gp/GpLog.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

AGpCharacterView::AGpCharacterView()
{
	bFindCameraComponentWhenViewTarget = true;

	InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComponent"));
}

void AGpCharacterView::Enable(AActor* TargetActor, UCameraComponent* SourceCamera)
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* Controller = World->GetFirstPlayerController())
		{
			Controller->PushInputComponent(InputComponent);
		}
	}
}

void AGpCharacterView::Disable()
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* Controller = World->GetFirstPlayerController())
		{
			Controller->PopInputComponent(InputComponent);
		}
	}
}

const FName& AGpCharacterView::GetViewName()
{
	return ViewName;
}
