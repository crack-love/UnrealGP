#pragma once

#include "AssetTypeActions_Base.h"
#include "ExampleData.h"

class FExampleDataTypeActions : public FAssetTypeActions_Base
{
public:
	FExampleDataTypeActions(EAssetTypeCategories::Type InAssetCategory);

	// IAssetTypeActions interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
	// End of IAssetTypeActions interface

	// for reimport
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
    void ExecuteReimport(TArray<TWeakObjectPtr<UExampleData>> Objects);
	
	private:
	EAssetTypeCategories::Type MyAssetCategory;
};
