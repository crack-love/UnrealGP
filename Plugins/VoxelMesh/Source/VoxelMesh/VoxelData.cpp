#include "VoxelData.h"

void AVoxelData::SetSize(const FIntVector NewSize)
{
	if (NewSize == Size)
	{
		return;
	}

	Clear();

	const int32 SSize = NewSize.X * NewSize.Y * NewSize.Z;
	Volumes.SetNumZeroed(SSize, true);
	Size = NewSize;
}

void AVoxelData::SetGap(FVector NewGap)
{
	Gap = NewGap;
}

void AVoxelData::SetVolume(const FIntVector Idx, const float Volume)
{
	const int32 SIdx = SerialIndex(Idx);
	Volumes[SIdx] = Volume;
}

float AVoxelData::GetVolume(const FIntVector Idx) const
{
	const int32 SIdx = SerialIndex(Idx);
	return Volumes[SIdx];
}

TArray<float> AVoxelData::GetVolumeArray() const
{
	return Volumes;
}

FIntVector AVoxelData::GetSize() const
{
	return Size;
}

FVector AVoxelData::GetGap() const
{
	return Gap;
}

int32 AVoxelData::SerialIndex(const FIntVector Idx) const
{
	return Idx.X + Idx.Y * Size.X + Idx.Z * Size.X * Size.Y;
}

void AVoxelData::Clear()
{
	std::fill(Volumes.begin(), Volumes.end(), 0.f);
}
