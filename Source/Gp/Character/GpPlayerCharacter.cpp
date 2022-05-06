#include "GpPlayerCharacter.h"

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

#include "GpShoulderViewComponent.h"


AGpPlayerCharacter::AGpPlayerCharacter(const FObjectInitializer& Init /*= FObjectInitializer::Get()*/)
{
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	SkeletalMesh->SetRelativeLocationAndRotation(FVector(0,0,-85), FRotator(0,-90,0));

	SpringArm = Init.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	ShoulderView = Init.CreateDefaultSubobject<UGpShoulderViewComponent>(this, TEXT("ShoulderView"));
}

void AGpPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ShoulderView->Setup(SpringArm);
}

void AGpPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	ShoulderView->SetupInput(PlayerInputComponent);
}

void AGpPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ThisClass, ReplicatedAccel, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ThisClass, ReplicatedAnimation, COND_SimulatedOnly);
}

void AGpPlayerCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);

	// update animation?
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