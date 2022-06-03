#pragma once
#include "VoxelMeshModule.h"

class FMarchingCubesCpu;
class FMarchingCubesGpu;
class FTransVdToDm3;
class FTransDm3ToPmc;

class FVoxelMeshTools
{
	friend class FVoxelMeshModule;
	
public:
	static FTransVdToDm3* GetTransVdToDm3() { return VdToDm3; }
	
	static FTransDm3ToPmc* GetTransDm3ToPmc() { return Dm3ToPm; }	

	static FMarchingCubesCpu* GetMarchingCubesCpu() { return McCpu; }
	
	static FMarchingCubesGpu* GetMarchingCubesGpu() { return McGpu; }

private:
	static FTransVdToDm3* VdToDm3;
	static FTransDm3ToPmc* Dm3ToPm;
	static FMarchingCubesCpu* McCpu;
	static FMarchingCubesGpu* McGpu;
};
