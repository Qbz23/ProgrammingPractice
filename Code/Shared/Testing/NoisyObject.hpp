#include <iostream>

class NoisyObject 
{
  public:
  NoisyObject()                                   { std::cout << "\tNoisyObject Constructed" << std::endl; }
  ~NoisyObject()                                  { std::cout << "\tNoisyObject Destructed" << std::endl; }
  NoisyObject& operator=(const NoisyObject& rhs)  { std::cout << "\tNoisyObject Ref Operator=" << std::endl; }
  //Can this even happen?
  NoisyObject& operator=(const NoisyObject rhs)   { std::cout << "\tNoisyObject Value Operator=" << std::endl; }
  NoisyObject(const NoisyObject& rhs)             { std::cout << "\tNoisyObject Ref Copy Constructed" << std::endl; }
};

class CompositeNoisyObject
{
  public:
  CompositeNoisyObject()                                            { std::cout << "\tCompositeNoisyObject Constructed" << std::endl; }
  ~CompositeNoisyObject()                                           { std::cout << "\tCompositeNoisyObject Destructed" << std::endl; }
  CompositeNoisyObject& operator=(const CompositeNoisyObject& rhs)  { std::cout << "\tCompositeNoisyObject Ref Operator=" << std::endl; }
  CompositeNoisyObject& operator=(const CompositeNoisyObject rhs)   { std::cout << "\tCompositeNoisyObject Value Operator=" << std::endl; }
  CompositeNoisyObject(const CompositeNoisyObject& rhs)             { std::cout << "\tCompositeNoisyObject Ref Copy Constructed" << std::endl; }
  
  NoisyObject no1;
  NoisyObject no2;
};
