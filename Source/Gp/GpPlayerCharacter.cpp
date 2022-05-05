#include "GpPlayerCharacter.h"
#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

#include "GpShoulderViewComponent.h"


AGpPlayerCharacter::AGpPlayerCharacter(const FObjectInitializer& Init /*= FObjectInitializer::Get()*/)
{
//	LookRightSpeed = 50.f;
//	LookUpSpeed = 40.f;
//
//	bUseControllerRotationPitch = false;
//	bUseControllerRotationYaw = false;
//	bUseControllerRotationRoll = false;
//	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
//	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f); // ...at this rotation rate
//	GetCharacterMovement()->JumpZVelocity = 600.f;
//	GetCharacterMovement()->AirControl = 0.2f;

	SpringArm = Init.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	//Camera = Init.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	//Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	ShoulderView = Init.CreateDefaultSubobject<UGpShoulderViewComponent>(this, TEXT("ShoulderView"));
}

void AGpPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	ShoulderView->SetupInput(PlayerInputComponent);

	/*PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGpPlayerCharacter::Input_MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGpPlayerCharacter::Input_MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AGpPlayerCharacter::Input_LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AGpPlayerCharacter::Input_LookUp);*/
}

void AGpPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGpPlayerCharacter, ReplicatedAccel);
	DOREPLIFETIME(AGpPlayerCharacter, ReplicatedAnimation);
}

void AGpPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ShoulderView->Setup(SpringArm);
}

void AGpPlayerCharacter::Server_InputAttack_Implementation()
{

}

void AGpPlayerCharacter::Server_InputRoll_Implementation()
{

}

void AGpPlayerCharacter::Server_InputJump_Implementation()
{

}

void AGpPlayerCharacter::OnRep_ReplicatedAccel()
{

}

void AGpPlayerCharacter::OnRep_ReplicatedAnimation()
{

}

