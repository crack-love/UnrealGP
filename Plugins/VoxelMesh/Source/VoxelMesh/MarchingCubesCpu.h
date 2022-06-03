#pragma once

class AVoxelData;
namespace UE::Geometry {class FDynamicMesh3;}

struct FMarchingCubesCpuInput
{
	AVoxelData* InData;
	UE::Geometry::FDynamicMesh3* OutMesh;
	bool bWrap;
};


class FMarchingCubesCpu
{
public:	
	float ISOLevel = 0.0f;
	float VolumeMax = 0.95f;
	float VolumeMin = 0.05f;
	
	void MarchingCubes(FMarchingCubesCpuInput Input);

private:
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
	
	void SingleMarchingCube(int X, int Y, int Z);
	FCornerVertex GetInputVertex(int X, int Y, int Z);
	FTriangleVertex InterpolateVerts(FCornerVertex Idx1, FCornerVertex Idx2);
	void AppendTriangle(FTriangle Triangle);
	void Clear();
	
	FIntVector VertexSize;
	FVector VertexGap;
	bool bWrap = true;
	AVoxelData* Data = nullptr;
	UE::Geometry::FDynamicMesh3* Mesh = nullptr;
};
