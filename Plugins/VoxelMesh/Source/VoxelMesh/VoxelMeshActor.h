// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicMesh3.h"
#include "ProceduralMeshComponent.h"

#include "VoxelMeshActorEnums.h"
#include "VoxelMeshActor.generated.h"

UCLASS(Blueprintable)
class VOXELMESH_API AVoxelMeshActor : public AActor
{
	GENERATED_BODY()

public:
	AVoxelMeshActor();

// Engine API
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

// Public API (Server)
public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetMesh();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetFigure(EVM_PrimitiveFigure Figure);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetCollisionMode(EVM_CollisionOption Op);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetNormalMode(EVM_NormalMode Mode);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetComputeMode(EVM_ComputeMode Mode);

private:
	UFUNCTION()
	void UpdateCollision();

	UFUNCTION()
	void UpdateMesh();

// Visible Variables (Replicated)
private:

	UPROPERTY(VisibleAnywhere, Category = CPP, ReplicatedUsing = UpdateMesh)
	EVM_NormalMode NormalMode;

	UPROPERTY(VisibleAnywhere, Category = CPP, ReplicatedUsing = UpdateCollision)
	EVM_CollisionOption CollisionOption;

	UPROPERTY(VisibleAnywhere, Category = CPP, Replicated)
	EVM_ComputeMode ComputeMode;

	UPROPERTY(VisibleAnywhere, Category = CPP, Replicated)
	bool bWrapMesh;

// Hidden Variables
private:
	UPROPERTY(ReplicatedUsing = UpdateMesh)
	class UVoxelData* VoxelData;

	class FDynamicMesh3 DynamicMesh;

	class UProceduralMeshComponent* ProceduralMesh;
};