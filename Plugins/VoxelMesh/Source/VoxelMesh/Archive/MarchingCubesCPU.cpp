
#include "MarchingCubesCPU.h"
#include "MarchingCubesTable.h"
//
//// defines
//#define ISO_LEVEL 0
//#define VOLUME_MAX 0.95f // interpolate중 Volume쪽 적용 %
//#define VOLUME_MIN 0.05f // interpolate중 Volume쪽 적용 %
//
//// structs
//struct CornerVertex
//{
//	FVector pos;
//	int tex;
//	float v;
//};
//
//struct TriangleVertex
//{
//	float3 pos;
//	int tex;
//};
//
//struct Triangle
//{
//	TriangleVertex v1;
//	TriangleVertex v2;
//	TriangleVertex v3;
//};
//


//CornerVertex GetInputVertex(int x, int y, int z)
//{
//	CornerVertex res;
//	int sidx = x + y * _VertexSize.z + z * _VertexSize.x * _VertexSize.y;
//
//	// pos
//	res.pos = float3(x * _VertexGap.x, y * _VertexGap.y, z * _VertexGap.z) + _LeftBot;
//
//	// tex
//	res.tex = BYTE.Load(_Textures, sidx, _IsLittleEndian).ToInt255();
//
//	// v
//	res.v = BYTE.Load(_Volumes, sidx, _IsLittleEndian).ToFloat01();
//
//	//res.mvidx = (x % 3) + (y % 3) * 3 + (z % 3) * 9;
//
//	return res;
//}
//
//CornerVertex GetInputVertexWrap(int x, int y, int z)
//{
//	CornerVertex res;
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
//	return res;
//}
//
//TriangleVertex InterpolateVerts(CornerVertex idx1, CornerVertex idx2)
//{
//	TriangleVertex res;
//
//	CornerVertex vEmpty;
//	CornerVertex vVolume;
//
//	// split empty or volume
//	// 여기 들어오는 두 버텍스는 엠티 or 볼륨 배타적(서로 다름) 상태이다
//
//	if (idx1.v <= 0)
//	{
//		vEmpty = idx1;
//		vVolume = idx2;
//	}
//	else
//	{
//		vEmpty = idx2;
//		vVolume = idx1;
//	}
//
//	// 볼륨 min max clamp
//	vVolume.v = lerp(VOLUME_MIN, VOLUME_MAX, vVolume.v);
//
//	// 볼륨 1일시 포지션은 엠티쪽
//	// 볼륨 0일시 포지션은 볼륨쪽
//	res.pos = lerp(vVolume.pos, vEmpty.pos, vVolume.v);
//
//	// 텍스는 볼륨쪽
//	res.tex = vVolume.tex;
//
//	//res.mvidx = vVolume.mvidx;
//
//	return res;
//}
//
//void MarchingCubesCPU::MarchingCubeSingle(const FMarchingCubesCPUInput& Input, int x, int y, int z)
//{
//	TArray<float> Volumes = Input.Volumes;
//	FVector Size = Input.Size;
//	FVector Gap = Input.Gap;
//	TWeakPtr<UProceduralMeshComponent> Mesh = Input.Mesh;
//
//	// 8 corners of the current cube
//	CornerVertex cubeCorners[8];
//	cubeCorners[0] = GetInputVertex(id.x, id.y, id.z);
//	cubeCorners[1] = GetInputVertex(id.x, id.y, id.z + 1);
//	cubeCorners[2] = GetInputVertex(id.x + 1, id.y, id.z + 1);
//	cubeCorners[3] = GetInputVertex(id.x + 1, id.y, id.z);
//	cubeCorners[4] = GetInputVertex(id.x, id.y + 1, id.z);
//	cubeCorners[5] = GetInputVertex(id.x, id.y + 1, id.z + 1);
//	cubeCorners[6] = GetInputVertex(id.x + 1, id.y + 1, id.z + 1);
//	cubeCorners[7] = GetInputVertex(id.x + 1, id.y + 1, id.z);
//
//	// Calculate unique index for each cube configuration.
//	int cubeIndex = 0; // entierly inside
//	if (cubeCorners[0].v <= ISO_LEVEL)
//		cubeIndex |= 1; // corner is outside
//	if (cubeCorners[1].v <= ISO_LEVEL)
//		cubeIndex |= 2;
//	if (cubeCorners[2].v <= ISO_LEVEL)
//		cubeIndex |= 4;
//	if (cubeCorners[3].v <= ISO_LEVEL)
//		cubeIndex |= 8;
//	if (cubeCorners[4].v <= ISO_LEVEL)
//		cubeIndex |= 16;
//	if (cubeCorners[5].v <= ISO_LEVEL)
//		cubeIndex |= 32;
//	if (cubeCorners[6].v <= ISO_LEVEL)
//		cubeIndex |= 64;
//	if (cubeCorners[7].v <= ISO_LEVEL)
//		cubeIndex |= 128;
//
//	// Create triangles for current cube configuration
//	for (uint i = 0; triangulation[cubeIndex][i] > -1; i += 3)
//	{
//		// 3 edges
//		int a0 = cornerIndexAFromEdge[triangulation[cubeIndex][i]];
//		int a1 = cornerIndexAFromEdge[triangulation[cubeIndex][i + 1]];
//		int a2 = cornerIndexAFromEdge[triangulation[cubeIndex][i + 2]];
//		int b0 = cornerIndexBFromEdge[triangulation[cubeIndex][i]];
//		int b1 = cornerIndexBFromEdge[triangulation[cubeIndex][i + 1]];
//		int b2 = cornerIndexBFromEdge[triangulation[cubeIndex][i + 2]];
//
//		Triangle t;
//		t.v1 = InterpolateVerts(cubeCorners[a0], cubeCorners[b0]);
//		t.v2 = InterpolateVerts(cubeCorners[a1], cubeCorners[b1]);
//		t.v3 = InterpolateVerts(cubeCorners[a2], cubeCorners[b2]);
//
//		Mesh->Object->
//		_Triangles.Append(t);
//	}
//
//}
//
//void MarchingCubesCPU::MarchingCubesWrap(FMarchingCubesCPUInput Input)
//{
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
//}
//
//void MarchingCubesCPU::MarchingCubes(FMarchingCubesCPUInput Input)
//{
//
//	for (int i = 0; i < Size.X; ++i)
//	{
//		for (int j = 0; j < Size.Y; ++j)
//		{
//			for (int k = 0; k < Size.Z; ++k)
//			{
//
//			}
//		}
//	}
//
//
//}
