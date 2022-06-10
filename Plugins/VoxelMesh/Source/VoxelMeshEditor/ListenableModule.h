#pragma once

class IModuleListener
{
	friend class FListenableModule;
	
public:
	virtual ~IModuleListener() = default;

protected:
	virtual void OnStartupModule() {}
	
	virtual void OnShutdownModule() {}
};

// Can have IModuleListeners
class FListenableModule : public IModuleInterface
{
protected:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

	virtual void AddModuleListeners() = 0;
	
	TArray<TSharedRef<IModuleListener>> ModuleListeners;
};
