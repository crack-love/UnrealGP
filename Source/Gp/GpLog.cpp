#include "GpLog.h"

#include "GameFramework/Actor.h"
#include "UObject/Object.h"

DEFINE_LOG_CATEGORY(LogGp);

void FGpLog::Log(const TCHAR* Msg, UObject* Context)
{
	FString Header = GetClientServerString(Context);

	UE_LOG(LogGp, Log, TEXT("%s : %s"), *Header, Msg);
}

void FGpLog::Screen(const FString& Msg, UObject* Context, int32 Key, float Time, FColor Color)
{
#if WITH_EDITOR
	if (GEngine == NULL) return;

	FString Header = GetClientServerString(Context);
	FString HeaderedMsg = FString::Printf(TEXT("[%s] %s"), *Header, *Msg);

	GEngine->AddOnScreenDebugMessage(Key, Time, Color, HeaderedMsg);
#endif
}

// branch of clientN, server, unkown?
FString FGpLog::GetClientServerString(UObject* Context)
{
	ENetRole Role = ROLE_None;

	if (AActor* Actor = Cast<AActor>(Context))
	{
		Role = Actor->GetLocalRole();
	}
	else if (UActorComponent* Component = Cast<UActorComponent>(Context))
	{
		Role = Component->GetOwnerRole();
	}

	if (Role != ROLE_None)
	{
		return (Role == ROLE_Authority) ? TEXT("Server") : TEXT("Client");
	}
	else
	{
#if WITH_EDITOR
		if (GIsEditor)
		{
			extern ENGINE_API FString GPlayInEditorContextString;
			return GPlayInEditorContextString;
		}
#endif
	}

	return TEXT("[]");
}
