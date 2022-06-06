#pragma once

#include "ExampleTabToolBase.h"
#include "EditorToolExample/IEditorToolExampleModule.h"
#include "EditorToolExample/EditorToolExampleModule.h"

// slate module
#include "Framework/Docking/TabManager.h"
#include "widgets/Docking/SDockTab.h"

class FExampleTabToolBase :
public IEditorToolExampleModuleListener,
public TSharedFromThis<FExampleTabToolBase>
{
public:
	// IPixelopusToolBase
	virtual void OnStartupModule() override
	{
		Initialize();
		
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			TabName,
			FOnSpawnTab::CreateRaw(this, &FExampleTabToolBase::SpawnTab))
			.SetGroup(FEditorToolExampleModule::Get().GetMenuRoot())
			.SetDisplayName(TabDisplayName)
			.SetTooltipText(ToolTipText);
	};

	virtual void OnShutdownModule() override
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TabName);
	};

	// In this function set TabName/TabDisplayName/ToolTipText
	virtual void Initialize() {};
	
	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
	{
		return SNew(SDockTab);
	};

	virtual void MakeMenuEntry(FMenuBuilder &menuBuilder)
	{
		FGlobalTabmanager::Get()->PopulateTabSpawnerMenu(menuBuilder, TabName);
	};

protected:
	FName TabName;
	FText TabDisplayName;
	FText ToolTipText;
};
