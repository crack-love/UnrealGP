#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelData.generated.h"

UCLASS(Abstract)
class VOXELMESH_API AVoxelData : public AActor
{
	GENERATED_BODY()

public:
	AVoxelData(const FObjectInitializer& Init);

	void SetSize(FIntVector InSize, bool bForceAllocate = false);

	virtual void SetGap(FVector InGap);

	virtual void SetVolume(FIntVector Idx, float Volume);

	virtual float GetVolume(FIntVector Idx) const;

	virtual TArray<float> GetVolumeArray() const;

	virtual FIntVector GetSize() const;

	virtual FVector GetGap() const;

	void ClearVolumes();

protected:
	virtual void OnVoxelDataModificated() {}
	
private:	
	int SerialIndex(const FIntVector Idx) const;

	UPROPERTY(EditDefaultsOnly, Category=Voxel)
	FIntVector Size;

	UPROPERTY(EditDefaultsOnly, Category=Voxel)
	FVector Gap;
	
	UPROPERTY()
	TArray<float> Volumes;
};
