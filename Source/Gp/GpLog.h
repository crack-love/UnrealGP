// #pragma once
//
// #include "Logging/LogMacros.h"
// #include "Containers/UnrealString.h"
//
// DECLARE_LOG_CATEGORY_EXTERN(GpLog, Log, All);
//
// // Literal Format with args to FString
// #define TEXTFSTR(FmtLit,...) FString::Printf(TEXT(FmtLit),##__VA_ARGS__)
//
// // Literal Format with args to const TCHAR*
// #define TEXTF(FmtLit,...) *TEXTFSTR(FmtLit,##__VA_ARGS__)
//
// class FGpLog
// {
// public:
// 	static void Log(const TCHAR* Msg, UObject* Context = nullptr);
//
// 	static void Screen(const FString& Msg, UObject* Context = nullptr, int32 Key = INDEX_NONE, float Time = 3.f, FColor Color = FColor::Green);
//
// private:
// 	static FString GetClientServerString(UObject* Context = nullptr);
// };
//
//
//
// //#define PI 3.1415926
// //#define MAX(a,b) (a)>(b) ? (a) :(b)
// //
// ////define 2 Assist Macro
// //#define   PRINT_MACRO_HELPER(x)   #x  
// //#define   PRINT_MACRO(x)   #x"="PRINT_MACRO_HELPER(x)  
// //
// ////print Macro content
// ////examples:
// //#pragma message(PRINT_MACRO(PI))
// //#pragma message(PRINT_MACRO(PI2))
// //#pragma message(PRINT_MACRO(MAX(a,b)))
// //#pragma message(PRINT_MACRO(MAX(x,y)))
// ////print ProjectName_API Macro
// //#pragma message(PRINT_MACRO(ProjectName_API))
