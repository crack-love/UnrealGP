#pragma once

class IExampleEditorModuleListener
{
public:
    virtual ~IExampleEditorModuleListener() = default;
    
    virtual void OnStartupModule() {};
    virtual void OnShutdownModule() {};
};

class IExampleEditorModule : public IModuleInterface
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
    TArray<TSharedRef<IExampleEditorModuleListener>> ModuleListeners;
};
