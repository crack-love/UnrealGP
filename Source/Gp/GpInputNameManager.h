#pragma once

class FGpInputNameManager
{
public:
	static FName NAME_AxisMoveForward;
	static FName NAME_AxisMoveRight;
	static FName NAME_AxisLookRight;
	static FName NAME_AxisLookUp;
};

FName FGpInputNameManager::NAME_AxisMoveForward = FName(TEXT("MoveForward"));
FName FGpInputNameManager::NAME_AxisMoveRight = FName(TEXT("MoveRight"));
FName FGpInputNameManager::NAME_AxisLookRight = FName(TEXT("LookRight"));
FName FGpInputNameManager::NAME_AxisLookUp = FName(TEXT("LookUp"));