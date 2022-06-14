#pragma once

#include "EditorToolExample/IEditorToolExampleModule.h"

class MenuTool :
	public IEditorToolExampleModuleListener,
	public TSharedFromThis<MenuTool>
{
public:
	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	void MakeMenuEntry(FMenuBuilder &menuBuilder);
	void MakeSubMenu(FMenuBuilder &menuBuilder);

protected:
	TSharedPtr<FUICommandList> CommandList;

	// UI Command functions
	void MenuCommand1();

private:
	void AddTagMenuWidget(FMenuBuilder &menuBuilder);
	FName TagToAdd;
	FReply AddTag();
	FText GetTagToAddText() const;
	void OnTagToAddTextCommited(const FText& InText, ETextCommit::Type CommitInfo);
};
