#pragma once

#include <string>
#include <vector> 


namespace Util
{
    namespace String 
    {
        extern std::vector<std::string> Tokenize(std::string str, char delimiter);
        extern bool WildcardMatch(std::string wildcardStr, std::string otherStr);
    }
}
