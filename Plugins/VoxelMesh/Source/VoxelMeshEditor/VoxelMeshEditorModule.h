#pragma once

#include "UnrealEd.h"
#include "ListenableModule.h"

class FVoxelMeshEditorModule final : public FListenableModule
{
public:
	virtual void StartupModule() override;
	
	virtual void ShutdownModule() override;
	
	virtual void AddModuleListeners() override;

	/* beg ITabToolMenuRoot */
	// virtual TSharedRef<FWorkspaceItem> GetMenuRoot()
	// {
	// 	return MenuRoot;
	// }
	/* end ITabToolMenuRoot */
	
	static FVoxelMeshEditorModule& Get()
	{		
		return FModuleManager::LoadModuleChecked<FVoxelMeshEditorModule>("EditorToolExample");
	}


	// static bool IsAvailable();
	//
	// static TSharedRef<FWorkspaceItem> GetMenuRoot();
	//
	// void AddMenuExtension(
	// 	const FMenuExtensionDelegate &extensionDelegate,
	// 	FName extensionHook,
	// 	const TSharedPtr<FUICommandList> &CommandList = nullptr,
	// 	EExtensionHook::Position position = EExtensionHook::Before) const;

protected:
	//static TSharedRef<FWorkspaceItem> MenuRoot;
	
	// void MakePulldownMenu(FMenuBarBuilder &menuBuilder);
	//
	// void FillPulldownMenu(FMenuBuilder &menuBuilder) const;
	//
	//
	// TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
	//
	// TSharedPtr<FExtender> MenuExtender;
	//
	// TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
