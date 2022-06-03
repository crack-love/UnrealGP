
#include "MarchingCubesCpu.h"

#include "MarchingCubesTable.h"
#include "Math/UnrealMathUtility.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "VoxelData.h"

void FMarchingCubesCpu::Clear()
{
	VertexSize = FIntVector::ZeroValue; 
	VertexGap = FVector::ZeroVector;
	Data = nullptr;
	Mesh = nullptr;
	bWrap = false;
}

 auto FMarchingCubesCpu::GetInputVertex(int X, int Y, int Z) -> FCornerVertex
 {
	FCornerVertex Res;
	
	if (bWrap)
	{
		const int SizeX = VertexSize.X - 2;
		const int SizeY = VertexSize.Y - 2;
		const int SizeZ = VertexSize.Z - 2;
		X -= 1;
		Y -= 1;
		Z -= 1;

		// Wrapping vertex인 경우
		if (X <= -1 || Y <= -1 || Z <= -1 || X >= SizeX || Y >= SizeY || Z >= SizeZ)
		{
			Res.Volume = 0;
			Res.Pos = FVector(X * VertexGap.X, Y * VertexGap.Y, Z * VertexGap.Z);
			return Res;
		}
	}
		
	Res.Pos = { X * VertexGap.X, Y * VertexGap.Y, Z * VertexGap.Z };
	Res.Volume = Data->GetVolume({ X,Y,Z });
	return Res;
}

auto FMarchingCubesCpu::InterpolateVerts(FCornerVertex Idx1, FCornerVertex Idx2) -> FTriangleVertex
{
	FTriangleVertex res;
	FCornerVertex vEmpty;
	FCornerVertex vVolume;

	// split empty or volume
	// 여기 들어오는 두 버텍스는 엠티 or 볼륨 배타적(서로 다름) 상태이다
	if (Idx1.Volume <= 0)
	{
		vEmpty = Idx1;
		vVolume = Idx2;
	}
	else
	{
		vEmpty = Idx2;
		vVolume = Idx1;
	}

	// 볼륨 min max clamp
	vVolume.Volume = FMath::Lerp(
		FMarchingCubesCpu::VolumeMin,
		FMarchingCubesCpu::VolumeMax,
		vVolume.Volume);

	// 볼륨 1일시 포지션은 엠티쪽
	// 볼륨 0일시 포지션은 볼륨쪽
	res.Pos = FMath::Lerp(vVolume.Pos, vEmpty.Pos, vVolume.Volume);

	// 텍스는 볼륨쪽
	//res.tex = vVolume.tex;
	//res.mvidx = vVolume.mvidx;

	return res;
}

void  FMarchingCubesCpu::AppendTriangle(FTriangle Triangle)
{
	int id0 = Mesh->AppendVertex(Triangle.V1.Pos);
	int id1 = Mesh->AppendVertex(Triangle.V2.Pos);
	int id2 = Mesh->AppendVertex(Triangle.V3.Pos);
	Mesh->AppendTriangle(id2, id1, id0);
}

void  FMarchingCubesCpu::SingleMarchingCube(int X, int Y, int Z)
{
	// 8 corners of the current cube
	FCornerVertex CubeCorners[8];
	CubeCorners[0] = GetInputVertex(X, Y, Z);
	CubeCorners[1] = GetInputVertex(X + 1, Y, Z);
	CubeCorners[2] = GetInputVertex(X + 1, Y + 1, Z);
	CubeCorners[3] = GetInputVertex(X, Y + 1, Z);
	CubeCorners[4] = GetInputVertex(X, Y, Z + 1);
	CubeCorners[5] = GetInputVertex(X + 1, Y, Z + 1);
	CubeCorners[6] = GetInputVertex(X + 1, Y + 1, Z + 1);
	CubeCorners[7] = GetInputVertex(X, Y + 1, Z + 1);
	
	// Calculate unique index for each cube configuration.
	int cubeIndex = 0; // entierly inside
	if (CubeCorners[0].Volume <= FMarchingCubesCpu::ISOLevel)
		cubeIndex |= 1; // corner is outside
	if (CubeCorners[1].Volume <= FMarchingCubesCpu::ISOLevel)
		cubeIndex |= 2;
	if (CubeCorners[2].Volume <= FMarchingCubesCpu::ISOLevel)
		cubeIndex |= 4;
	if (CubeCorners[3].Volume <= FMarchingCubesCpu::ISOLevel)
		cubeIndex |= 8;
	if (CubeCorners[4].Volume <= FMarchingCubesCpu::ISOLevel)
		cubeIndex |= 16;
	if (CubeCorners[5].Volume <= FMarchingCubesCpu::ISOLevel)
		cubeIndex |= 32;
	if (CubeCorners[6].Volume <= FMarchingCubesCpu::ISOLevel)
		cubeIndex |= 64;
	if (CubeCorners[7].Volume <= FMarchingCubesCpu::ISOLevel)
		cubeIndex |= 128;

	// Create triangles for current cube configuration
	for (int32 i = 0; triangulation[cubeIndex][i] > -1; i += 3)
	{
		// 3 edges
		int32 a0 = cornerIndexAFromEdge[triangulation[cubeIndex][i]];
		int32 a1 = cornerIndexAFromEdge[triangulation[cubeIndex][i + 1]];
		int32 a2 = cornerIndexAFromEdge[triangulation[cubeIndex][i + 2]];
		int32 b0 = cornerIndexBFromEdge[triangulation[cubeIndex][i]];
		int32 b1 = cornerIndexBFromEdge[triangulation[cubeIndex][i + 1]];
		int32 b2 = cornerIndexBFromEdge[triangulation[cubeIndex][i + 2]];

		FTriangle t;
		t.V1 = InterpolateVerts(CubeCorners[a0], CubeCorners[b0]);
		t.V2 = InterpolateVerts(CubeCorners[a1], CubeCorners[b1]);
		t.V3 = InterpolateVerts(CubeCorners[a2], CubeCorners[b2]);

		AppendTriangle(t);
	}
}

void FMarchingCubesCpu::MarchingCubes(FMarchingCubesCpuInput Input)
{
	bWrap = Input.bWrap;
	VertexSize = Input.InData->GetSize();
	if (bWrap) VertexSize += FIntVector(2,2,2);
	VertexGap = Input.InData->GetGap();
	Data = Input.InData;
	Mesh = Input.OutMesh;
	Mesh->Clear();
		
	for (int i = 0; i < VertexSize.X - 1; ++i)
	{
		for (int j = 0; j < VertexSize.Y - 1; ++j)
		{
			for (int k = 0; k < VertexSize.Z - 1; ++k)
			{
				SingleMarchingCube(i, j, k);
			}
		}
	}
	
	Clear();
}
