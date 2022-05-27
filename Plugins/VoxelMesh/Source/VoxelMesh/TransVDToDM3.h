#pragma once

// GeometryProcessing Plugin
// DynamicMesh Module
#include "DynamicMesh3.h"

#include "VoxelData.h"
#include "MarchingCubesCPU.h"
#include "MarchingCubesGPU.h"

// Transform VoxelData to DynamicMesh3
class FTransVDToDM3
{
public:
	static void TransformationCPU(UVoxelData* InVoxelData, FDynamicMesh3* OutDynamicMesh)
	{
		FMarchingCubesInput Input;
		Input.InVoxelData = InVoxelData;
		Input.OutDynamicMesh = OutDynamicMesh;

		FMarchingCubesCPU MC;
		MC.MarchingCubes(Input);
	}

	static void TransformationGPU(UVoxelData* InVoxelData, FDynamicMesh3* InOutDynamicMesh)
	{

	}
};