#include "VoxelData.h"

//AVoxelData::AVoxelData(const FObjectInitializer& Init) : Super(Init)
//{
//	SetSize({10, 10, 10});	
//	Gap = {10,10,10};
//
//	UE_LOG(LogTemp, Log, TEXT("Voxel Data Ctor Called"));
//}

AVoxelData::AVoxelData(const FObjectInitializer& Init = FObjectInitializer::Get()) : Super(Init)
{
	SetSize({10, 10, 10});	
	Gap = {10,10,10};
	
	UE_LOG(LogTemp, Log, TEXT("Voxel Data Ctor Called"));
};

void AVoxelData::SetSize(const FIntVector InSize, const bool bForceAllocate)
{
	if (InSize == Size && !bForceAllocate)
	{
		return;
	}

	const int32 SSize = InSize.X * InSize.Y * InSize.Z;
	Volumes.SetNum(SSize, true);
	Size = InSize;
	UE_LOG(LogTemp, Log, TEXT("Voxel Size Setted %s"), *Size.ToString());

	// set filled
	std::fill(Volumes.begin(), Volumes.end(), 1.f);

	OnVoxelDataModificated();
}

void AVoxelData::SetGap(FVector InGap)
{
	Gap = InGap;

	OnVoxelDataModificated();
}

void AVoxelData::SetVolume(const FIntVector Idx, const float Volume)
{
	const int32 SIdx = SerialIndex(Idx);
	Volumes[SIdx] = Volume;

	OnVoxelDataModificated();
}

void AVoxelData::ClearVolumes()
{
	std::fill(Volumes.begin(), Volumes.end(), 0.f);

	OnVoxelDataModificated();
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
