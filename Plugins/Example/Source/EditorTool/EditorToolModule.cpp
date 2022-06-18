#include "EditorToolModule.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"
#include "CustomDataType/ExampleDataTypeActions.h"
#include "CustomProjectSettings/ExampleSettings.h"
#include "DetailCustomization/ExampleActor.h"
#include "DetailCustomization/ExampleActorDetails.h"
#include "EditorMode/ExampleEdModeTool.h"
#include "MenuTool/MenuTool.h"
#include "TabTool/TabTool.h"

TSharedRef<FWorkspaceItem> FEditorToolModule::MenuRoot =
	FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

inline bool FEditorToolModule::IsAvailable()
{
	return FModuleManager::Get().IsModuleLoaded("EditorTool");
}

TSharedRef<FWorkspaceItem> FEditorToolModule::GetMenuRoot()
{
	return MenuRoot;
}

void FEditorToolModule::AddModuleListeners()
{
	// add tools later
	//ModuleListeners.Add(MakeShareable(new MenuTool));
	//ModuleListeners.Add(MakeShareable(new TabTool()));
	//ModuleListeners.Add(MakeShareable(new ExampleEdModeTool));
}

void FEditorToolModule::StartupModule()
{
	//////////////////
	return;
	///////////////////

	if (!IsRunningCommandlet())
	{
		FLevelEditorModule& LevelEditorModule =
			FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		
		LevelEditorMenuExtensibilityManager =
			LevelEditorModule.GetMenuExtensibilityManager();
		
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension(
			"Window",
			EExtensionHook::After,
			nullptr,
			FMenuBarExtensionDelegate::CreateRaw(
				this,
				&FEditorToolModule::MakePulldownMenu));
		
		LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);
	}

	// register custom layouts
	{
		static FName PropertyEditor("PropertyEditor");
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);
		PropertyModule.RegisterCustomClassLayout(AExampleActor::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FExampleActorDetails::MakeInstance));
	}
	
	// register custom types:
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		// add custom category
		EAssetTypeCategories::Type ExampleCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Example")), FText::FromString("Example"));
		// register our custom asset with example category
		TSharedPtr<IAssetTypeActions> Action = MakeShareable(new FExampleDataTypeActions(ExampleCategory));
		AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
		// saved it here for unregister later
		CreatedAssetTypeActions.Add(Action);
	}

	// register settings:
	{
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
		if (SettingsModule)
		{
			TSharedPtr<ISettingsContainer> ProjectSettingsContainer = SettingsModule->GetContainer("Project");
			ProjectSettingsContainer->DescribeCategory("ExampleCategory", FText::FromString("Example Category"), FText::FromString("Example settings description text here"));

			SettingsModule->RegisterSettings("Project", "ExampleCategory", "ExampleSettings",
				FText::FromString("Example Settings"),
				FText::FromString("Configure Example Settings"),
				GetMutableDefault<UExampleSettings>()
			);
		}
	}
	
	IEditorToolModule::StartupModule();
}

void FEditorToolModule::ShutdownModule()
{
	//////////////////
	return;
	///////////////////
	

	// unregister custom layouts
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout(AExampleActor::StaticClass()->GetFName());
	}

	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 i = 0; i < CreatedAssetTypeActions.Num(); ++i)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[i].ToSharedRef());
		}
	}

	// unregister settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule)
	{
		SettingsModule->UnregisterSettings("Project", "ExampleCategory", "ExampleSettings");
	}
	
	IEditorToolModule::ShutdownModule();
}

void FEditorToolModule::AddMenuExtension(
	const FMenuExtensionDelegate &extensionDelegate,
	FName extensionHook,
	const TSharedPtr<FUICommandList> &CommandList,
	EExtensionHook::Position position) const
{
	MenuExtender->AddMenuExtension(extensionHook, position, CommandList, extensionDelegate);
}

void FEditorToolModule::MakePulldownMenu(FMenuBarBuilder &menuBuilder)
{
	menuBuilder.AddPullDownMenu(
		FText::FromString("Example"),
		FText::FromString("Open the Example menu"),
		FNewMenuDelegate::CreateRaw(this, &FEditorToolModule::FillPulldownMenu),
		"Example",
		FName(TEXT("ExampleMenu"))
	);
}

void FEditorToolModule::FillPulldownMenu(FMenuBuilder &menuBuilder) const
{
	// just a frame for tools to fill in
	menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 1"));
	menuBuilder.AddMenuSeparator(FName("Section_1"));
	menuBuilder.EndSection();

	menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 2"));
	menuBuilder.AddMenuSeparator(FName("Section_2"));
	menuBuilder.EndSection();
}

IMPLEMENT_GAME_MODULE(FEditorToolModule, EditorTool)
