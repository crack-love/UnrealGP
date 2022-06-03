#pragma once

namespace UE::Geometry{ class FDynamicMesh3; }
class AVoxelData;

struct FVdToDm3Input
{
	AVoxelData* InData;
	UE::Geometry::FDynamicMesh3* OutMesh;
	bool bWrap;
};

// Transform VoxelData to DynamicMesh3
class FTransVdToDm3
{
public:
	void TransformCpu(FVdToDm3Input Input);
	
	void TransformGpu(FVdToDm3Input Input);
};
