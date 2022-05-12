//#pragma once
//
//#include "CoreMinimal.h"
//
//#include "Animation/AnimInstance.h"
//#include "Delegates/Delegate.h"
//
//#include "GpAnimationInstance.generated.h"
//
//DECLARE_MULTICAST_DELEGATE(FOnBegAttack);
//DECLARE_MULTICAST_DELEGATE(FOnEndAttack);
//DECLARE_MULTICAST_DELEGATE(FOnMontageEnd);
//
//class UAnimMontage;
//
//USTRUCT()
//struct FMontageAndNamePair
//{
//	GENERATED_BODY()
//
//	UPROPERTY()
//	UAnimMontage* AnimMontage;
//
//	UPROPERTY()
//	FString Name;
//};
//
//// locomition
//UCLASS()
//class UGpAnimationInstance : public UAnimInstance
//{
//	GENERATED_BODY()
//
//	//
//	// Init
//	//
//public:
//	UGpAnimationInstance();
//
//	void NativeUpdateAnimation(float DeltaSeconds) override;
//
//	//
//	// Events
//	//
//public:
//	// Actual Melee Attack Start, enable collistion or get continuous input etc
//	FOnBegAttack OnBegAttack;
//
//	// Actual Melee Attack End
//	FOnEndAttack OnEndAttack;
//
//	FOnMontageEnd OnMontageEnd;
//
//	// 
//	// Plublic Methods
//	//
//public:
//	float PlayAnimMontage(UAnimMontage* Montage);
//
//	float PlayAnimMontage(int32 Idx);
//
//	float PlayAnimMontage(const FString& Name);
//
//	//
//	// Notifies
//	//
//private:
//	void AnimNotify_BegAttack();
//	void AnimNotify_EndAttack();
//	void Internal_MontageEnded(UAnimMontage* Montage, bool bInterrupted);
//
//	//
//	// Properties
//	//
//private:
//	// Accel is setted from NativeUpdateAnimation, 
//	// accessed by anim graph for locomotion
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
//	FVector Acceleration;
//
//	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
//	TArray<FMontageAndNamePair> MontageList;
//};