#pragma once

#include "UnrealEd.h"
#include "ListenableModule.h"

class FVoxelMeshEditorModule final : public FListenableModule
{
public:
	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline FVoxelMeshEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FVoxelMeshEditorModule>("VoxelMeshEditor");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("VoxelMeshEditor");
	}

	virtual void StartupModule() override;
	
	virtual void ShutdownModule() override;
	
	virtual void AddModuleListeners() override;

	/* beg ITabToolMenuRoot */
	// virtual TSharedRef<FWorkspaceItem> GetMenuRoot()
	// {
	// 	return MenuRoot;
	// }
	/* end ITabToolMenuRoot */
	
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
