#include "Logging.h"
#include <iostream>

uint32_t Log::mFlags = 0;

void Log::Enable(int flag)
{
    mFlags |= flag;
}

void Log::Disable(int flag)
{
    mFlags &= ~(flag);
}

static void LogImpl(std::string s)
{
    std::cout << s;
}

void Log::Always(std::string s)
{
    LogImpl(s);
}

void Log::Debug(std::string s)
{   
#if _DEBUG
    LogImpl(s);
#endif
}

void Log::If(int flag, std::string s)
{
    if((flag  & mFlags) != 0)
    {
        LogImpl(s);
    }
}

void Log::DebugIf(int flag, std::string s)
{
#if _DEBUG
    If(flag, s);
#endif
}
