//#pragma once
//
//#include "CoreMinimal.h"
//#include "ProceduralMeshComponent.h"
//
//class VOXELMESH_API ProdeduralMeshComponentTool
//{
//public:
//	/**
//	 * Create/replace a section for this procedural mesh component.
//	 * @param	Vertices			Vertex buffer of all vertex positions to use for this mesh section.
//	 * @param	Triangles			Index buffer indicating which vertices make up each triangle. Length must be a multiple of 3.
//	 * @param	Normals				Optional array of normal vectors for each vertex. If supplied, must be same length as Vertices array.
//	 * @param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array.
//	 * @param	VertexColors		Optional array of colors for each vertex. If supplied, must be same length as Vertices array.
//	 * @param	Tangents			Optional array of tangent vector for each vertex. If supplied, must be same length as Vertices array.
//	 * @param	bCreateCollision	Indicates whether collision should be created for this section. This adds significant cost.
//	 */
//	static void CreateMesh(
//		UProceduralMeshComponent* SrcMesh,
//		TArray<FVector> CopyVertices,
//		TArray<FVector> CopyNormals,
//		TArray<int32> CopyTriangles,
//		TArray<FVector2D> CopyUV0,
//		bool bUseFaceNormals,
//		bool bCreateCollision);
//};