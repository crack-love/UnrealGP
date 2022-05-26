// #include "GpThirdPersonView.h"
//
// #include "CoreMinimal.h"
// #include "Camera/CameraComponent.h"
// #include "Components/InputComponent.h"
// #include "GameFramework/Character.h"
// #include "GameFramework/CharacterMovementComponent.h"
// #include "GameFramework/Controller.h"
// #include "GameFramework/SpringArmComponent.h"
// #include "Gp/GpInputNames.h"
//
// AGpThirdPersonView::AGpThirdPersonView() : Super()
// {
// 	// Set Defaults
// 	RotateHorSpeed = 100;
// 	RotateVerSpeed = 100;
// 	bClampVerticalRotation = true;
// 	MinVerticalRotation = -35;
// 	MaxVerticalRotation = 20;
//
// 	// Create SpringArm
// 	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
// 	SpringArm->SetUsingAbsoluteRotation(true);
// 	SpringArm->bUsePawnControlRotation = false;
// 	SpringArm->bEnableCameraLag = true;
// 	SpringArm->bEnableCameraRotationLag = true;
// 	SpringArm->CameraLagSpeed = 500.f;
// 	SpringArm->SetupAttachment(RootComponent);
// }
//
//
// void AGpThirdPersonView::Enable(AActor* TargetActor, ACameraActor* SourceCamera)
// {
// 	Super::Enable(TargetActor, SourceCamera);
//
// 	Character = Cast<ACharacter>(TargetActor);
// 	if (Character != nullptr)
// 	{
// 		Character->bUseControllerRotationYaw = false;
// 		Character->bUseControllerRotationPitch = false;
// 		Character->bUseControllerRotationRoll = false;
//
// 		// set rotation constraint
// 		Movement = Character->GetCharacterMovement();
// 		if (Movement != nullptr)
// 		{
// 			Movement->bOrientRotationToMovement = false; // sidewalk
// 			Movement->bUseControllerDesiredRotation = true; // use controller rotation
// 			Movement->RotationRate = FRotator(0, 500, 0);
// 			Movement->bIgnoreBaseRotation = true;
// 		}
// 	}
//
// 	Camera = SourceCamera;
// 	Camera->bUsePawnControlRotation = false;
//
// 	// Setup Attachments
// 	SpringArm->AttachToComponent(TargetActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
// 	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetIncludingScale, USpringArmComponent::SocketName);
// 	//AttachToActor(TargetActor, FAttachmentTransformRules::SnapToTargetIncludingScale);
// 	TargetActor->RegisterAllComponents();	
//
// 	APlayerController* Controller = Cast<APlayerController>(Character->Controller);
// 	APlayerCameraManager* CameraManager = Controller->PlayerCameraManager;
// 	//CameraManager->CameraCache
// }
//
// void AGpThirdPersonView::Disable()
// {
// 	Super::Disable();
// }
//
// void AGpThirdPersonView::PostInitializeComponents()
// {
// 	Super::PostInitializeComponents();
//
// 	// Bind Inputs
// 	InputComponent->BindAxis(FGpInputNames::NAME_AxisLookUp, this, &ThisClass::InputLookUp);
// 	InputComponent->BindAxis(FGpInputNames::NAME_AxisLookRight, this, &ThisClass::InputLookRight);
// }
//
// void AGpThirdPersonView::InputLookRight(float Value01)
// {
// 	if (Value01 == 0.f) return;
//
// 	float DeltaSec = GetWorld()->GetDeltaSeconds();
// 	float DeltaYaw = Value01 * RotateHorSpeed * DeltaSec;
// 	FRotator Rotation = SpringArm->GetRelativeRotation();
// 	Rotation.Yaw += DeltaYaw;
//
// 	SpringArm->SetRelativeRotation(Rotation); // teleport
// }
//
// void AGpThirdPersonView::InputLookUp(float Value01)
// {
// 	if (Value01 == 0.f) return;
//
// 	float DeltaSec = GetWorld()->GetDeltaSeconds();
// 	float DeltaPitch = Value01 * RotateVerSpeed * DeltaSec;
// 	FRotator Rotation = SpringArm->GetRelativeRotation();
// 	Rotation.Pitch += DeltaPitch;
//
// 	// clamp
// 	if (bClampVerticalRotation)
// 	{
// 		Rotation.Pitch = FMath::Clamp(Rotation.Pitch, MinVerticalRotation, MaxVerticalRotation);
// 	}
//
// 	SpringArm->SetRelativeRotation(Rotation); // teleport
// }
