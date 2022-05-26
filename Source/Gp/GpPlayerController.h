// #pragma once
//
// #include "CoreMinimal.h"
// #include "GameFramework/PlayerController.h"
// #include "Gp/CharacterView/GpCharacterViewManager.h"
// #include "GpPlayercontroller.generated.h"
//
//
// UCLASS(Blueprintable)
// class AGpPlayerController : public APlayerController
// {
// 	GENERATED_BODY()
//
// public:
// 	AGpPlayerController() {}
//
// 	void PreInitializeComponents() override;
//
// 	AGpCharacterViewManager* GetCharacterViewManager();
//
// private:
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
// 	TSubclassOf<AGpCharacterViewManager> CharacterViewManagerClass;
// 	
// 	UPROPERTY(Transient)
// 	AGpCharacterViewManager* CharacterViewManager;
// };
