#pragma once

class FGpInputNames
{
public:
	static FName NAME_AxisMoveForward;
	static FName NAME_AxisMoveRight;
	static FName NAME_AxisLookRight;
	static FName NAME_AxisLookUp;
};

FName FGpInputNames::NAME_AxisMoveForward = FName(TEXT("MoveForward"));
FName FGpInputNames::NAME_AxisMoveRight =	FName(TEXT("MoveRight"));
FName FGpInputNames::NAME_AxisLookRight =	FName(TEXT("LookRight"));
FName FGpInputNames::NAME_AxisLookUp =		FName(TEXT("LookUp"));