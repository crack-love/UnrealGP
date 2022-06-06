#pragma once
#include "UnrealEd.h"
#include "ExampleDataFactory.generated.h"

UCLASS()
class UExampleDataFactory : public UFactory
{
	// If you want to have custom editor for the data, you can follow "Customize Details Panel" section to create custom widget. Or you can override OpenAssetEditor function in ExampleDataTypeActions, to create a complete different editor. We are not going to dive in here, search "OpenAssetEditor" in Unreal engine for examples.
	
	GENERATED_UCLASS_BODY()
public:
	// not using (other example that create new data)
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;	
	
	virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;
	
	virtual bool FactoryCanImport(const FString& Filename) override;

	// helper function
	static void MakeExampleDataFromText(class UExampleData* Data, const TCHAR*& Buffer, const TCHAR* BufferEnd);
};
