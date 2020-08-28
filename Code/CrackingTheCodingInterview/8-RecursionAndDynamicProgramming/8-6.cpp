// 8.6 - Towers of Hannoi
//
// 3 Towers of N disks of different sizes. Starts with disks sorted in 
// ascending order of size from top to bottom 
// 
// 1. Only 1 disk can move at a time 
// 2. A moved disk must immediately go on a tower 
// 3. A disk cannot be placed on top of a smlaller disk 
//
// Write a program to move the disks from the first to last tower 
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <cassert>
#include "../../Shared/DataStructures/Stack.h"

DEF_TESTDATA(MagicIndexData, std::vector<int>, uint32_t);

//
// Each move of N disks has a source stack, a dest stack, and a working stack 
// 
// 1 Disk 
// Source, Working, Dest - working irrelevant 
// 2 Disks 
// Source, Working, Dest 
//  1-2,    _,      _
//  2,      1,      _
//  _,      1,      2
//  _,      _,      1-2
// 3 Disks 
//  Start by solving n-1 with working as dest 
//  Source,     Dest,       Working
//  3,          1-2,        _
//  Now we can return to expected order
//  Source,     Working,    Dest     
//  3,          1-2,        _       # We move source to dest 
//  Working,    Source,     Dest
//  _           1-2,        3       # Now build up again 
//  1,          2,          3
//  1,          _,          2-3
//  _,          _,          1-2-3
//
// So Generally, to move N from src to dst 
//  if N > 2 
//      Solve for N-1
//      treat current working stack as new dest 
//      treat current dest as new working 
//  if N <= 2
//      src -> working
//      src -> dst 
//      working -> dst 
//
// When you've moved your N-1, build up, swapping working and source stacks 
//  Reducing stack size swaps working and dst 
//  Increasing stack size swaps working and source 
// 
//  Go through for N=4
//
//  s           w           d
//  1-2-3-4,    _,          _ 
//      Move 3 disks to working 
//  s           d           w
//          Move 2 disks to working 
//  s           w           d
//  2-3-4,      1,          _
//  3-4,        1,          2
//  3-4,        _,          1-2
//          Done with N=2, return to prev order 
//  s           d           w
//  3-4         _,          1-2,
//          Move yourself to dest 
//  s           d           w
//  4           3           1-2
//          Now you're building back up. Swap working and source
//  w           d           s
//  4           3           1-2
//          You need to move 2, which can be done simply
//  1-4         3,          2
//  1-4         2-3,        _
//  4,          1-2-3       _
//      Done with N=3, return to previous order 
//  s           w           d
//  4           1-2-3       _
//      Move yourself to dest 
//  s           w           d
//  _           1-2-3       4
//      Now you're building up again, swap working and source 
//  w           s           d
//  _           1-2-3       4
//          We move N-1 to working, swap working and dest /
//          N-1 is 2 so can be moved simply 
//  d           s           w
//  _           1-2-3       4
//  _           2-3,        1-4
//  2           3           1-4
//  1-2         3           4
//      Return out of that to previous 
//  w           s           d
//  1-2         3           4
//      Move yourself to dst
//  1-2         _           3-4
//      Building up, swap working and source
//  s           w           d
//  1-2         _           3-4
//  2           1           3-4
//  _           1           2-3-4
//  _           _           1-2-3-4
//          
//  Move N-1 to working 
//      Swap dest and working 
//  Move self to dest 
//      Return to previous stack states 
//  Move n-1 on working to dest 
//      Set source and working 
//

class Tower 
{
    public:
        static const unsigned int skNumTowers = 3;

        Tower(unsigned int N)
        {
            for(int i = (int)N; i >= 0; --i)
            {
                Towers[0].Push(i);
            }
        }
        Stack<unsigned int> Towers[skNumTowers];

        std::vector<unsigned int> GetFinalTower() const 
        {
            Stack<unsigned int> copy(Towers[skNumTowers - 1]);
            std::vector<unsigned int> result;
            while(!copy.Empty())
            {
                result.push_back(copy.Pop());
            }
            return result;
        }
};

static uint32_t MagicIndex(std::vector<int>& input)
{
    //return MagicIndexImpl(input, 0, (uint32_t)input.size());
}

int Cci::Run_8_6()
{
    //static const uint32_t NoSolution = (uint32_t)-1;
    //
    //const unsigned int kNumTestCases = 13;
    //MagicIndexData testCases[kNumTestCases] = {
    //    {{-1, 1, 3},                                1},     // Obvious solution
    //    {{0, 2, 3, 4, 5},                           0},     // Solution at first value 
    //    {{-1, 0, 1, 2, 4},                          4},     // Solution at last value 
    //    {{-8, 4, 0, 3, 7, 9},                       3},     // Simple but step up
    //    {{-8, 1, 3, 4, 5, 6},                       1},
    //    {{-1, 2, 3},                       NoSolution},     // Simple no solution
    //    {{1, 2, 4},                        NoSolution},     
    //    {{-1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, NoSolution},     // No solution deep left
    //    {{-1, 0, 1, 2, 3, 4, 5, 6, 7, 10}, NoSolution},     // No solution deep right
    //    {{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 
    //       9, 10, 12, 16, 18, 20, 21, 25},         12},     // Stress
    //    {{-2, -1, 2, 4, 5, 6, 7, 8, 9, 10,
    //       11, 12, 13, 16, 18, 20, 21, 25},         2},     
    //    {{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8,
    //       9, 10, 13, 16, 18, 20, 21, 25}, NoSolution},     // Stress no soln
    //    {{-2, -1, 3, 4, 5, 6, 7, 8, 9, 10,
    //      11, 12, 13, 16, 18, 20, 21, 25}, NoSolution},
    //};
    //
    //return TestRunner::RunTestCases<std::vector<int>, uint32_t, kNumTestCases>(testCases, &MagicIndex);

    return 0;
}
