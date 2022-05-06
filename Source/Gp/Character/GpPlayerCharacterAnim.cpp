//#include "GpAnimationInstance.h"
//
//#include "CoreMinimal.h"
//#include "Delegates/Delegate.h"
//#include "GameFramework/CharacterMovementComponent.h"
//
//#include "Gp/GpLog.h"
//#include "GpPlayerCharacter.h"
//
//UGpAnimationInstance::UGpAnimationInstance()
//{
//	OnMontageEnded.AddDynamic(this, &ThisClass::Internal_MontageEnded);
//}
//
//void UGpAnimationInstance::NativeUpdateAnimation(float DeltaSeconds)
//{
//	const AGpPlayerCharacter* Character = Cast<AGpPlayerCharacter>(GetOwningActor());
//	if (!Character) return;
//
//	const UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
//	if (!Movement) return;
//
//	float MaxAccel = Movement->GetMaxAcceleration();
//	FVector CurAccel = Movement->GetCurrentAcceleration();
//	CurAccel /= MaxAccel; // to -1~1
//
//	FRotator Rotation = Character->GetActorRotation();
//	FVector ForwardRot = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
//	FVector StrafeRot = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
//	float ForwardMag = FVector::DotProduct(CurAccel, ForwardRot);
//	float StrafeMag = FVector::DotProduct(CurAccel, StrafeRot);
//
//	Acceleration.X = StrafeMag;
//	Acceleration.Y = ForwardMag;
//	Acceleration.Z = 0;
//
//	//FGpLog::Log(TEXTF("%s", *Acceleration.ToString()), this);
//}
//
//float UGpAnimationInstance::PlayAnimMontage(int32 Idx)
//{
//	if (Idx >= MontageList.Num())
//	{
//		FGpLog::Log(TEXT("MontageList Index Range Overflowed"), this);
//		return 0;
//	}
//
//	return PlayAnimMontage(MontageList[Idx].AnimMontage);
//}
//
//float UGpAnimationInstance::PlayAnimMontage(const FString& Name)
//{
//	for (const FMontageAndNamePair& pair : MontageList)
//	{
//		if (pair.Name == Name)
//		{
//			return PlayAnimMontage(pair.AnimMontage);
//		}
//	}
//
//	FGpLog::Log(TEXTF("Can't Find Montage Name: %s", *Name), this);
//	return 0;
//}
//
//float UGpAnimationInstance::PlayAnimMontage(UAnimMontage* Montage)
//{
//	return Montage_Play(Montage);
//}
//
//void UGpAnimationInstance::AnimNotify_BegAttack()
//{
//	OnBegAttack.Broadcast();
//}
//
//void UGpAnimationInstance::AnimNotify_EndAttack()
//{
//	OnEndAttack.Broadcast();
//}
//
//void UGpAnimationInstance::Internal_MontageEnded(UAnimMontage* Montage, bool bInterrupted)
//{
//	OnMontageEnd.Broadcast();
//}
//
