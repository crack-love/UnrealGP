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


	// Objects only replicate from server to client. If we didn't guard this
	// the client would create the object just fine but it would get replaced
	// by the server version (more accurately the property would be replaced to
	// point to the version from the server. The one the client allocated would
	// eventually be garbage collected.
	// NOTE: Very important, objects Outer must be our Actor! (this)
	VoxelData = NewObject<UVoxelData>(this, TEXT("VoxelData"));
	VoxelData->SetSize({ 10,10,10 });
	VoxelData->SetGap({ 2,2,2 });

	// default set
	SetCollisionMode_Implementation(EVM_CollisionOption::All);
	SetNormalMode_Implementation(EVM_NormalMode::Face);
	SetComputeMode_Implementation(EVM_ComputeMode::CPU);
	SetFigure_Implementation(EVM_PrimitiveFigure::FlatGround);
}

bool AVoxelMeshActor::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	WroteSomething |= Channel->ReplicateSubobject(VoxelData, *Bunch, *RepFlags);

	return WroteSomething;
}

void AVoxelMeshActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVoxelMeshActor, VoxelData);
	DOREPLIFETIME(AVoxelMeshActor, NormalMode);
	DOREPLIFETIME(AVoxelMeshActor, CollisionOption);
	DOREPLIFETIME(AVoxelMeshActor, ComputeMode);
}

void AVoxelMeshActor::SetMesh_Implementation()
{
	// set voxelData


	UpdateMesh();
}

void AVoxelMeshActor::SetFigure_Implementation(EVM_PrimitiveFigure Figure)
{
	if (Figure == EVM_PrimitiveFigure::FlatGround)
	{
		VoxelData->Clear();
		VoxelData->SetSize({ 10,10,10 });
		VoxelData->SetGap({ 1,1,1 });

		for (int i = 0; i < VoxelData->GetSize().X; ++i)
		{
			for (int j = 0; j < VoxelData->GetSize().Y; ++j)
			{
				VoxelData->SetVolume({ i,j,0 }, 1.0f);
			}
		}
	}
	else if (Figure == EVM_PrimitiveFigure::Filled)
	{
		VoxelData->Clear();
		VoxelData->SetSize({ 10,10,10 });
		VoxelData->SetGap({ 2,2,2 });

		for (int i = 0; i < VoxelData->GetSize().X; ++i)
		{
			for (int j = 0; j < VoxelData->GetSize().Y; ++j)
			{
				for (int k = 0; k < VoxelData->GetSize().Y - 1; ++k)
				{
					VoxelData->SetVolume({ i,j,k }, 1.0f);
				}
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("SetFigure Called"));
	UpdateMesh();
}

void AVoxelMeshActor::SetCollisionMode_Implementation(EVM_CollisionOption Op)
{
	CollisionOption = Op;
	UpdateCollision();
}

void AVoxelMeshActor::SetNormalMode_Implementation(EVM_NormalMode Mode)
{
	NormalMode = Mode;
}

void AVoxelMeshActor::SetComputeMode_Implementation(EVM_ComputeMode Mode)
{
	ComputeMode = Mode;
}

void AVoxelMeshActor::UpdateCollision()
{
	// todo : to proceduralMesh Util 
	// func with bool option
	
	ProceduralMesh->bUseComplexAsSimpleCollision = (CollisionOption & EVM_CollisionOption::SimpleComplex) > EVM_CollisionOption::Never;
	ProceduralMesh->bUseAsyncCooking = (CollisionOption & EVM_CollisionOption::AsyncCooking) > EVM_CollisionOption::Never;

	bool bQuery = (CollisionOption & EVM_CollisionOption::Query) > EVM_CollisionOption::Never;
	bool bPhysics = (CollisionOption & EVM_CollisionOption::Physics) > EVM_CollisionOption::Never;

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
	if (VoxelData == nullptr) return;

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
