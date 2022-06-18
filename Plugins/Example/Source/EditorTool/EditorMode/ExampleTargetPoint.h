#pragma once
#include "Engine/Targetpoint.h"
#include "ExampleTargetPoint.generated.h"

UCLASS()
class EDITORTOOL_API AExampleTargetPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Points")
	TArray<FVector> Points;
};
