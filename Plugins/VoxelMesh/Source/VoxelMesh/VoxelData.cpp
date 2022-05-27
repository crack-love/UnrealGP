#include "VoxelData.h"

void FVoxelData::SetSize(FIntVector NewSize)
{
	if (NewSize == Size)
	{
		return;
	}

	Clear();

	int32 SSize = NewSize.X * NewSize.Y * NewSize.Z;
	Volumes.SetNumZeroed(SSize, true);
	Size = NewSize;
}

void FVoxelData::SetGap(FVector NewGap)
{
	Gap = NewGap;
}

FORCEINLINE void UVoxelData::SetVolume(FIntVector Idx, float Volume)
{
	int32 SIdx = SerialIndex(Idx);
	Volumes[SIdx] = Volume;
}

FORCEINLINE float UVoxelData::GetVolume(FIntVector Idx)
{
	int32 SIdx = SerialIndex(Idx);
	return Volumes[SIdx];
}

FORCEINLINE TArray<float> UVoxelData::GetVolumes()
{
	return Volumes;
}

FORCEINLINE FIntVector UVoxelData::GetSize()
{
	return Size;
}

FORCEINLINE FVector UVoxelData::GetGap()
{
	return Gap;
}

FORCEINLINE int32 UVoxelData::GetSerialIndex_Internal(FIntVector Idx, FIntVector Size)
{
	return Idx.X + Idx.Y * Size.X + Idx.Z * Size.X * Size.Y;
}

FORCEINLINE int32 UVoxelData::SerialIndex(FIntVector Idx)
{
	return GetSerialIndex(Idx, Size);
}

void UVoxelData::Clear()
{
	std::fill(Volumes.begin(), Volumes.end(), 0.f);
}

void UVoxelData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UVoxelData, Volumes);
	DOREPLIFETIME(UVoxelData, Size);
	DOREPLIFETIME(UVoxelData, Gap);

	UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
	if (BPClass) BPClass->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
}

bool UVoxelData::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	return true;
}