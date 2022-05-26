
#include "GpLog.h"
#include "Modules/ModuleManager.h"

class FGpModule : public FDefaultGameModuleImpl
{
	void StartupModule() override
	{
		//FGpLog::Log(TEXT("FGPModule::StartupModule"));
	}

	void ShutdownModule() override
	{
		//FGpLog::Log(TEXT("FGPModule::ShutdownModule"));
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FGpModule, GP, "")
