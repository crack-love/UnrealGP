//#include "GpPlayerCharacter.h"
//
//#include "CoreMinimal.h"
//#include "Camera/CameraComponent.h"
//#include "Components/InputComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Net/UnrealNetwork.h"
//
//#include "GpShoulderViewComponent.h"
//
//
//AGpPlayerCharacter::AGpPlayerCharacter(const FObjectInitializer& Init /*= FObjectInitializer::Get()*/)
//{
//	USkeletalMeshComponent* SkeletalMesh = GetMesh();
//	SkeletalMesh->SetRelativeLocationAndRotation(FVector(0,0,-85), FRotator(0,-90,0));
//
//	SpringArm = Init.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm"));
//	SpringArm->SetupAttachment(RootComponent);
//
//	ShoulderView = Init.CreateDefaultSubobject<UGpShoulderViewComponent>(this, TEXT("ShoulderView"));
//}
//
//void AGpPlayerCharacter::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//
//	ShoulderView->Setup(SpringArm);
//}
//
//void AGpPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	ShoulderView->SetupInput(PlayerInputComponent);
//}
//
//void AGpPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME_CONDITION(ThisClass, ReplicatedAccel, COND_SimulatedOnly);
//	DOREPLIFETIME_CONDITION(ThisClass, ReplicatedAnimation, COND_SimulatedOnly);
//}
//
//void AGpPlayerCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
//{
//	Super::PreReplication(ChangedPropertyTracker);
//
//	UpdateReplicateAccel();
//}
//
//void AGpPlayerCharacter::Server_InputAttack_Implementation()
//{
//
//}
//
//void AGpPlayerCharacter::Server_InputRoll_Implementation()
//{
//
//}
//
//void AGpPlayerCharacter::Server_InputJump_Implementation()
//{
//
//}
//
//void AGpPlayerCharacter::OnRep_ReplicatedAxis()
//{
//
//}
//
//void AGpPlayerCharacter::OnRep_ReplicatedAccel()
//{
//	// update accel to movementcomp
//
//	UCharacterMovementComponent* Movement = GetCharacterMovement();
//
//	float FwdMag = ReplicatedAccel.AccelX / 127.0;
//	float RgtMag = ReplicatedAccel.AccelY / 127.0;
//	
//	Movement->Acceleration = 
//}
//
//void AGpPlayerCharacter::UpdateReplicateAccel()
//{
//	const UCharacterMovementComponent* Movement = GetCharacterMovement();
//	if (!Movement) return;
//
//	float MaxAccel = Movement->GetMaxAcceleration();
//	FVector WorldAccel = Movement->GetCurrentAcceleration();
//	WorldAccel /= MaxAccel; // -1~1
//
//	FRotator WorldRot = Character->GetActorRotation(); // world rotation
//	FVector ForwardAxis = FRotationMatrix(WorldRot).GetUnitAxis(EAxis::X);
//	FVector RightAxis = FRotationMatrix(WorldRot).GetUnitAxis(EAxis::Y);
//	float ForwardMag = FVector::DotProduct(WorldAccel, ForwardAxis);
//	float RightMag = FVector::DotProduct(WorldAccel, RightAxis);
//
//	// -1~1 to -127~127
//	ReplicatedAccel.AccelY = FMath::FloorToInt(ForwardMag * 127.0);
//	ReplicatedAccel.AccelX = FMath::FloorToInt(RightMag * 127.0); 
//}
//
//
//void AGpPlayerCharacter::OnRep_ReplicatedAnimation()
//{
//
//}