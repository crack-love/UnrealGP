// #include "GpCharacterViewManager.h"
// #include "CoreMinimal.h"
// #include "GpCharacterView.h"
// #include "Camera/CameraActor.h"
// #include "Camera/CameraComponent.h"
//
// AGpCharacterViewManager::AGpCharacterViewManager() : Super()
// {
// 	SetReplicates(false);
// }
//
// void AGpCharacterViewManager::PostInitializeComponents()
// {
// 	Super::PostInitializeComponents();
//
// 	GenerateBaseCamera();
// 	GenerateViews();
//
// 	Controller = Cast<APlayerController>(GetOwner());	
// }
//
// void AGpCharacterViewManager::SetView(const FName& ViewName, AActor* Target)
// {
// 	for (AGpCharacterView* View : Views)
// 	{
// 		if (View->IsMatchViewName(ViewName))
// 		{
// 			if (CurrentView)
// 			{
// 				CurrentView->Disable();
// 			}
//
// 			View->Enable(Target, BaseCamera);
// 			CurrentView = View;
//
// 			break;
// 		}
// 	}
// }
//
// void AGpCharacterViewManager::GenerateBaseCamera()
// {
// 	if (!BaseCameraClass)
// 	{
// 		BaseCameraClass = ACameraActor::StaticClass();
// 		UE_LOG(LogTemp, Log, TEXT("Using Default Static Class"));
// 	}
//
// 	// spawn
// 	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();
// 	//SpawnInfo.Name = TEXT("CharacterViewManagerBaseCamera");
// 	SpawnInfo.ObjectFlags |= RF_Transient;
// 	BaseCamera = GetWorld()->SpawnActor<ACameraActor>(BaseCameraClass, SpawnInfo);
// 	BaseCamera->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
// }
//
// void AGpCharacterViewManager::GenerateViews()
// {
// 	// spawn
// 	UWorld* World = GetWorld();
// 	FActorSpawnParameters SpawnInfo;
// 	//SpawnInfo.Instigator = GetInstigator();
// 	SpawnInfo.ObjectFlags |= RF_Transient;
// 	for (TSubclassOf<AGpCharacterView> ViewClass : ViewClasses)
// 	{
// 		AGpCharacterView* View = World->SpawnActor<AGpCharacterView>(ViewClass, SpawnInfo);
// 		View->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
//
// 		Views.Add(View);
// 	}
// }
