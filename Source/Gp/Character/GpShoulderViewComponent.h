#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GpShoulderViewComponent.generated.h"

class ACharacter;
class UCameraComponent;
class UCharacterMovementComponent;
class USpringArmComponent;

// input look
// input move
//UCLASS(meta = (BlueprintSpawnableComponent))
UCLASS(BlueprintType)
class UGpShoulderViewComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGpShoulderViewComponent(const FObjectInitializer& Init = FObjectInitializer::Get());

public:
	// SpringArmComponent must created from actor's contructor and attached root
	// if not, it's override value written in bluprint is not setted.
	// been solve this for a week but never find why...
	void Setup(USpringArmComponent* SpringArm);

	void SetupInput(UInputComponent* PlayerInputComponent);

	void InputMoveForward(float Value01);

	void InputMoveRight(float Value01);

	void InputLookRight(float Value01);

	void InputLookUp(float Value01);

	// OnMovementChanged
	// 
	// OnRotateChanged

private:
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	float RotateHorSpeed;

	UPROPERTY(EditAnywhere)
	float RotateVerSpeed;

	UPROPERTY(EditAnywhere)
	bool bClampVerticalRotation;

	// rotate to upper
	UPROPERTY(EditAnywhere)
	float MinVerticalRotation;

	// rotate to lower
	UPROPERTY(EditAnywhere)
	float MaxVerticalRotation;

	ACharacter* CharacterCache;

	UCharacterMovementComponent* MovementCache;
};
