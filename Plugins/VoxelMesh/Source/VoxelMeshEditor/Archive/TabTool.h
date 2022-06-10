// #pragma once
//
// #include "ListenableModule.h"
//
// class ITabToolMenuRoot
// {
// public:
// 	virtual ~ITabToolMenuRoot() {}
// 	
// 	virtual TSharedRef<FWorkspaceItem> GetMenuRoot() = 0;
// };
//
// struct FTabToolInitParam
// {
// 	ITabToolMenuRoot* TabRoot = nullptr;
// 	FName TabName;
// 	FText TabDisplayText;
// 	FText ToolTipText;
// };
//
// class FTabTool : public IModuleListener, public TSharedFromThis<FTabTool>
// {
// public:
// 	virtual void OnStartupModule() override;
//
// 	virtual void OnShutdownModule() override;
//
// 	virtual TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& TabSpawnArgs);
//
// 	virtual void MakeMenuEntry(FMenuBuilder &MenuBuilder);
//
// protected:
// 	virtual FTabToolInitParam GetInitParams() = 0;
//
// private:
// 	FTabToolInitParam InitParam;
// };
