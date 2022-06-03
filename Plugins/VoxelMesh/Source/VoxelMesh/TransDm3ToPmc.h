#pragma once

namespace UE::Geometry
{ class FDynamicMesh3; }
class UProceduralMeshComponent;
struct FPmcSectionData;

enum EDm3ToPmc_NormalType
{
	Triangle,
	Vertex,
	Face,
};

struct FDm3ToPmcInput
{
	UE::Geometry::FDynamicMesh3* DynamicMesh3;
	UProceduralMeshComponent* ProceduralMesh;
	FPmcSectionData* SectionData;
	EDm3ToPmc_NormalType NormalType;
	bool bGenerateCollision;
};

class FTransDm3ToPmc
{
public:
	void Transform(FDm3ToPmcInput Input);

private:
	void UpdatePMCFromDynamicMesh_SplitTriangles(
		UE::Geometry::FDynamicMesh3* DynamicMesh,
		UProceduralMeshComponent* ProceduralMesh,
		FPmcSectionData* SectionData,
		EDm3ToPmc_NormalType NormalType,
		bool bInitializeUV0,
		bool bInitializeVertexColors,
		bool bCreateCollision);
};
