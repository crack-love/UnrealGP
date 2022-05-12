#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GpCharacterView.h"
#include "GpCharacterViewManager.generated.h"

class UCameraComponent;
class AGpCharacterView;

// ?÷???? ???????? ????
UCLASS(Blueprintable)
class AGpCharacterViewManager : public AActor
{
	GENERATED_BODY()

public:
	AGpCharacterViewManager();

	void PreInitializeComponents() override;

	void SetView(const FName& ViewName, AActor* Target);

	// Can be null
	AGpCharacterView* GetCurentView() { return CurrentView; }

	UCameraComponent* GetBaseCamera() { return BaseCamera; }

private:
	// Camera commonly can be used each views
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UCameraComponent* BaseCamera;

	// class of views to generate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TArray<TSubclassOf<AGpCharacterView>> ViewClasses;

	UPROPERTY(Transient)
	AGpCharacterView* CurrentView;

	UPROPERTY(Transient)
	TArray<AGpCharacterView*> Views;
};