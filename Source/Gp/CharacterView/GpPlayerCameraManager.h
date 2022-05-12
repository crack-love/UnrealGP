// #pragma once
//
// #include "Camera/PlayerCameraManager.h"
//
// #include "Camera/CameraComponent.h"
// #include "Camera/CameraActor.h"
// #include "GpPlayerCameraManager.generated.h"
//
// UCLASS(Blueprintable)
// class AGpPlayerCameraManager : public APlayerCameraManager
// {
// 	GENERATED_BODY()
// 	
// 	AGpPlayerCameraManager()
// 	{
// 		this->CameraStyle = TEXT("ThirdPerson");
//
// 		BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BaseCAM"));
// 	}
//
// 	void PostInitializeComponents() override
// 	{
// 		Super::PostInitializeComponents();
// 		
// 		FString displayName = GetName() + "_AnimCamera";
// 		AnimCameraActor->Rename(*displayName);
// 		AnimCameraActor->SetActorLabel(*displayName);
//
// 		AnimCameraActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
// 		AttachToActor(GetWorld()->GetFirstPlayerController(), FAttachmentTransformRules::KeepWorldTransform);
//
// 		//// spawn the temp CameraActor used for updating CameraAnims
// 		//FActorSpawnParameters SpawnInfo;
// 		//SpawnInfo.Owner = this;
// 		//SpawnInfo.Instigator = GetInstigator();
// 		//SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// 		//SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save these temp actors into a map
// 		//AnimCameraActor = GetWorld()->SpawnActor<ACameraActor>(SpawnInfo);
// 	}
//
// public:
// 	UPROPERTY()
// 	TArray<AActor*> TargetActors;
//
// 	UPROPERTY(EditAnywhere)
// 	class UCameraComponent* BaseCamera;
// };