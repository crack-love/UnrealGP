#pragma once

#include "GameFramework/Actor.h"
#include "VoxelData.generated.h"

UCLASS()
class AVoxelData : public AActor
{
	GENERATED_BODY()
	
	// VoxelData Modification
public:
	void SetSize(FIntVector NewSize);

	void SetGap(FVector NewGap);

	void SetVolume(FIntVector Idx, float Volume);

	// Clear vertices but remain meta(size,gap)
	void Clear();
	
	float GetVolume(FIntVector Idx) const;

	TArray<float> GetVolumeArray() const;

	FIntVector GetSize() const;

	FVector GetGap() const;
	
private:
	int SerialIndex(const FIntVector Idx) const;
	
	TArray<float> Volumes;

	FIntVector Size;

	FVector Gap;
};
