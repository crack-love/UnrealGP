#include "ListenableModule.h"

void FListenableModule::StartupModule()
{
	if (!IsRunningCommandlet())
	{
		AddModuleListeners();
			
		for (int32 i = 0; i < ModuleListeners.Num(); ++i)
		{
			ModuleListeners[i]->OnStartupModule();
		}
	}
}

void FListenableModule::ShutdownModule()
{
	for (int32 i = 0; i < ModuleListeners.Num(); ++i)
	{
		ModuleListeners[i]->OnShutdownModule();
	}
}
