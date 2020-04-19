#pragma once

#include "../Shared/Logging/Logging.h"

namespace OtherTestsLogFlags
{
    static const int LogDataStructureTestsVerbose = 1 << (Log::NumReservedLogFlags + 1);
};
