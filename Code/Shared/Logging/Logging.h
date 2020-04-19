#pragma once
#include <string>

class Log
{
public:
    static const int bLogTests             = 1 << 0;
    static const int bLogTestsVerbose      = 1 << 1;
    static const int bLogTestCases         = 1 << 2;
    static const int bLogTestCasesVerbose  = 1 << 3;
    static const int bLogNoisyObject       = 1 << 4;
    static const int NumReservedLogFlags   =      5;
    static const int bSharedLogFlags = (1 << NumReservedLogFlags) - 1;

    static void Enable(int flag);
    static void Disable(int flag);

    static void Always(std::string s);
    static void Debug(std::string s);
    static void If(int flag, std::string s);
    static void DebugIf(int flag, std::string s);

private:
    static uint32_t mFlags;
};
