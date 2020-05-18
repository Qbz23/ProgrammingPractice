// 3.6 Animal Shelter - p 99
//
// Use a linked list to implement fifo animal shelter policy 
// Can either request general oldest or oldest cat/dog 
//
#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <list>
#include <random>
#include <time.h>
#include <queue>
#include <cassert>

class AnimalShelter 
{
    public:
        struct AnimalInput
        {
            AnimalInput(int _id, bool _isDog) : id(_id), isDog(_isDog) {}
            int id;
            bool isDog;
        };

        AnimalShelter(std::vector<AnimalInput> input)
        {
            for(auto it = input.begin(); it != input.end(); ++it)
            {
                AddAnimal(*it);
            }
        }

        void AddDog(int id)
        {
            m_Dogs.emplace_front(id, m_AnimalCounter++);
        }

        void AddCat(int id)
        {
            m_Cats.emplace_front(id, m_AnimalCounter++);
        }

        int GetDog()
        {
            int val = m_Dogs.back().id;
            m_Dogs.pop_back();
            return val;
        }

        int GetCat()
        {
            int val = m_Cats.back().id;
            m_Cats.pop_back();
            return val;
        }

        int GetAnimal()
        {
            if(!m_Dogs.empty() && !m_Cats.empty())
            {
                if(m_Dogs.back().counter < m_Cats.back().counter)
                {
                    return GetDog();
                }
                else 
                {
                    return GetCat();
                }
            }
            else if(!m_Dogs.empty())
            {
                return GetDog();
            }
            else 
            {
                assert(!m_Cats.empty());
                return GetCat();
            }
        }

        bool DogsEmpty() const 
        {
            return m_Dogs.empty();
        }

        bool CatsEmpty() const
        {
            return m_Cats.empty();
        }

        bool Empty() const 
        {
            return m_Dogs.empty() && m_Cats.empty();
        }

        // for testing
        std::vector<int> GetData() const
        {
            AnimalShelter copy = AnimalShelter(*this);
            std::vector<int> output;
            while (!copy.Empty())
            {
                output.push_back(copy.GetAnimal());
            }
            return output;
        }

    private:
        void AddAnimal(AnimalInput input)
        {
            if(input.isDog)
            {
                AddDog(input.id);
            }
            else 
            {
                AddCat(input.id);
            }
        }

        // "Oldest" is based on arrival time
        // Newer animals have a higher counter 
        uint64_t m_AnimalCounter = 0;
        struct Animal
        {
            Animal(int _id, uint64_t _counter) : id(_id), counter(_counter) {}
            int id;
            uint64_t counter;
        };

        std::list<Animal> m_Dogs;
        std::list<Animal> m_Cats;
};

DEF_TESTDATA(AnimalShelterData, AnimalShelter, bool);

static bool ActualMatchesExpected(int actual, int expected)
{
    if (expected != actual)
    {
        std::string debugString = "Shuffle Shelter Failed! Actual: " + std::to_string(actual) +
            " doesn't match expected " + std::to_string(expected) + "\n";
        Log::Debug(debugString);
        return false;
    }
    else
    {
        return true;
    }
}

static void PushAnimal(AnimalShelter& shelter, std::queue<int>& expectedAnimals)
{
    int id = rand();
    bool bAddDog = rand() % 2;
    if(bAddDog)
    {
        shelter.AddDog(id);
    }
    else 
    {
        shelter.AddCat(id);
    }
    expectedAnimals.push(id);
}

static void PushAnimalSpecific(AnimalShelter& shelter, std::queue<int>& expectedDogs, std::queue<int>& expectedCats)
{
    int id = rand();
    bool bAddDog = rand() % 2;
    if (bAddDog)
    {
        shelter.AddDog(id);
        expectedDogs.push(id);
    }
    else
    {
        shelter.AddCat(id);
        expectedCats.push(id);
    }
}

// Pop an animal of either type, whatever's oldest at the shelter 
static bool PopAnimal(AnimalShelter& shelter, std::queue<int>& expectedAnimals)
{
    int actual = shelter.GetAnimal();
    int expected = expectedAnimals.front();
    expectedAnimals.pop();

    return ActualMatchesExpected(actual, expected);
}

// Pop a cat or dog specifically 
static bool PopAnimalSpecific(AnimalShelter& shelter, std::queue<int>& expectedDogs, std::queue<int>& expectedCats)
{
    int actual;
    int expected;
    if(shelter.DogsEmpty())
    {
        assert(!shelter.CatsEmpty());

        actual = shelter.GetCat();
        expected = expectedCats.front();
        expectedCats.pop();
    }
    else if(shelter.CatsEmpty())
    {
        actual = shelter.GetDog();
        expected = expectedDogs.front();
        expectedDogs.pop();
    }
    else 
    {
        // Has a cat and a dog pick randomly
        bool bGetDog = rand() % 2;
        if(bGetDog)
        {
            actual = shelter.GetDog();
            expected = expectedDogs.front();
            expectedDogs.pop();
        }
        else 
        {
            actual = shelter.GetCat();
            expected = expectedCats.front();
            expectedCats.pop();
        }
    }

    return ActualMatchesExpected(actual, expected);
}

// Similar to shuffle in 3-4 but doing a few things specific to this problem
static bool ShuffleShelter(AnimalShelter& shelter)
{
    // Shuffle is the real test, input data doesn't really signal anything other than ctor 
    // Ctor just calls add animal which is being tested here anyway 
    assert(shelter.Empty());

    srand((unsigned int)time(0)); // seed randomness
    const unsigned int numCycles = 6; // Number of times to push/pop
    const unsigned int numActions = 2049; // Number of pushes in each cycle
    unsigned int pushCounter; // Keeps track of how many things have been pushed/popped
    unsigned int popCounter;

    for (unsigned int n = 0; n < numCycles; ++n)
    {
        pushCounter = 0;
        popCounter = 0;
        std::queue<int> pushedDogs;
        std::queue<int> pushedCats;
        std::queue<int> pushedAnimals;

        // Alternate between using Get/Add Cat/Dog and using Get/Add Animal
        bool UseAnimalSpecific = n % 2;
        while (pushCounter < numActions)
        {
            // If nothing to pop, just push 
            // If something to pop, 50/50 chance to push or pop 
            bool shouldPop = popCounter < pushCounter && (rand() % 2);
            if(shouldPop)
            {
                bool succeeded = false;
                if (UseAnimalSpecific)
                {
                    succeeded = PopAnimalSpecific(shelter, pushedDogs, pushedCats);
                }
                else
                {
                    succeeded = PopAnimal(shelter, pushedAnimals);
                }

                popCounter += 1;
                if(!succeeded)
                {
                    return false;
                }
            }
            else 
            {
                if (UseAnimalSpecific)
                {
                    PushAnimalSpecific(shelter, pushedDogs, pushedCats);
                }
                else
                {
                    PushAnimal(shelter, pushedAnimals);
                }

                pushCounter += 1;
            }
        }

        // Pop off anythign remaining
        while (popCounter < numActions)
        {
            bool succeeded = false;
            if (UseAnimalSpecific)
            {
                succeeded = PopAnimalSpecific(shelter, pushedDogs, pushedCats);
            }
            else
            {
                succeeded = PopAnimal(shelter, pushedAnimals);
            }

            popCounter += 1;
            if (!succeeded)
            {
                return false;
            }
        }

        // Expect all queues to be empty
        assert(pushedDogs.empty() && pushedCats.empty() && pushedAnimals.empty());
    }

    
    return true;
}


int Cci::Run_3_6()
{
    const unsigned int kNumTestCases = 1; 
    AnimalShelterData testCases[kNumTestCases] = {
        {{{}},                          true}
    };
        
    return TestRunner::RunTestCases<AnimalShelter, bool, kNumTestCases>(testCases, &ShuffleShelter);
    return 0;
}

