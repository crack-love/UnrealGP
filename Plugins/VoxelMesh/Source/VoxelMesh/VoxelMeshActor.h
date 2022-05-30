#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelMeshActor.generated.h"

class FDynamicMesh3;
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
	Never			= 0,
	Query			= 1 << 0,
	Physics			= 1 << 1,
	Simple			= 1 << 2,
	AsyncCooking	= 1 << 3,
	All				= 255,
};
ENUM_CLASS_FLAGS(EVM_CollisionOption);

// VoxelMesh Primitive Figure
UENUM(BlueprintType)
enum class EVM_PrimitiveFigure : uint8
{
	Filled = 0,
	FlatGround = 1,
};

// VoxelMesh Marching-cubes Compute Mode
UENUM(BlueprintType)
enum class EVM_ComputeMode : uint8
{
	CPU = 0,
	GPU = 1,
};

UCLASS(Blueprintable)
class VOXELMESH_API AVoxelMeshActor : public AActor
{
	GENERATED_BODY()

public:
	AVoxelMeshActor();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaSeconds) override;
	
	// Server interface
public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
	virtual void SetFigure(EVM_PrimitiveFigure Figure);

public:
	UFUNCTION(BlueprintCallable)
	void SetCollisionMode(EVM_CollisionOption Op);

	UFUNCTION(BlueprintCallable)
	void SetNormalMode(EVM_NormalMode Mode);

	UFUNCTION(BlueprintCallable)
	void SetComputeMode(EVM_ComputeMode Mode);

	UFUNCTION(BlueprintCallable)
	void SetWrapMode(bool bWrap);
	
	UFUNCTION()
	void UpdateCollision();

	UFUNCTION()
	void UpdateMesh();

	// Request to update mesh following next tick
	UFUNCTION()
	void QueueUpdateMesh();



private:

	int32 SerialIndex(FIntVector Idx) const;
	
private:
	UPROPERTY(ReplicatedUsing = QueueUpdateMesh)
	FVoxelData VoxelData;

	FDynamicMesh3* DynamicMesh;

	UProceduralMeshComponent* ProceduralMesh;

	bool bNeedUpdateMesh;
	
	bool bWrapMesh;
	
	EVM_NormalMode NormalMode;
	
	EVM_ComputeMode ComputeMode;
	
	EVM_CollisionOption CollisionOption;
};
