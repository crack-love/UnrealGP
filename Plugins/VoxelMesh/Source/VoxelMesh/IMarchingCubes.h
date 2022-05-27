#pragma once

#include "DynamicMesh3.h"
#include "VoxelData.h"

struct FMarchingCubesInput
{
	UVoxelData* InVoxelData;
	FDynamicMesh3* OutDynamicMesh;
};

class IMarchingCubes
{
public:
	virtual void MarchingCubes(FMarchingCubesInput Input) {}
	virtual void MarchingCubesWrap(FMarchingCubesInput Input) {}
};