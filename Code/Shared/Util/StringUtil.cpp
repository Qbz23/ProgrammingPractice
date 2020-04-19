#include "StringUtil.h"
#include <sstream>
#include "../../Shared/Logging/Logging.h"

namespace Util
{
    namespace String
    {
        std::vector<std::string> Tokenize(std::string str, char delimiter)
        {
            std::vector<std::string> out;
            std::stringstream ss(str);
            std::string token;
            while(std::getline(ss, token, delimiter))
            {
                if(!token.empty())
                {
                    out.push_back(token);
                }
            }
            
            return out;
        }

        bool WildcardMatch(std::string wildcardStr, std::string otherStr)
        {
            std::vector<std::string> tokens = Tokenize(wildcardStr, '*');
            if(tokens.empty())
            {
                if(!wildcardStr.empty())
                {
                    // Only expect this to be only wildcards
                    if(!wildcardStr[0] == '*')
                    {
                        Log::Debug("Hit unexpected case in WildcardMatch.\nWildcardStr: "  +
                                   wildcardStr + ", OtherStr: " + otherStr);
                    }
                    else 
                    {
                        // everything matches only wildcards
                        return true;
                    }
                }
                return false;
            }
            else 
            {
                // match if can find all the tokens in otherStr in the correct order
                int previousFindIndex = (int)otherStr.find(tokens[0]);
                if(previousFindIndex == -1 ||                        // first token not found or 
                  (wildcardStr[0] != '*' && previousFindIndex != 0)) // no wildcard prefix and first token not at beginning
                {
                    return false;
                }

                for(size_t i = 1; i < tokens.size(); ++i)
                {
                    int findIndex = (int)otherStr.find(tokens[i], previousFindIndex);
                    if(findIndex <= previousFindIndex)
                    {
                        return false;
                    }
                    previousFindIndex = findIndex;
                }

                // If wildcard suffix and got here, is a match
                if(wildcardStr[wildcardStr.size() - 1] == '*')
                {
                    return true;
                }
                else 
                {
                    // if no wildcard suffix, final token needs to line up with end of str
                    return previousFindIndex + tokens[tokens.size() - 1].size() == otherStr.size();
                }
            }
        }
    }
}