#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"

// ProceduralMeshComponent Section Data
struct FPmcSectionData
{
	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<int32> Triangles;
	TArray<FVector2D> UV0;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;
};
