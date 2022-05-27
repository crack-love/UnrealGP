#pragma once

#include "IMarchingCubes.h"
#include "VoxelData.h"
#include "Util/DynamicVector.h"

class FMarchingCubesCPU : IMarchingCubes
{
public:
	void MarchingCubes(FMarchingCubesInput Input) override;
	void MarchingCubesWrap(FMarchingCubesInput Input) override;

public:	
	struct FCornerVertex
	{
		FVector Pos;
		float Volume;
	};

	struct FTriangleVertex
	{
		FVector3d Pos;
	};

	struct FTriangle
	{
		FTriangleVertex V1;
		FTriangleVertex V2;
		FTriangleVertex V3;
	};

	float ISOLevel = 0.0f;
	float VolumeMax = 0.95f;
	float VolumeMin = 0.05f;

private:
	void Clear();
	void SetConfig(FMarchingCubesInput Input);
	void SingleMarchingCube(int X, int Y, int Z);
	void SingleMarchingCubeWrap(int X, int Y, int Z);
	FCornerVertex GetInputVertex(int X, int Y, int Z);
	FCornerVertex GetInputVertexWrap(int X, int Y, int Z);
	FTriangleVertex InterpolateVerts(FCornerVertex Idx1, FCornerVertex Idx2);
	void AppendTriangle(FTriangle Triangle);
	
	FIntVector VSize;
	FVector VGap;
	UVoxelData* VoxelData;
	FDynamicMesh3* Mesh;
};