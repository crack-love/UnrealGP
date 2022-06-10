#pragma once
#include "ExampleSettings.generated.h"

UCLASS(config = EditorUserSettings, defaultconfig)
class UExampleSettings : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, config, Category = Test)
	bool bTest = false;
};

/*
To get access to this settings, do the following:

const UExampleSettings* ExampleSettings = GetDefault<UExampleSettings>();
if(ExampleSettings && ExampleSettings->bTest)
	// do something
*/
