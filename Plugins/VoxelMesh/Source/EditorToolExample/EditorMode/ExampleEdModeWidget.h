#pragma once

#include "Framework/Application/SlateApplication.h"
//#include "SlateApplication.h"

class SExampleEdModeWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SExampleEdModeWidget)
	{
		
	}
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs);

	// Util Functions
	class FExampleEdMode* GetEdMode() const;
};
