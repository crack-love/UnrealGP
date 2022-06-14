#include "MenuTool.h"
#include "ExampleEditor/ExampleEditorModule.h"

#define LOCTEXT_NAMESPACE "MenuTool"

class MenuToolCommands : public TCommands<MenuToolCommands>
{
public:
	MenuToolCommands() :
	TCommands<MenuToolCommands>(
		TEXT("MenuTool"), // Context name for fast lookup
		FText::FromString("Example Menu tool"), // Context name for displaying
		NAME_None,   // No parent context
		FEditorStyle::GetStyleSetName() // Icon Style Set
		)
	{
	}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(MenuCommand1, "Menu Command 1", "Test Menu Command 1 Desc",
			EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(MenuCommand2, "Menu Command 2", "Test Menu Command 2 Desc",
			EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(MenuCommand3, "Menu Command 3", "Test Menu Command 3 Desc",
			EUserInterfaceActionType::Button, FInputChord());
	}

public:
	TSharedPtr<FUICommandInfo> MenuCommand1;
	TSharedPtr<FUICommandInfo> MenuCommand2;
	TSharedPtr<FUICommandInfo> MenuCommand3;
};

void MenuTool::OnStartupModule()
{
	// create commmand list
	CommandList = MakeShareable(new FUICommandList);

	// regist it
	MenuToolCommands::Register();

	// map it
	CommandList->MapAction(
		MenuToolCommands::Get().MenuCommand1,
		FExecuteAction::CreateSP(
			this, &MenuTool::MenuCommand1),
		FCanExecuteAction());

	// register to menu extension
	FExampleEditorModule::Get().AddMenuExtension(
		FMenuExtensionDelegate::CreateRaw(
			this,
			&MenuTool::MakeMenuEntry),
		FName("Section_1"),
		CommandList);
}

void MenuTool::OnShutdownModule()
{
	MenuToolCommands::Unregister();
}

void MenuTool::MakeMenuEntry(FMenuBuilder &menuBuilder)
{
	menuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand1);

	menuBuilder.AddSubMenu(
		FText::FromString("Sub Menu"),
		FText::FromString("This is example sub menu"),
		FNewMenuDelegate::CreateSP(
			this, &MenuTool::MakeSubMenu)
	);

	AddTagMenuWidget(menuBuilder);
}

void MenuTool::MakeSubMenu(FMenuBuilder &menuBuilder)
{
	menuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand2);
	menuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand3);
}

void MenuTool::AddTagMenuWidget(FMenuBuilder& menuBuilder)
{
	TSharedRef<SWidget> AddTagWidget =
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SEditableTextBox)
			.MinDesiredWidth(50)
			.Text(this, &MenuTool::GetTagToAddText)
			.OnTextCommitted(this, &MenuTool::OnTagToAddTextCommited)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(5, 0, 0, 0)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Text(FText::FromString("Add Tag"))
			.OnClicked(this, &MenuTool::AddTag)
		];

	menuBuilder.AddWidget(AddTagWidget, FText::FromString(""));
}

void MenuTool::MenuCommand1()
{
	UE_LOG(LogTemp, Log, TEXT("clicked MenuCommand1"));
}

FReply MenuTool::AddTag()
{
	if (!TagToAdd.IsNone())
	{
		const FScopedTransaction Transaction(
			FText::FromString("Add Tag"));

		for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
		{
			AActor* Actor = static_cast<AActor*>(*It);
			if (!Actor->Tags.Contains(TagToAdd))
			{
				Actor->Modify();
				Actor->Tags.Add(TagToAdd);
			}
		}
	}
	
	return FReply::Handled();
}

FText MenuTool::GetTagToAddText() const
{
	return FText::FromName(TagToAdd);
}

void MenuTool::OnTagToAddTextCommited(
	const FText& InText, ETextCommit::Type CommitInfo)
{
	FString str = InText.ToString();
	TagToAdd = FName(*str.TrimStartAndEnd());
}


#undef LOCTEXT_NAMESPACE
