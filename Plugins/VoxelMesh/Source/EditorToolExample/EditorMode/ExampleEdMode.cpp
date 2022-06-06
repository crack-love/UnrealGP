#include "ExampleEdMode.h"
#include "ScopedTransaction.h"
#include "ExampleEdModeToolkit.h"

#include "Toolkits/ToolkitManager.h"

const FEditorModeID FExampleEdMode::EM_Example(TEXT("EM_Example"));

void FExampleEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid())
	{
		Toolkit = MakeShareable(new FExampleEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FExampleEdMode::Exit()
{
	FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
	Toolkit.Reset();

	FEdMode::Exit();
}
