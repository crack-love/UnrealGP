// #include "TabTool.h"
//
// void FTabTool::OnStartupModule()
// {
// 	InitParam = GetInitParams();
//
// 	auto Spawner = FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
// 		InitParam.TabName,
// 		FOnSpawnTab::CreateRaw(this, &FTabTool::OnSpawnTab));
//
// 	Spawner.SetGroup(InitParam.TabRoot->GetMenuRoot());
// 	Spawner.SetDisplayName(InitParam.TabDisplayText);
// 	Spawner.SetTooltipText(InitParam.ToolTipText);
// }
//
// void FTabTool::OnShutdownModule()
// {
// 	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(InitParam.TabName);
// }
//
// TSharedRef<SDockTab> FTabTool::OnSpawnTab(const FSpawnTabArgs& TabSpawnArgs)
// {
// 	return SNew(SDockTab);
// }
//
// void FTabTool::MakeMenuEntry(FMenuBuilder& MenuBuilder)
// {
// 	FGlobalTabmanager::Get()->PopulateTabSpawnerMenu(MenuBuilder, InitParam.TabName);
// }
