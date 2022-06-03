#include "VoxelMeshTools.h"

FTransVdToDm3* FVoxelMeshTools::VdToDm3 = nullptr;
FTransDm3ToPmc* FVoxelMeshTools::Dm3ToPm = nullptr;
FMarchingCubesCpu* FVoxelMeshTools::McCpu = nullptr;
FMarchingCubesGpu* FVoxelMeshTools::McGpu = nullptr;
