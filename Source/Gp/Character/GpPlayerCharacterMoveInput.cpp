// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "GpPlayerCharacterMoveInput.h"
//
//
// // Sets default values for this component's properties
// UGpPlayerCharacterMoveInput::UGpPlayerCharacterMoveInput()
// {
// 	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
// 	// off to improve performance if you don't need them.
// 	PrimaryComponentTick.bCanEverTick = true;
//
// 	// ...
// }
//
//
// // Called when the game starts
// void UGpPlayerCharacterMoveInput::BeginPlay()
// {
// 	Super::BeginPlay();
//
// 	// ...
// 	
// }
//
// void AGpThirdPersonView::InputMoveForward(float Value01)
// {
// 	// 1. rotate toward springArm's rotation
// 	// 2. move forward
//
// 	if (Value01 == 0.0f) return;
// 	if (Character == nullptr) return;
// 	if (Movement == nullptr) return;
// 	AController* Controller = Character->Controller;
// 	if (Controller == nullptr) return;
//
// 	// Rotate controller
// 	float SpringArmYaw = SpringArm->GetRelativeRotation().Yaw;
// 	FRotator Rotater(0, SpringArmYaw, 0);
// 	Controller->SetControlRotation(Rotater);
//
// 	// Move Forward/back
// 	float DeltaTime = GetWorld()->GetDeltaSeconds();
// 	FVector WorldDir = FRotationMatrix(Rotater).GetUnitAxis(EAxis::X);
// 	Character->AddMovementInput(WorldDir, Value01);
// }
//
// void AGpThirdPersonView::InputMoveRight(float Value01)
// {
// 	// 1. rotate toward springArm's rotation
// 	// 2. move side
//
// 	if (Value01 == 0.0f) return;
// 	if (Character == nullptr) return;
// 	if (Movement == nullptr) return;
// 	AController* Controller = Character->Controller;
// 	if (Controller == nullptr) return;
//
// 	// Rotate controller
// 	float SpringArmYaw = SpringArm->GetRelativeRotation().Yaw;
// 	FRotator Rotater(0, SpringArmYaw, 0);
// 	Controller->SetControlRotation(Rotater);
//
// 	// Move Side
// 	float DeltaTime = GetWorld()->GetDeltaSeconds();
// 	FVector WorldDir = FRotationMatrix(Rotater).GetUnitAxis(EAxis::Y);
// 	Character->AddMovementInput(WorldDir, Value01);
// }
// // Called every frame
// void UGpPlayerCharacterMoveInput::TickComponent(float DeltaTime, ELevelTick TickType,
//                                                 FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }
//
