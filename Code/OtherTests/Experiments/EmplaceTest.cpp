#include <vector>
#include <unordered_map>
#include "../OtherTests.h"
#include "../../Shared/Testing/NoisyObject.h"
#include "../../Shared//Logging/Logging.h"
#include "../OtherTestsLogFlags.h"

template <typename T> 
void VectorTest(std::string title)
{  
    Log::If(OtherTestsLogFlags::bLogExperiments, title);
    Log::If(OtherTestsLogFlags::bLogExperiments, "Constructing local: ");
    T obj;
    std::vector<T> vec;
    vec.reserve(5);
    
    Log::If(OtherTestsLogFlags::bLogExperiments, "Push Back local\n");
    vec.push_back(obj);
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "Push Back temp\n");
    vec.push_back(T());
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "Emplace Back local\n");
    vec.emplace_back(obj);
      
    Log::If(OtherTestsLogFlags::bLogExperiments, "Emplace Back temp\n");
    vec.emplace_back(T());

    Log::If(OtherTestsLogFlags::bLogExperiments, "Emplace Back variadic args\n");
    vec.emplace_back();
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "End test, vars will destruct");
}

template <typename T>
void MapTest(std::string title)
{
    Log::If(OtherTestsLogFlags::bLogExperiments, title);
    Log::If(OtherTestsLogFlags::bLogExperiments, "Constructing local: ");  T obj;
    std::unordered_map<int, T> map;
    map.reserve(7);
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "Constructing local pair\n");
    std::pair<int, T> pair(0, obj);
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "Insert local pair\n");
    map.insert(pair);
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "Insert made pair\n");
    map.insert(std::make_pair<int, T&>(1, obj));
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "Insert with initalizer list\n");
    map.insert({2, obj});
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "Emplace local pair\n");
    map.emplace(pair);
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "Emplace made pair\n");
    map.emplace(std::make_pair<int, T&>(3, obj));
  
    Log::If(OtherTestsLogFlags::bLogExperiments, "Emplace variadic args including local obj\n");
    map.emplace(4, obj);
    
    Log::If(OtherTestsLogFlags::bLogExperiments, "End Test. Destruct local, local pair, and " +  
        std::to_string(map.size()) + " long map\n");
}

int OtherTests::EmplaceTest()
{
    VectorTest<NoisyObject>("NoisyObject Vector Test");
    MapTest<NoisyObject>("NoisyObject Map Test");
    VectorTest<CompositeNoisyObject>("CompositeNoisyObject Vector Test");
    MapTest<CompositeNoisyObject>("CompositeNoisyObject Map Test");

    return 0;
}