#pragma once

#include "UObject/ObjectMacros.h"

extern struct FIntVector;

USTRUCT()
class FVoxelData
{
	GENERATED_BODY()

	// Static Method
public:
	static int32 GetSerialIndex(FIntVector Idx, FIntVector Size);

	// Public Method
public:
	void SetSize(FIntVector Size);

	void SetGap(FVector Gap);

	void SetVolume(FIntVector Idx, float Volume);

	float GetVolume(FIntVector Idx);

	TArray<float> GetVolumeArray();

	FIntVector GetSize();

	FVector GetGap();

	// Clear vertices but reamin meta(size,gap)
	void Clear();

private:
	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<float> Volumes;

	UPROPERTY(VisibleAnywhere, Replicated)
	FIntVector Size;

	UPROPERTY(VisibleAnywhere, Replicated)
	FVector Gap;

	int32 GetSerialIndex_Internal(FIntVector Idx);
};