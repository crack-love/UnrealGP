#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GpPlayerCharacter.generated.h"

/*
어소라이즈서버모델
플레이어캐릭터
	로코모션
	구르기
	숄더뷰카메라
	스테이트
		경험치
		레벨
		능력치(스탯)
		현재스테이트
	파쿠르(climbing)
*/

USTRUCT()
struct FGpReplicatedAccel
{
	GENERATED_BODY()

	// Direction of XY accel component, quantized to represent [0, 2*pi]
	UPROPERTY()
	uint8 AccelXYRadians = 0;	
	
	//Accel rate of XY component, quantized to represent [0, MaxAcceleration]
	UPROPERTY()
	uint8 AccelXYMagnitude = 0;	

	// Raw Z accel rate component, quantized to represent [-MaxAcceleration, MaxAcceleration]
	UPROPERTY()
	int8 AccelZ = 0;
};

USTRUCT()
struct FGpReplicatedAnimation
{
	GENERATED_BODY()

	UPROPERTY()
	uint8 AnimIndex = 0;
};

UCLASS()
class AGpPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	//
	// Inits
	// 
public:
	AGpPlayerCharacter(const FObjectInitializer& Init = FObjectInitializer::Get());

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void PostInitializeComponents() override;

	//
	// RPCs
	//
private:
	UFUNCTION(Server, Reliable)
	void Server_InputAttack();

	UFUNCTION(Server, Reliable)
	void Server_InputRoll();

	UFUNCTION(Server, Reliable)
	void Server_InputJump();

private:
	UFUNCTION()
	void OnRep_ReplicatedAccel();

	UFUNCTION()
	void OnRep_ReplicatedAnimation();

private:
	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedAccel)
	FGpReplicatedAccel ReplicatedAccel;

	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedAnimation)
	FGpReplicatedAccel ReplicatedAnimation;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UGpShoulderViewComponent* ShoulderView;
};


//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta=(AllowPrivateAccess = "true"))