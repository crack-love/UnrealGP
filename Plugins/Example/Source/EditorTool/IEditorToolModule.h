#pragma once

#include "CoreGlobals.h"
#include "Containers/Array.h"
#include "Modules/ModuleInterface.h"
#include "Templates/SharedPointer.h"

class IEditorToolModuleListener
{
public:
    virtual ~IEditorToolModuleListener() = default;
    
    virtual void OnStartupModule() {};
    virtual void OnShutdownModule() {};
};

class IEditorToolModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        if (!IsRunningCommandlet())
        {
            AddModuleListeners();
            for (int i = 0; i < ModuleListeners.Num(); ++i)
            {
                ModuleListeners[i]->OnStartupModule();
            }
        }
    }

    virtual void ShutdownModule() override
    {
        for (int i = 0; i < ModuleListeners.Num(); ++i)
        {
            ModuleListeners[i]->OnShutdownModule();
        }
    }

    virtual void AddModuleListeners() {};

protected:
    TArray<TSharedRef<IEditorToolModuleListener>> ModuleListeners;
};
