#pragma once

// VoxelMesh Normal Mode
UENUM(BlueprintType)
enum class EVM_NormalMode : uint8
{
	Split = 0,
	Vertex,
	Face,
};

// VoxelMesh Collision Mode
// UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
UENUM(BlueprintType, meta = (Bitflags))
enum class EVM_CollisionOption : uint8
{
	Never			= 0,
	Query			= 1 << 0,
	Physics			= 1 << 1,
	SimpleComplex	= 1 << 2,
	AsyncCooking	= 1 << 3,

	All				= 0b11111111,
};
ENUM_CLASS_FLAGS(EVM_CollisionOption);

// VoxelMesh Primitive Figure
UENUM(BlueprintType)
enum class EVM_PrimitiveFigure : uint8
{
	Filled = 0,
	FlatGround,
};

// VoxelMesh Marchingcubes Compute Mode
UENUM(BlueprintType)
enum class EVM_ComputeMode : uint8
{
	CPU = 0,
	GPU,
};