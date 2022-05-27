//
//#pragma once
//
//// Core Module
//#include "Containers/Array.h" // tarray
//#include "Math/UnrealMathUtility.h" // vector
//#include "Templates/SharedPointer.h" // tweakptr
//
//// ProceduralMeshComponent Module
//#include "ProceduralMeshComponent.h"
//
//struct FMarchingCubesCPUInput
//{
//	TArray<float> Volumes;
//	FVector Size;
//	FVector Gap;
//	TWeakPtr<UProceduralMeshComponent> Mesh;
//};
//
//class VOXELMESH_API MarchingCubesCPU
//{
//public:
//	void MarchingCubes(FMarchingCubesCPUInput Input);
//	void MarchingCubesWrap(FMarchingCubesCPUInput Input);
//
//private:
//	CornerVertex GetInputVertex(int x, int y, int z);
//	CornerVertex GetInputVertexWrap(int x, int y, int z)
//	TriangleVertex InterpolateVerts(CornerVertex idx1, CornerVertex idx2)
//};