// Fill out your copyright notice in the Description page of Project Settings.

#include "VoxelMeshActor.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "TransVDToDM3.h"
#include "TransDM3ToPMC.h"
#include "VoxelData.h"

AVoxelMeshActor::AVoxelMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// create components
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProceduralMesh->SetIsReplicated(false);
	SetRootComponent(ProceduralMesh);

	// default set
	CollisionOption = EVM_CollisionOption::All;
	NormalMode = EVM_NormalMode::Face;
	ComputeMode = EVM_ComputeMode::CPU;
}

void AVoxelMeshActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVoxelMeshActor, VoxelData);
}

void AVoxelMeshActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bNeedUpdateMesh)
	{
		bNeedUpdateMesh = false;
		UpdateMesh();
	}
}

void AVoxelMeshActor::SetFigure_Implementation(EVM_PrimitiveFigure Figure)
{
	if (Figure == EVM_PrimitiveFigure::FlatGround)
	{
		VoxelData.Clear();
		VoxelData.SetSize({ 10,10,10 });
		VoxelData.SetGap({ 1,1,1 });

		const FIntVector Size = VoxelData.GetSize();
		for (int i = 0; i < Size.X; ++i)
		{
			for (int j = 0; j < Size.Y; ++j)
			{
				VoxelData.SetVolume({ i,j,0 }, 1.0f);
			}
		}
	}
	else if (Figure == EVM_PrimitiveFigure::Filled)
	{
		VoxelData.Clear();
		VoxelData.SetSize({ 10,10,10 });
		VoxelData.SetGap({ 1,1,1 });

		const FIntVector Size = VoxelData.GetSize();
		for (int i = 0; i < Size.X; ++i)
		{
			for (int j = 0; j < Size.Y; ++j)
			{
				for (int k = 0; k < Size.Y - 1; ++k)
				{
					VoxelData.SetVolume({ i,j,k }, 1.0f);
				}
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("SetFigure Called"));
	UpdateMesh();
}

void AVoxelMeshActor::SetCollisionMode(EVM_CollisionOption Op)
{
	CollisionOption = Op;
	UpdateCollision();
}

void AVoxelMeshActor::SetNormalMode(EVM_NormalMode Mode)
{
	NormalMode = Mode;
}

void AVoxelMeshActor::SetComputeMode(EVM_ComputeMode Mode)
{
	ComputeMode = Mode;
}

void AVoxelMeshActor::SetWrapMode(bool bWrap)
{
	bWrapMesh = bWrap;
}

// query, physics, simple, async
void AVoxelMeshActor::UpdateCollision()
{
	// todo : to proceduralMesh Util 
	// func with bool option
	
	ProceduralMesh->bUseComplexAsSimpleCollision =
		(CollisionOption & EVM_CollisionOption::Simple) > EVM_CollisionOption::Never;
	ProceduralMesh->bUseAsyncCooking =
		(CollisionOption & EVM_CollisionOption::AsyncCooking) > EVM_CollisionOption::Never;
	const bool bQuery =
		(CollisionOption & EVM_CollisionOption::Query) > EVM_CollisionOption::Never;
	const bool bPhysics =
		(CollisionOption & EVM_CollisionOption::Physics) > EVM_CollisionOption::Never;

	if (!bQuery && !bPhysics)
	{
		ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else if (bQuery && !bPhysics)
	{
		ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else if (!bQuery && bPhysics)
	{
		ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}
	else if (bQuery && bPhysics)
	{
		ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AVoxelMeshActor::UpdateMesh()
{
	if (ComputeMode == EVM_ComputeMode::CPU)
	{
		FTransVDToDM3::TransformationCPU(VoxelData, &DynamicMesh);
		FTransDM3ToPMC::Transformation(&DynamicMesh, ProceduralMesh);
	}
	else
	{
		FTransVDToDM3::TransformationGPU(VoxelData, &DynamicMesh);
		// todo : callback
		// FTransDM3ToPMC::Transformation(&DynamicMesh, ProceduralMesh);
	}
}

void AVoxelMeshActor::QueueUpdateMesh()
{
	bNeedUpdateMesh = true;
}
