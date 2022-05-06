#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GpPlayerCharacter.generated.h"

/*
��Ҷ��������
�÷��̾�ĳ����
	���ڸ��
	������
	�����ī�޶�
	������Ʈ
		����ġ
		����
		�ɷ�ġ(����)
		���罺����Ʈ
	����(climbing)
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