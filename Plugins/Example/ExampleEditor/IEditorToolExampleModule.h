#pragma once

class IEditorToolExampleModuleListener
{
public:
    virtual ~IEditorToolExampleModuleListener() = default;
    
    virtual void OnStartupModule() {};
    virtual void OnShutdownModule() {};
};

class IEditorToolExampleModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
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

    virtual void ShutdownModule() override
    {
        for (int32 i = 0; i < ModuleListeners.Num(); ++i)
        {
            ModuleListeners[i]->OnShutdownModule();
        }
    }

    virtual void AddModuleListeners() {};

protected:
    TArray<TSharedRef<IEditorToolExampleModuleListener>> ModuleListeners;
};
