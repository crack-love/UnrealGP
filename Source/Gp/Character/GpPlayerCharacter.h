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

class UInputComponent;
class USpringArmComponent;
class UGpShoulderViewComponent;

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

	void PostInitializeComponents() override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
	void OnRep_ReplicatedAnimation();

private:
	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedAnimation)
	FGpReplicatedAnimation ReplicatedAnimation;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UGpShoulderViewComponent* ShoulderView;
};


//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta=(AllowPrivateAccess = "true"))