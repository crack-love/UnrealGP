// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelMeshModule.h"

#include "VoxelMeshTools.h"
#include "MarchingCubesCpu.h"
#include "MarchingCubesGpu.h"
#include "TransVdToDm3.h"
#include "TransDm3ToPmc.h"

#define LOCTEXT_NAMESPACE "FVoxelMeshModule"

void FVoxelMeshModule::StartupModule()
{
	FVoxelMeshTools::McCpu = new FMarchingCubesCpu();
	FVoxelMeshTools::McGpu = new FMarchingCubesGpu();
	FVoxelMeshTools::VdToDm3 = new FTransVdToDm3();
	FVoxelMeshTools::Dm3ToPm = new FTransDm3ToPmc();
}

void FVoxelMeshModule::ShutdownModule()
{
	delete FVoxelMeshTools::McCpu;
	delete FVoxelMeshTools::McGpu;
	delete FVoxelMeshTools::VdToDm3;
	delete FVoxelMeshTools::Dm3ToPm;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVoxelMeshModule, VoxelMesh)
