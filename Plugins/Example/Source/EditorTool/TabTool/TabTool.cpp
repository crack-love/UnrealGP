#include "TabTool.h"
#include "TabToolPanel.h"
#include "EditorTool/EditorToolModule.h"

void TabTool::OnStartupModule()
{
	FExampleTabToolBase::OnStartupModule();
	FEditorToolModule::Get().AddMenuExtension(FMenuExtensionDelegate::CreateRaw(this, &TabTool::MakeMenuEntry), FName("Section_2"));
}

void TabTool::OnShutdownModule()
{
	FExampleTabToolBase::OnShutdownModule();
}

void TabTool::Initialize()
{
	TabName = "TabTool";
	TabDisplayName = FText::FromString("Tab Tool");
	ToolTipText = FText::FromString("Tab Tool Window");
}

TSharedRef<SDockTab> TabTool::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(TabToolPanel)
			.Tool(SharedThis(this))
		];

	return SpawnedTab;
}
