#pragma once

#include "IAssetTypeActions.h"
#include "UnrealEd.h"
#include "IEditorToolModule.h"

class FEditorToolModule : public IEditorToolModule
{
	/* IVoxelMeshEditorModule */
public:
	virtual void StartupModule() override;
	
	virtual void ShutdownModule() override;
	
	virtual void AddModuleListeners() override;

public:
	inline static FEditorToolModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FEditorToolModule>("EditorTool");
	}
	
	static bool IsAvailable();

	static TSharedRef<FWorkspaceItem> GetMenuRoot();

	void AddMenuExtension(
		const FMenuExtensionDelegate &extensionDelegate,
		FName extensionHook,
		const TSharedPtr<FUICommandList> &CommandList = nullptr,
		EExtensionHook::Position position = EExtensionHook::Before) const;

protected:
	void MakePulldownMenu(FMenuBarBuilder &menuBuilder);
	
	void FillPulldownMenu(FMenuBuilder &menuBuilder) const;

	static TSharedRef<FWorkspaceItem> MenuRoot;
	
	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
	
	TSharedPtr<FExtender> MenuExtender;
	
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
