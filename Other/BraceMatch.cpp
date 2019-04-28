// Given a set of braces, determine whether or not theyre evenly matched 

#include "../Shared/TestRunner.hpp"
#include "../Shared/DataStructures/Stack.hpp"

bool bracesValid(std::string& braceStr)
{
  Stack braces = Stack(std::vector<int>()); 
  for(auto it = braceStr.begin(); it != braceStr.end(); ++it)
  {
    switch(*it)
    {
      case '(':
      case '[':
      case '{':
      {
        braces.Push(*it);
        break;
      }
      case ')':
      {
        if(braces.Empty() || braces.Top() != (int)'(')
        {
          return false;
        }
        else
          braces.Pop();
        break;
      }
      case ']':
      {
        if(braces.Empty() || braces.Top() != (int)'[')
        {
          return false;
        }
        else
          braces.Pop();
        break;      
      }
      case '}':
      {
        if(braces.Empty() || braces.Top() != (int)'{')
        {
          return false;
        }
        else
          braces.Pop();
        break;
      }
    }
  }
    
  return braces.Empty();
}

DEF_TESTDATA(BracesValidData, std::string, bool)

int main()
{
  const unsigned int kNumTestCases = 5;
  BracesValidData testCases[kNumTestCases] = {
    {"({[]})",              true},
    {"([{]})",              false},
    {"({[]})({[]})",        true},
    {"({[]}))({[]})",       false},
    {"({[]}({[]})",         false},
  };
  
  testRunner::runTests<std::string, bool, kNumTestCases>(testCases, &bracesValid); 
}