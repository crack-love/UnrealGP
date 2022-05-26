// #pragma once
//
// #include "CoreMinimal.h"
// #include "GameFramework/Actor.h"
// #include "GpCharacterView.generated.h"
//
// class AActor;
//
// // AGpCharacterViewManager ����
// // 3��Ī 1��Ī �� ĳ���� �� ��ȯ ����
// // ī�޶�, ĳ���� �̵� ����
// // �� �丶�� ���� ��ǲ ������Ʈ ���
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
