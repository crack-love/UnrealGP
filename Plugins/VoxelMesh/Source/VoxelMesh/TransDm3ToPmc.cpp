#include "TransDm3ToPmc.h"

#include "PmcSectionData.h"
#include "ProceduralMeshComponent.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "DynamicMesh/MeshNormals.h"
using namespace UE::Geometry;

void FTransDm3ToPmc::Transform(FDm3ToPmcInput Input)
{
	const bool bGenerateCollision = Input.bGenerateCollision;
	constexpr bool bUseUV0 = false;
	constexpr bool bUseVertexColors = false;
	
	UpdatePMCFromDynamicMesh_SplitTriangles(
		Input.DynamicMesh3,
		Input.ProceduralMesh,
		Input.SectionData,
		Input.NormalType,
		bUseUV0,
		bUseVertexColors,
		bGenerateCollision);

	// update material
	UMaterialInterface* UseMaterial = Input.ProceduralMesh->GetMaterial(0);
	if (UseMaterial == nullptr)
	{
		UseMaterial = UMaterial::GetDefaultMaterial(MD_Surface);
	}
	Input.ProceduralMesh->SetMaterial(0, UseMaterial);
}

void FTransDm3ToPmc::UpdatePMCFromDynamicMesh_SplitTriangles(
	FDynamicMesh3* DynamicMesh,
	UProceduralMeshComponent* ProceduralMesh,
	FPmcSectionData* SectionData,
	EDm3ToPmc_NormalType NormalType,
	bool bInitializeUV0,
	bool bInitializeVertexColors,
	bool bCreateCollision)
{
	// unpack
	int32 NumTriangles = DynamicMesh->TriangleCount();
	int32 NumVertices = DynamicMesh->VertexCount();
	TArray<FVector> &Vertices = SectionData->Vertices;
	TArray<FVector> &Normals = SectionData->Normals;
	TArray<int32> &Triangles = SectionData->Triangles;
	TArray<FVector2D> &UV0 = SectionData->UV0;	
	TArray<FLinearColor> &VtxColors = SectionData->VertexColors;
	TArray<FProcMeshTangent> &Tangents = SectionData->Tangents; // not supporting this for now
		
	// Get normals
	// vertex, face, tri normal
	const FDynamicMeshNormalOverlay* NormalOverlay = nullptr;
	FMeshNormals VertexNormals;
	bool bUseFaceNormals = false;
	bool bUsePerVertexNormals = false;
	if (NormalType == Face && DynamicMesh->HasAttributes())
	{
		NormalOverlay = DynamicMesh->Attributes()->PrimaryNormals();
		bUseFaceNormals = true;
	}
	else if (NormalType == Vertex)
	{
		VertexNormals.SetMesh(DynamicMesh);
		VertexNormals.ComputeVertexNormals();
		bUsePerVertexNormals = true;
	}
	
	// Get Uvs
	const FDynamicMeshUVOverlay* UVOverlay = nullptr;
	bool bUseUV0 = false;
	if (bInitializeUV0 && DynamicMesh->HasAttributes())
	{
		UVOverlay = DynamicMesh->Attributes()->PrimaryUV();
		bUseUV0 = true;
	}

	// Get vertex colors
	bool bUsePerVertexColors = false;
	if (bInitializeVertexColors && DynamicMesh->HasVertexColors())
	{
		bUsePerVertexColors = true;
	}

	// initialize buffer size
	Vertices.SetNumUninitialized(NumVertices);
	Normals.SetNumUninitialized(NumVertices);
	Triangles.SetNumUninitialized(NumTriangles * 3);
	if (bUseUV0)
	{
		UV0.SetNumUninitialized(NumVertices);
	}
	if (bUsePerVertexColors)
	{
		VtxColors.SetNumUninitialized(NumVertices);
	}
	
	int32 BufferIndex = 0;
	for (int32 Tid : DynamicMesh->TriangleIndicesItr())
	{
		FIndex3i TriVerts = DynamicMesh->GetTriangle(Tid);
		int32 Vid = 3 * (BufferIndex++);

		// Set vertex
		FVector3d Position[3];
		DynamicMesh->GetTriVertices(Tid, Position[0], Position[1], Position[2]);
		Vertices[Vid] = Position[0];
		Vertices[Vid + 1] = Position[1];
		Vertices[Vid + 2] = Position[2];

		// Set Normal
		if (bUsePerVertexNormals)
		{
			Normals[Vid] = VertexNormals[TriVerts.A];
			Normals[Vid + 1] = VertexNormals[TriVerts.B];
			Normals[Vid + 2] = VertexNormals[TriVerts.C];
		}
		else if (bUseFaceNormals)
		{
			FVector3f Normal[3];
			NormalOverlay->GetTriElements(Tid, Normal[0], Normal[1], Normal[2]);
			Normals[Vid] = (FVector)Normal[0];
			Normals[Vid + 1] = (FVector)Normal[1];
			Normals[Vid + 2] = (FVector)Normal[2];
		}
		else
		{
			FVector3d TriNormal = DynamicMesh->GetTriNormal(Tid);
			Normals[Vid] = TriNormal;
			Normals[Vid + 1] = TriNormal;
			Normals[Vid + 2] = TriNormal;
		}

		// SetUV
		if (bUseUV0)
		{
			FVector2f UV[3];
			UVOverlay->GetTriElements(Tid, UV[0], UV[1], UV[2]);
			UV0[Vid] = (FVector2D)UV[0];
			UV0[Vid + 1] = (FVector2D)UV[1];
			UV0[Vid + 2] = (FVector2D)UV[2];
		}

		// set vertex color
		if (bUsePerVertexColors)
		{
			VtxColors[Vid] = DynamicMesh->GetVertexColor(TriVerts.A);
			VtxColors[Vid + 1] = DynamicMesh->GetVertexColor(TriVerts.B);
			VtxColors[Vid + 2] = DynamicMesh->GetVertexColor(TriVerts.C);
		}
	
		Triangles[Vid] = Vid;
		Triangles[Vid + 1] = Vid + 1;
		Triangles[Vid + 2] = Vid + 2;
	}

	ProceduralMesh->CreateMeshSection_LinearColor(0,
		Vertices, Triangles, Normals, UV0, VtxColors, Tangents, bCreateCollision);
}

