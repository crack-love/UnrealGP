#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GpCharacter.generated.h"



class UGpCharacterCameraView;
class USpringArmComponent;


UCLASS()
class AGpCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGpCharacter();

	void PossessedBy(AController* NewController) override;

	void UnPossessed() override;


};