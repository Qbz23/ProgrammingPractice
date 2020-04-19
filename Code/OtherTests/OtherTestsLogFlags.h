#pragma once

#include "../Shared/Logging/Logging.h"

namespace OtherTestsLogFlags
{
    static const int bLogDataStructureTestsVerbose = 1 << (Log::NumReservedLogFlags + 1);
    static const int bLogExperiments               = 1 << (Log::NumReservedLogFlags + 2);
};
