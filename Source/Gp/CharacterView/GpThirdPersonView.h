#pragma once

#include "CoreMinimal.h"
#include "GpCharacterView.h"
#include "GpThirdPersonView.generated.h"

class ACharacter;
class UCameraComponent;
class UCharacterMovementComponent;
class USpringArmComponent;
struct FInputAxisBinding;

UCLASS(BlueprintType)
class AGpThirdPersonView : public AGpCharacterView
{
	GENERATED_BODY()

public:
	AGpThirdPersonView();

	void Enable(AActor* TargetActor, UCameraComponent* SourceCamera) override;

	void Disable() override;

	void PostInitializeComponents() override;

private:
	void InputMoveForward(float Value01);

	void InputMoveRight(float Value01);

	void InputLookRight(float Value01);

	void InputLookUp(float Value01);

private:
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

	// Cache
	UPROPERTY(Transient)
	UCameraComponent* Camera;

	// Cache
	UPROPERTY(Transient)
	ACharacter* Character;
	
	// Cache
	UPROPERTY(Transient)
	UCharacterMovementComponent* Movement;
};
