#include "Dbghlp.h"


// ctor
DbghlpDll::DbghlpDll()
: DllHandle(("dbghelp.dll"))
{
    if (handle_ && init())
    {
        // turn on default options
        DWORD dwOptions = this->SymGetOptions();
        dwOptions |= SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_DEBUG;
        this->SymSetOptions(dwOptions);
    }
    else
    {
        LOG_LAST_ERROR();
    }
}

// dctor
DbghlpDll::~DbghlpDll()
{
    this->SymCleanup(GetCurrentProcess());
}

BOOL DbghlpDll::init()
{
    SymGetOptions = (SymGetOptions_t)GetFuncAddress(("SymGetOptions"));
    SymSetOptions = (SymSetOptions_t)GetFuncAddress(("SymSetOptions"));
    SymInitialize = (SymInitialize_t)GetFuncAddress(("SymInitialize"));
    SymCleanup = (SymCleanup_t)GetFuncAddress(("SymCleanup"));
    StackWalk = (StackWalk_t)GetFuncAddress(("StackWalk"));
    SymFromAddr = (SymFromAddr_t)GetFuncAddress(("SymFromAddr"));
    SymFunctionTableAccess = (SymFunctionTableAccess_t)GetFuncAddress(("SymFunctionTableAccess"));
    SymGetModuleBase = (SymGetModuleBase_t)GetFuncAddress(("SymGetModuleBase"));
    SymGetLineFromAddr = (SymGetLineFromAddr_t)GetFuncAddress(("SymGetLineFromAddr"));
    SymSetContext = (SymSetContext_t)GetFuncAddress(("SymSetContext"));
    SymEnumSymbols = (SymEnumSymbols_t)GetFuncAddress(("SymEnumSymbols"));
    SymGetTypeInfo = (SymGetTypeInfo_t)GetFuncAddress(("SymGetTypeInfo"));
    EnumerateLoadedModules = (EnumerateLoadedModules_t)GetFuncAddress(("EnumerateLoadedModules"));
    MiniDumpWriteDump = (MiniDumpWriteDump_t)GetFuncAddress(("MiniDumpWriteDump"));

    return (SymGetOptions && SymSetOptions && SymInitialize && SymCleanup
        && StackWalk && SymFromAddr && SymFunctionTableAccess && SymGetModuleBase
        && SymGetLineFromAddr && SymSetContext && SymEnumSymbols
        && SymGetTypeInfo && EnumerateLoadedModules && MiniDumpWriteDump);
}

// DbgHelp dll wrapper object
DbghlpDll&  GetDbghelpDll()
{
    static DbghlpDll   instance;
    return instance;
}