#include "GpShoulderViewComponent.h"

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GpInputNameManager.h"

UGpShoulderViewComponent::UGpShoulderViewComponent(const FObjectInitializer& Init)
{
	// Set Defaults
	RotateHorSpeed = 100;
	RotateVerSpeed = 100;
	bClampVerticalRotation = true;
	MinVerticalRotation = -35;
	MaxVerticalRotation = 20;

	Camera = Init.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
}

void UGpShoulderViewComponent::Setup(USpringArmComponent* InSpringArm)
{
	CharacterCache = Cast<ACharacter>(GetOwner());
	if (CharacterCache != nullptr)
	{
		CharacterCache->bUseControllerRotationYaw = false;
		CharacterCache->bUseControllerRotationPitch = false;
		CharacterCache->bUseControllerRotationRoll = false;

		MovementCache = CharacterCache->GetCharacterMovement();
		if (MovementCache != nullptr)
		{
			MovementCache->bOrientRotationToMovement = false; // sidewalk
			MovementCache->bUseControllerDesiredRotation = true; // use controller rotation
			MovementCache->RotationRate = FRotator(0, 500, 0);
			MovementCache->bIgnoreBaseRotation = true;
			//MovementCache->JumpZVelocity = 400.f;
			//MovementCache->AirControl = 0.2f;
		}
	}

	SpringArm = InSpringArm;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 500.f;

	ensure(Camera);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale, USpringArmComponent::SocketName);
}

void UGpShoulderViewComponent::SetupInput(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(FGpInputNameManager::NAME_AxisMoveForward, this, &ThisClass::InputMoveForward);
	PlayerInputComponent->BindAxis(FGpInputNameManager::NAME_AxisMoveRight, this, &ThisClass::InputMoveRight);
	PlayerInputComponent->BindAxis(FGpInputNameManager::NAME_AxisLookUp, this, &ThisClass::InputLookUp);
	PlayerInputComponent->BindAxis(FGpInputNameManager::NAME_AxisLookRight, this, &ThisClass::InputLookRight);
}

void UGpShoulderViewComponent::InputMoveForward(float Value01)
{
	// 1. rotate toward springArm's rotation
	// 2. move forward

	if (Value01 == 0.0f) return;
	if (CharacterCache == nullptr) return;
	if (MovementCache == nullptr) return;
	AController* Controller = CharacterCache->Controller;
	if (Controller == nullptr) return;

	// Rotate controller
	float SpringArmYaw = SpringArm->GetRelativeRotation().Yaw;
	FRotator Rotater(0, SpringArmYaw, 0);
	Controller->SetControlRotation(Rotater);

	// Move Forward/back
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector WorldDir = FRotationMatrix(Rotater).GetUnitAxis(EAxis::X);
	CharacterCache->AddMovementInput(WorldDir, Value01);
}

void UGpShoulderViewComponent::InputMoveRight(float Value01)
{
	// 1. rotate toward springArm's rotation
	// 2. move side

	if (Value01 == 0.0f) return;
	if (CharacterCache == nullptr) return;
	if (MovementCache == nullptr) return;
	AController* Controller = CharacterCache->Controller;
	if (Controller == nullptr) return;

	// Rotate controller
	float SpringArmYaw = SpringArm->GetRelativeRotation().Yaw;
	FRotator Rotater(0, SpringArmYaw, 0);
	Controller->SetControlRotation(Rotater);

	// Move Side
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector WorldDir = FRotationMatrix(Rotater).GetUnitAxis(EAxis::Y);
	CharacterCache->AddMovementInput(WorldDir, Value01);
}

void UGpShoulderViewComponent::InputLookRight(float Value01)
{
	if (Value01 == 0.f) return;

	float DeltaSec = GetWorld()->GetDeltaSeconds();
	float DeltaYaw = Value01 * RotateHorSpeed * DeltaSec;
	FRotator Rotation = SpringArm->GetRelativeRotation();
	Rotation.Yaw += DeltaYaw;

	SpringArm->SetRelativeRotation(Rotation); // teleport
}

void UGpShoulderViewComponent::InputLookUp(float Value01)
{
	if (Value01 == 0.f) return;

	float DeltaSec = GetWorld()->GetDeltaSeconds();
	float DeltaPitch = Value01 * RotateVerSpeed * DeltaSec;
	FRotator Rotation = SpringArm->GetRelativeRotation();
	Rotation.Pitch += DeltaPitch;

	// clamp
	if (bClampVerticalRotation)
	{
		Rotation.Pitch = FMath::Clamp(Rotation.Pitch, MinVerticalRotation, MaxVerticalRotation);
	}

	SpringArm->SetRelativeRotation(Rotation); // teleport
}