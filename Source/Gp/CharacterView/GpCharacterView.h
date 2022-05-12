#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GpCharacterView.generated.h"

class AActor;
class UCameraComponent;

// 3��Ī 1��Ī �� ĳ���� �� ��ȯ ����
// �� �丶�� ���� ��ǲ ������Ʈ ��� (Actor's Property)
UCLASS(Abstract, Blueprintable)
class AGpCharacterView : public AActor
{
	GENERATED_BODY()

public:
	AGpCharacterView();

	virtual void Enable(AActor* TargetActor, UCameraComponent* BaseCamera);

	virtual void Disable();

	const FName& GetViewName();

protected:
	UPROPERTY(EditDefaultsOnly)
	FName ViewName;
};
