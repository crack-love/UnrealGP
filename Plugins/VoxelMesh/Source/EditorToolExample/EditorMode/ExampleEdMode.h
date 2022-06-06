#pragma once
#include "EditorModes.h"
#include "EdMode.h"

class FExampleEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_Example;

	// FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;
};
