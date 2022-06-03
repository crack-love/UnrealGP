#pragma once

#include "CoreMinimal.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "PmcSectionData.h"
#include "VoxelData.h"
#include "VoxelMesh.generated.h"

class UProceduralMeshComponent;

// VoxelMesh Normal Mode
UENUM(BlueprintType)
enum class EVM_NormalMode : uint8
{
	Split = 0,
	Vertex = 1,
	Face = 2,
};

// VoxelMesh Collision Mode (flags)
UENUM(BlueprintType, meta = (Bitflags))
enum class EVM_CollisionOption : uint8
{
	None = 0,
	Query = 1 << 0,
	Physics = 1 << 1,
	Simple = 1 << 2,
	AsyncCooking = 1 << 3,
	All = 255,
};

ENUM_CLASS_FLAGS(EVM_CollisionOption);

// VoxelMesh Marching-cubes Compute Mode
UENUM(BlueprintType)
enum class EVM_ComputeMode : uint8
{
	CPU = 0,
	GPU = 1,
};

// 복셀 데이터 -> 다이나믹 메쉬 -> 프로세듀얼 메쉬
UCLASS(Blueprintable)
class VOXELMESH_API AVoxelMesh : public AVoxelData
{
	GENERATED_BODY()

public:
	AVoxelMesh(const FObjectInitializer& Init);
	
	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual bool ShouldTickIfViewportsOnly() const override;

	virtual void OnVoxelDataModificated() override;
	
	/** Tick that runs ONLY in the editor viewport.*/
	UFUNCTION(BlueprintImplementableEvent, CallInEditor, Category = "Events")
	void BlueprintEditorTick(float DeltaSeconds);

	// Server interface
public:
	// interface
public:
	UFUNCTION(BlueprintCallable)
	void SetCollisionMode(EVM_CollisionOption Op);

	UFUNCTION(BlueprintCallable)
	void SetNormalMode(EVM_NormalMode Mode);

	UFUNCTION(BlueprintCallable)
	void SetComputeMode(EVM_ComputeMode Mode);

	UFUNCTION(BlueprintCallable)
	void SetWrapMode(bool bWrap);

private:
	void UpdateCollision() const;

	void UpdateMesh();
	
	UPROPERTY(EditAnywhere, Category=Voxel)
	bool bWrapMesh;

	UPROPERTY(EditAnywhere, Category=Voxel)
	EVM_NormalMode NormalMode;

	UPROPERTY(EditAnywhere, Category=Voxel)
	EVM_ComputeMode ComputeMode;

	UPROPERTY(EditDefaultsOnly, Category=Voxel, meta=(Bitflags))
	EVM_CollisionOption CollisionOption;

	UPROPERTY(EditAnywhere, Category=Voxel)
	bool bUseEditorTick = true;
	
	UPROPERTY()
	UProceduralMeshComponent* ProceduralMesh;

	FPmcSectionData ProceduralMeshSectionData;

	UE::Geometry::FDynamicMesh3 DynamicMesh;

	bool bNeedUpdateMesh;
};
