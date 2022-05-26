// #include "GpCharacterAnim.h"
// #include "CoreMinimal.h"
// #include "GameFramework/Pawn.h"
// #include "GameFramework/PawnMovementComponent.h"
//
// void UGpCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
// {
// 	Super::NativeUpdateAnimation(DeltaSeconds);
//
// 	auto Pawn = TryGetPawnOwner();
// 	if (IsValid(Pawn))
// 	{
// 		FVector Velocity = Pawn->GetVelocity();
// 		float MaxVelocity = Pawn->GetMovementComponent()->GetMaxSpeed();
// 		Velocity /= MaxVelocity;
// 		FRotator Rotation = Pawn->GetActorRotation();
//
// 		FVector Forward = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
// 		ForwardVelocity = FVector::DotProduct(Velocity, Forward);
// 		
// 		FVector Sideway = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
// 		RightVelocity = FVector::DotProduct(Velocity, Sideway);
// 	}
// }
//
