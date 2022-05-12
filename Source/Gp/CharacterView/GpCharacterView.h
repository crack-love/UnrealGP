#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GpCharacterView.generated.h"

class AActor;
class UCameraComponent;

// 3인칭 1인칭 등 캐릭터 뷰 전환 단위
// 각 뷰마다 개별 인풋 컴포넌트 사용 (Actor's Property)
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
