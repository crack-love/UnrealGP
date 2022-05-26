// #pragma once
//
// #include "CoreMinimal.h"
// #include "GameFramework/Actor.h"
// #include "GpCharacterViewManager.generated.h"
//
// class AGpCharacterView;
//
// // Contained from APlayerController
// UCLASS(Blueprintable)
// class AGpCharacterViewManager final : public AActor
// {
// 	GENERATED_BODY()
//
// 	// Camera commonly can be used each views
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
// 	TSubclassOf<ACameraActor> BaseCameraClass;
//
// 	// class of views to generate
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
// 	TArray<TSubclassOf<AGpCharacterView>> ViewClasses;
// 	
// public:
// 	AGpCharacterViewManager();
//
// 	virtual void PostInitializeComponents() override;
//
// 	void SetView(const FName& ViewName, AActor* Target);
//
// 	AGpCharacterView* GetCurrentView() const { return CurrentView; }
//
// 	ACameraActor* GetBaseCamera() const { return BaseCamera; }
//
// 	APlayerController* GetPlayerController() const {return Controller; }
//
// private:
// 	void GenerateBaseCamera();
// 	void GenerateViews();
// 	
// 	UPROPERTY(Transient)
// 	ACameraActor* BaseCamera;
// 	
// 	UPROPERTY(Transient)
// 	TArray<AGpCharacterView*> Views;
//
// 	UPROPERTY(Transient)
// 	AGpCharacterView* CurrentView;
//
// 	UPROPERTY(Transient)
// 	APlayerController* Controller;
// };
