#include "VoxelMeshEdModeWidget.h"

#include "UnrealEd.h"
#include "VoxelMeshEdMode.h"

void SVoxelMeshEdModeWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 5.f, 0.f, 0.f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("This is a editor mode example.")))
			]
			// + SVerticalBox::Slot()
			// .AutoHeight()
			// .Padding(0.f, 5.f, 0.f, 0.f)
			// [
			// 	SNew(SHorizontalBox)
			// 	+ SHorizontalBox::Slot()
			// 	.AutoWidth()
			// 	.Padding(2, 0, 0, 0)
			// 	.VAlign(VAlign_Center)
			// 	[
			// 		SNew(SButton)
			// 		.Text(FText::FromString("Add"))
			// 		.OnClicked(this, &SVoxelMeshEdModeWidget::OnAddPoint)
			// 		.IsEnabled(this, &SVoxelMeshEdModeWidget::CanAddPoint)
			// 	]
			// 	+ SHorizontalBox::Slot()
			// 	.AutoWidth()
			// 	.VAlign(VAlign_Center)
			// 	.Padding(0, 0, 2, 0)
			// 	[
			// 		SNew(SButton)
			// 		.Text(FText::FromString("Remove"))
			// 		.OnClicked(this, &SVoxelMeshEdModeWidget::OnRemovePoint)
			// 		.IsEnabled(this, &SVoxelMeshEdModeWidget::CanRemovePoint)
			// 	]
			// ]
		]
	];
}

FExampleEdMode* SVoxelMeshEdModeWidget::GetEdMode() const
{
	return (FExampleEdMode*)GLevelEditorModeTools().GetActiveMode(FVoxelMeshEdMode::EM_VoxelMesh);
}

FReply SVoxelMeshEdModeWidget::OnAddPoint()
{
	//GetEdMode()->AddPoint();
	return FReply::Handled();
}

bool SVoxelMeshEdModeWidget::CanAddPoint() const
{
	//return GetEdMode()->CanAddPoint();
	return  true;
}

FReply SVoxelMeshEdModeWidget::OnRemovePoint()
{
	//GetEdMode()->RemovePoint();
	return FReply::Handled();
}

bool SVoxelMeshEdModeWidget::CanRemovePoint() const
{
	//return GetEdMode()->CanRemovePoint();
	return true;
}
