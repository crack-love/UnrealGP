// #pragma once
//
// #include "CoreMinimal.h"
// #include "GameFramework/Actor.h"
// #include "GpCharacterView.generated.h"
//
// class AActor;
//
// // AGpCharacterViewManager 소유
// // 3인칭 1인칭 등 캐릭터 뷰 전환 단위
// // 카메라, 캐릭터 이동 관리
// // 각 뷰마다 개별 인풋 컴포넌트 사용
// UCLASS(Abstract, Blueprintable)
// class AGpCharacterView : public AActor
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditDefaultsOnly)
// 	FName ViewName;
// 	
// public:
// 	AGpCharacterView();
//
// 	virtual void Enable(AActor* TargetActor, ACameraActor* BaseCamera);
//
// 	virtual void Disable();
//
// 	bool IsMatchViewName(const FName& InName) const;
// };
