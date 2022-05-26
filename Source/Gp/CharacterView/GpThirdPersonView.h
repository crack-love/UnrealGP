// #pragma once
//
// #include "CoreMinimal.h"
// #include "GpCharacterView.h"
// #include "GpThirdPersonView.generated.h"
//
// class ACharacter;
// class UCameraComponent;
// class UCharacterMovementComponent;
// class USpringArmComponent;
// struct FInputAxisBinding;
//
// // 카메라 rotation, zoom
// // 캐릭터 move
// UCLASS(BlueprintType)
// class AGpThirdPersonView final : public AGpCharacterView
// {
// 	GENERATED_BODY()
//
// public:
// 	AGpThirdPersonView();
//
// 	virtual void Enable(AActor* TargetActor, ACameraActor* SourceCamera) override;
//
// 	virtual void Disable() override;
//
// 	// initialize input
// 	virtual void PostInitializeComponents() override;
//
// private:
// 	void InputMoveRight(float Value01);
// 	
// 	void InputMoveForward(float Value01);
// 	
// 	void InputLookRight(float Value01);
//
// 	void InputLookUp(float Value01);
//
// private:
// 	UPROPERTY(EditAnywhere)
// 	USpringArmComponent* SpringArm;
//
// 	UPROPERTY(EditAnywhere)
// 	float RotateHorSpeed;
//
// 	UPROPERTY(EditAnywhere)
// 	float RotateVerSpeed;
//
// 	UPROPERTY(EditAnywhere)
// 	bool bClampVerticalRotation;
//
// 	// rotate to upper
// 	UPROPERTY(EditAnywhere)
// 	float MinVerticalRotation;
//
// 	// rotate to lower
// 	UPROPERTY(EditAnywhere)
// 	float MaxVerticalRotation;
//
// 	// Cache
// 	UPROPERTY(Transient)
// 	UCameraComponent* Camera;
//
// 	// Cache
// 	UPROPERTY(Transient)
// 	ACharacter* Character;
// 	
// 	// Cache
// 	UPROPERTY(Transient)
// 	UCharacterMovementComponent* Movement;
// };
