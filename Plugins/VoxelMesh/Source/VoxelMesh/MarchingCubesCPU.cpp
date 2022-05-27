
#include "MarchingCubesCPU.h"
#include "MarchingCubesTable.h"
#include "Math/UnrealMathUtility.h"

void FMarchingCubesCPU::MarchingCubes(FMarchingCubesInput Input)
{
	SetConfig(Input);

	for (int i = 0; i < VSize.X - 1; ++i)
	{
		for (int j = 0; j < VSize.Y - 1; ++j)
		{
			for (int k = 0; k < VSize.Z - 1; ++k)
			{
				SingleMarchingCube(i, j, k);
			}
		}
	}

	Clear();
}

void FMarchingCubesCPU::MarchingCubesWrap(FMarchingCubesInput Input)
{

}

void FMarchingCubesCPU::Clear()
{
	VSize = FIntVector::ZeroValue;
	VGap = FVector::ZeroVector;
	VoxelData = nullptr;
	Mesh = nullptr;
}

void FMarchingCubesCPU::SetConfig(FMarchingCubesInput Input)
{
	VSize = Input.InVoxelData->GetSize();
	VGap = Input.InVoxelData->GetGap();
	VoxelData = Input.InVoxelData;
	Mesh = Input.OutDynamicMesh;
	Mesh->Clear();
}

void FMarchingCubesCPU::SingleMarchingCube(int X, int Y, int Z)
{
	// 8 corners of the current cube
	FCornerVertex cubeCorners[8];
	cubeCorners[0] = GetInputVertex(X, Y, Z);
	cubeCorners[1] = GetInputVertex(X + 1, Y, Z);
	cubeCorners[2] = GetInputVertex(X + 1, Y + 1, Z);
	cubeCorners[3] = GetInputVertex(X, Y + 1, Z);
	cubeCorners[4] = GetInputVertex(X, Y, Z + 1);
	cubeCorners[5] = GetInputVertex(X + 1, Y, Z + 1);
	cubeCorners[6] = GetInputVertex(X + 1, Y + 1, Z + 1);
	cubeCorners[7] = GetInputVertex(X, Y + 1, Z + 1);
	
	// Calculate unique index for each cube configuration.
	int cubeIndex = 0; // entierly inside
	if (cubeCorners[0].Volume <= ISOLevel)
		cubeIndex |= 1; // corner is outside
	if (cubeCorners[1].Volume <= ISOLevel)
		cubeIndex |= 2;
	if (cubeCorners[2].Volume <= ISOLevel)
		cubeIndex |= 4;
	if (cubeCorners[3].Volume <= ISOLevel)
		cubeIndex |= 8;
	if (cubeCorners[4].Volume <= ISOLevel)
		cubeIndex |= 16;
	if (cubeCorners[5].Volume <= ISOLevel)
		cubeIndex |= 32;
	if (cubeCorners[6].Volume <= ISOLevel)
		cubeIndex |= 64;
	if (cubeCorners[7].Volume <= ISOLevel)
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
		t.V1 = InterpolateVerts(cubeCorners[a0], cubeCorners[b0]);
		t.V2 = InterpolateVerts(cubeCorners[a1], cubeCorners[b1]);
		t.V3 = InterpolateVerts(cubeCorners[a2], cubeCorners[b2]);

		AppendTriangle(t);
	}
}

void FMarchingCubesCPU::SingleMarchingCubeWrap(int X, int Y, int Z)
{
	////	// kernel 1
	////	// wrap: vertexsize를 +2하여 배치콜해야 한다
	////	// wrap: 일반 버전 외곽을 엠티 버텍스로 감싼것으로 계산
	////	[numthreads(THREAD_SIZE_PER_GROUP, THREAD_SIZE_PER_GROUP, THREAD_SIZE_PER_GROUP)]
	////	void MarchingCubeWrap(int3 id : SV_DispatchThreadID)
	////	{
	////		if (id.x >= _VertexSize.x - 1 || id.y >= _VertexSize.y - 1 || id.z >= _VertexSize.z - 1)
	////		{
	////			return;
	////		}
	////
	////		// 8 corners of the current cube
	////		CornerVertex cubeCorners[8];
	////		cubeCorners[0] = GetInputVertexWrap(id.x, id.y, id.z);
	////		cubeCorners[1] = GetInputVertexWrap(id.x, id.y, id.z + 1);
	////		cubeCorners[2] = GetInputVertexWrap(id.x + 1, id.y, id.z + 1);
	////		cubeCorners[3] = GetInputVertexWrap(id.x + 1, id.y, id.z);
	////		cubeCorners[4] = GetInputVertexWrap(id.x, id.y + 1, id.z);
	////		cubeCorners[5] = GetInputVertexWrap(id.x, id.y + 1, id.z + 1);
	////		cubeCorners[6] = GetInputVertexWrap(id.x + 1, id.y + 1, id.z + 1);
	////		cubeCorners[7] = GetInputVertexWrap(id.x + 1, id.y + 1, id.z);
	////
	////		// Calculate unique index for each cube configuration.
	////		int cubeIndex = 0; // entierly inside
	////		if (cubeCorners[0].v <= ISO_LEVEL)
	////			cubeIndex |= 1; // corner is outside
	////		if (cubeCorners[1].v <= ISO_LEVEL)
	////			cubeIndex |= 2;
	////		if (cubeCorners[2].v <= ISO_LEVEL)
	////			cubeIndex |= 4;
	////		if (cubeCorners[3].v <= ISO_LEVEL)
	////			cubeIndex |= 8;
	////		if (cubeCorners[4].v <= ISO_LEVEL)
	////			cubeIndex |= 16;
	////		if (cubeCorners[5].v <= ISO_LEVEL)
	////			cubeIndex |= 32;
	////		if (cubeCorners[6].v <= ISO_LEVEL)
	////			cubeIndex |= 64;
	////		if (cubeCorners[7].v <= ISO_LEVEL)
	////			cubeIndex |= 128;
	////
	////		// Create triangles for current cube configuration
	////		for (uint i = 0; triangulation[cubeIndex][i] > -1; i += 3)
	////		{
	////			// 3 edges
	////			int a0 = cornerIndexAFromEdge[triangulation[cubeIndex][i]];
	////			int a1 = cornerIndexAFromEdge[triangulation[cubeIndex][i + 1]];
	////			int a2 = cornerIndexAFromEdge[triangulation[cubeIndex][i + 2]];
	////			int b0 = cornerIndexBFromEdge[triangulation[cubeIndex][i]];
	////			int b1 = cornerIndexBFromEdge[triangulation[cubeIndex][i + 1]];
	////			int b2 = cornerIndexBFromEdge[triangulation[cubeIndex][i + 2]];
	////
	////			Triangle t;
	////			t.v1 = InterpolateVerts(cubeCorners[a0], cubeCorners[b0]);
	////			t.v2 = InterpolateVerts(cubeCorners[a1], cubeCorners[b1]);
	////			t.v3 = InterpolateVerts(cubeCorners[a2], cubeCorners[b2]);
	////
	////			_Triangles.Append(t);
	////		}
	////	}
}

FMarchingCubesCPU::FCornerVertex FMarchingCubesCPU::GetInputVertex(int X, int Y, int Z)
{
	FCornerVertex Res;

	// pos
	Res.Pos = { X * VGap.X, Y * VGap.Y, Z * VGap.Z };// +_LeftBot;

	// tex
	// res.tex = BYTE.Load(_Textures, sidx, _IsLittleEndian).ToInt255();

	// v
	Res.Volume = VoxelData->GetVolume({ X,Y,Z });

	//res.mvidx = (x % 3) + (y % 3) * 3 + (z % 3) * 9;

	return Res;
}

FMarchingCubesCPU::FCornerVertex FMarchingCubesCPU::GetInputVertexWrap(int X, int Y, int Z)
{
	FCornerVertex Res;
//	int3 shiftedWrapVertex = _VertexSize - 2;
//
//	// shift left
//	x -= 1;
//	y -= 1;
//	z -= 1;
//
//	// Wraping vertex인 경우
//	if (x <= -1 || y <= -1 || z <= -1 ||
//		x >= shiftedWrapVertex.x ||
//		y >= shiftedWrapVertex.y ||
//		z >= shiftedWrapVertex.z)
//	{
//		// tex
//		res.tex = 0;
//
//		// volume
//		res.v = 0;
//
//		// positon
//		res.pos = float3(x * _VertexGap.x, y * _VertexGap.y, z * _VertexGap.z) + _LeftBot;
//	}
//	// Wraping vertex가 아닌 경우
//	else
//	{
//		int sidx = x + (y + z * shiftedWrapVertex.y) * shiftedWrapVertex.x;
//
//		// tex
//		res.tex = BYTE.Load(_Textures, sidx, _IsLittleEndian).ToInt255();
//
//		// volume
//		res.v = BYTE.Load(_Volumes, sidx, _IsLittleEndian).ToFloat01();
//
//		// positon
//		res.pos = float3(x * _VertexGap.x, y * _VertexGap.y, z * _VertexGap.z) + _LeftBot;
//	}
//
//	//res.mvidx = 0;
//
	return Res;
}

FMarchingCubesCPU::FTriangleVertex FMarchingCubesCPU::InterpolateVerts(FCornerVertex Idx1, FCornerVertex Idx2)
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
	vVolume.Volume = FMath::Lerp(VolumeMin, VolumeMax, vVolume.Volume);

	// 볼륨 1일시 포지션은 엠티쪽
	// 볼륨 0일시 포지션은 볼륨쪽
	res.Pos = FMath::Lerp(vVolume.Pos, vEmpty.Pos, vVolume.Volume);

	// 텍스는 볼륨쪽
	//res.tex = vVolume.tex;
	//res.mvidx = vVolume.mvidx;

	return res;
}

void FMarchingCubesCPU::AppendTriangle(FTriangle Triangle)
{
	int id0 = Mesh->AppendVertex(Triangle.V1.Pos);
	int id1 = Mesh->AppendVertex(Triangle.V2.Pos);
	int id2 = Mesh->AppendVertex(Triangle.V3.Pos);
	Mesh->AppendTriangle(id2, id1, id0);
}