// Given a set of braces, determine whether or not theyre evenly matched 

#include "../../Shared/Testing/TestRunner.h"
#include "../../Shared/DataStructures/Stack.h"
#include "../OtherTests.h"

DEF_TESTDATA(BracesValidData, std::string, bool)

static bool BracesValid(std::string& braceStr)
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

int OtherTests::BraceMatch()
{
  const unsigned int kNumTestCases = 5;
  BracesValidData testCases[kNumTestCases] = {
    {"({[]})",              true},
    {"([{]})",              false},
    {"({[]})({[]})",        true},
    {"({[]}))({[]})",       false},
    {"({[]}({[]})",         false},
  };
  
  return TestRunner::RunTestCases<std::string, bool, kNumTestCases>(testCases, &BracesValid); 
}
