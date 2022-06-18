#include "VoxelMeshActor.h"

#include "ProceduralMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "VoxelData.h"
#include "TransVDToDM3.h"
#include "TransDm3ToPmc.h"
#include "VoxelMeshTools.h"

AVoxelMeshActor::AVoxelMeshActor(const FObjectInitializer& Init) : Super(Init)
{
	// actor set
	PrimaryActorTick.bCanEverTick = true;
	
	// create components
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProceduralMesh->SetIsReplicated(false);
	SetRootComponent(ProceduralMesh);

	// default set
	CollisionOption = EVM_CollisionOption::All;
	NormalMode = EVM_NormalMode::Face;
	ComputeMode = EVM_ComputeMode::CPU;
	bWrapMesh = true;

	bNeedUpdateMesh = true;
}

void AVoxelMeshActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	UpdateCollision();
}

void AVoxelMeshActor::Tick(const float DeltaSeconds)
{
#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaSeconds);

		// todo check property changed
		// ex normal mode, size, collision option
		// update
		
		if (bNeedUpdateMesh)
		{
			UE_LOG(LogTemp, Log, TEXT("Tick Update Mesh (Editor)"));
		
			bNeedUpdateMesh = false;
			UpdateMesh();
		}
	}
	else
#endif
	{
		Super::Tick(DeltaSeconds);
		
		if (bNeedUpdateMesh)
		{
			UE_LOG(LogTemp, Log, TEXT("Tick Update Mesh"));
		
			bNeedUpdateMesh = false;
			UpdateMesh();
		}
	}
}

bool AVoxelMeshActor::ShouldTickIfViewportsOnly() const
{
	// This ultimately is what controls whether or not it can even tick at all in the editor view port. 
	//But, it is EVERY view port so it still needs to be blocked from preview windows and junk.
	
	if (bUseEditorTick && GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AVoxelMeshActor::OnVoxelDataModificated()
{
	UE_LOG(LogTemp, Log, TEXT("OnVoxelDataModificated"));
	
	Super::OnVoxelDataModificated();
	bNeedUpdateMesh = true;
}

void AVoxelMeshActor::SetCollisionMode(const EVM_CollisionOption Op)
{
	CollisionOption = Op;
	UpdateCollision();
}

void AVoxelMeshActor::SetNormalMode(const EVM_NormalMode Mode)
{
	NormalMode = Mode;
}

void AVoxelMeshActor::SetComputeMode(const EVM_ComputeMode Mode)
{
	ComputeMode = Mode;
}

void AVoxelMeshActor::SetWrapMode(const bool bWrap)
{
	bWrapMesh = bWrap;
}

// query, physics, simple, async
void AVoxelMeshActor::UpdateCollision() const
{		
	ProceduralMesh->bUseComplexAsSimpleCollision =
		EnumHasAnyFlags(CollisionOption, EVM_CollisionOption::Simple);
		
	ProceduralMesh->bUseAsyncCooking =
		EnumHasAnyFlags(CollisionOption, EVM_CollisionOption::AsyncCooking);
		
	const bool bQuery =
		EnumHasAnyFlags(CollisionOption, EVM_CollisionOption::Query);
	
	const bool bPhysics =
		EnumHasAnyFlags(CollisionOption, EVM_CollisionOption::Physics);

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
	UE_LOG(LogTemp, Log, TEXT("UpdateMesh"));
	
	if (ComputeMode == EVM_ComputeMode::CPU)
	{
		FVdToDm3Input I0;
		I0.InData = this;
		I0.OutMesh = &DynamicMesh;
		I0.bWrap = bWrapMesh;
		FVoxelMeshTools::GetTransVdToDm3()->TransformCpu(I0);

		FDm3ToPmcInput I1;
		I1.DynamicMesh3 = &DynamicMesh;
		I1.ProceduralMesh = ProceduralMesh;
		I1.SectionData = &ProceduralMeshSectionData;
		I1.NormalType = static_cast<EDm3ToPmc_NormalType>(NormalMode);
		I1.bGenerateCollision = ProceduralMesh->GetCollisionEnabled() != ECollisionEnabled::NoCollision;
		FVoxelMeshTools::GetTransDm3ToPmc()->Transform(I1);
	}
	else
	{
		// VDToDM3.TransformGPU(this, &DynamicMesh, bWrapMesh);
		// todo : callback
		// FTransDM3ToPMC::Transformation(&DynamicMesh, ProceduralMesh);
	}
}
