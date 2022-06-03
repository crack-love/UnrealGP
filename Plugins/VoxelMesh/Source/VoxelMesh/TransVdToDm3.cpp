#pragma once

#include "TransVdToDm3.h"
#include "MarchingCubesCpu.h"
#include "MarchingCubesGPU.h"
#include "VoxelMeshTools.h"

void FTransVdToDm3::TransformCpu(FVdToDm3Input Input)
{
	FMarchingCubesCpuInput McInput;
	McInput.InData = Input.InData;
	McInput.OutMesh = Input.OutMesh;
	McInput.bWrap = Input.bWrap;

	FMarchingCubesCpu* Mc = FVoxelMeshTools::GetMarchingCubesCpu();
	Mc->MarchingCubes(McInput);
}

void FTransVdToDm3::TransformGpu(FVdToDm3Input Input)
{
	
}
