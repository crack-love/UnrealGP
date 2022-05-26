// #pragma once
//
// #include "CoreMinimal.h"
// #include "Animation/AnimInstance.h"
// #include "GpCharacterAnim.generated.h"
//
// UCLASS()
// class UGpCharacterAnim : public UAnimInstance
// {
// 	GENERATED_BODY()
//
// public:
// 	void NativeUpdateAnimation(float DeltaSeconds) override;
//
// private:
// 	// forward local velocity [-1, 1]
// 	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
// 	float ForwardVelocity;
//
// 	// sideward local velocity [-1, 1]
// 	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
// 	float RightVelocity;
// };
