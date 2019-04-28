#include <vector>
#include <unordered_map>
#include "../Shared/NoisyObject.hpp"

template <typename T> 
void vectorTest(std::string title)
{
  std::cout << std::endl << title << std::endl << "=====" << std::endl;
  
  std::cout << "Constructing local" << std::endl;
  T obj;
  std::vector<T> vec;
  vec.reserve(5);
  
  std::cout << "Push Back local" << std::endl;
  vec.push_back(obj);
  
  std::cout << "Push Back temp" << std::endl;
  vec.push_back(T());
  
  std::cout << "Emplace Back local" << std::endl;
  vec.emplace_back(obj);
      
  std::cout << "Emplace Back temp" << std::endl;
  vec.emplace_back(T());

  
  std::cout << "Emplace Back variadic args" << std::endl;
  vec.emplace_back();
  
  std::cout << "End Test. Destruct local and " << vec.size() << " long vector" << std::endl;
}

template <typename T>
void mapTest(std::string title)
{
  std::cout << std::endl << title << std::endl << "=====" << std::endl;
  
  std::cout << "Constructing local" << std::endl;
  T obj; 
  std::unordered_map<int, T> map;
  map.reserve(7);
  
  std::cout << "Constructing local pair" << std::endl;
  std::pair<int, T> pair(0, obj);
  
  std::cout << "Insert local pair" << std::endl;
  map.insert(pair);
  
  std::cout << "Insert made pair" << std::endl;
  map.insert(std::make_pair<int, T&>(1, obj));
  
  std::cout << "Insert with initalizer list" << std::endl;
  map.insert({2, obj});
  
  std::cout << "Emplace local pair" << std::endl;
  map.emplace(pair);
  
  std::cout << "Emplace made pair" << std::endl;
  map.emplace(std::make_pair<int, T&>(3, obj));
  
  std::cout << "Emplace variadic args including local obj" << std::endl;
  map.emplace(4, obj);
    
  std::cout << "End Test. Destruct local, local pair, and " << map.size() << " long map" << std::endl;
}

int main()
{
  vectorTest<NoisyObject>("NoisyObject Vector Test");
  mapTest<NoisyObject>("NoisyObject Map Test");
  vectorTest<CompositeNoisyObject>("CompositeNoisyObject Vector Test");
  mapTest<CompositeNoisyObject>("CompositeNoisyObject Map Test");
}