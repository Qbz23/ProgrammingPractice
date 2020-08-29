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

DEF_TESTDATA(HanoiData, uint32_t, bool);

class Hanoi
{
    public:
        static const uint32_t skNumTowers = 3;

        Hanoi(uint32_t N) : m_NumDisks(N)
        {
            for(uint32_t i = N; i > 0; --i)
            {
                m_Towers[0].Push(i);
            }
        }

        void MoveDisk(uint32_t src, uint32_t dst)
        {
            // Assert there's a source disk to move
            assert(!m_Towers[src].Empty());
            // Assert the move is valid 
            assert(m_Towers[dst].Empty() || m_Towers[src].Top() < m_Towers[dst].Top());
            m_Towers[dst].Push(m_Towers[src].Pop());
        }

        bool IsSolved() const 
        {
            // Ensure all disks ended up on the dst tower
            if(!m_Towers[0].Empty() || 
               !m_Towers[1].Empty() || 
                m_Towers[2].Size() != m_NumDisks)
            {
                Log::Debug("Hanoi Validation Failed, not all disks are on dst tower.\n");
                return false;
            }
            // Ensure disks are smallest -> largest 
            else 
            {            
                uint32_t prev = 0;
                Stack<uint32_t> dstTowerCopy(m_Towers[2]);
                while(!dstTowerCopy.Empty())
                {
                    uint32_t top = dstTowerCopy.Pop();
                    if(top < prev)
                    {
                        Log::Debug(
                            "Hanoi Validation Failed, popped " + std::to_string(top) + 
                            " which was less than prev disk " + std::to_string(prev) + "\n");
                        return false;
                    }
                    else 
                    {
                        top = prev;
                    }
                }
            }

            return true;
        }

    private:
        Stack<uint32_t> m_Towers[skNumTowers];
        const uint32_t m_NumDisks;
};

void MoveDiskStack(Hanoi& towers, uint32_t srcIndex, 
    uint32_t workingIndex, uint32_t dstIndex, uint32_t numDisks)
{
    if(numDisks == 1)
    {
        towers.MoveDisk(srcIndex, dstIndex);
    }
    else if(numDisks == 2)
    {
        towers.MoveDisk(srcIndex, workingIndex);
        towers.MoveDisk(srcIndex, dstIndex);
        towers.MoveDisk(workingIndex, dstIndex);
    }
    else // numDisks > 2
    {
        // Move N-1 to working, using current dst as working
        MoveDiskStack(towers, srcIndex, dstIndex, workingIndex, numDisks - 1);
        // Move yourself (the Nth disk) to dst 
        towers.MoveDisk(srcIndex, dstIndex);
        // Now source is empty and n-1 substack is on working
        // Move that n-1 substack to dst, using empty source as working
        MoveDiskStack(towers, workingIndex, srcIndex, dstIndex, numDisks - 1);
    }
}

static bool SolveHanoi(uint32_t& numDisks)
{
    Hanoi h(numDisks);
    MoveDiskStack(h, 0, 1, 2, numDisks);
    return h.IsSolved();
}

int Cci::Run_8_6()
{
    const uint32_t kNumTestCases = 7;
    HanoiData testCases[kNumTestCases] = {
        {1,     true},      // Expoentially starts slowing down in the low 20's. 
        {2,     true},      //  N = 1: 1 move 
        {3,     true},      //  N = 2: 3 moves
        {4,     true},      //  N = 3: 3 moves to working + self + 3 moves working->dst = 7
        {5,     true},      // 
        {16,     true},     // F(N) = 2 * F(N-1) + 1
        {17,     true}      // F(N) = 2^N - 1                      
    };                      // F(3) = 2^3 - 1 = 7
    
    // So O(2^n), which explains the explosion around the 20's
    // F(20) = 1048575, F(25) = 33554431, F(30) = 1073741823                                 

    return TestRunner::RunTestCases<uint32_t, bool, kNumTestCases>(testCases, &SolveHanoi);
}
