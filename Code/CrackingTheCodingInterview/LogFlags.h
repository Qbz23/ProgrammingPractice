#pragma once
#include "../Shared/Logging/Logging.h"

namespace LogFlags 
{
    // Open possibility of project specific logging
    static const int DummyLogFlag = 1 << (Log::NumReservedLogFlags + 1);
};
