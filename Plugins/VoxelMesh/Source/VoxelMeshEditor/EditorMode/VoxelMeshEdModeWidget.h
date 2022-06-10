#pragma once

class SVoxelMeshEdModeWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVoxelMeshEdModeWidget)
	{
		
	}
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs);

	// Util Functions
	class FExampleEdMode* GetEdMode() const;

	// point
	FReply OnAddPoint();
	bool CanAddPoint() const;
	FReply OnRemovePoint();
	bool CanRemovePoint() const;
};
