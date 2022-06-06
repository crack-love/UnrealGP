#include "ExampleEdModeWidget.h"
#include "UnrealEd.h"
#include "ExampleEdMode.h"
#include "ExampleEdModeWidget.h"
#include "Widgets/Layout/SScrollBox.h"

void SExampleEdModeWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("This is a editor mode example.")))
		]
	];
}

FExampleEdMode* SExampleEdModeWidget::GetEdMode() const
{
	return (FExampleEdMode*)GLevelEditorModeTools().GetActiveMode(FExampleEdMode::EM_Example);
}
