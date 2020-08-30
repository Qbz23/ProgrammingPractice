// 8.5 - Recursive Multiply
//
// Multiply two positive ints with a combination of 
// addition, subtraction, and bit shifting. 
// Ideally, minimize those operations
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <cassert>

//
// The obvious solution is just use addition but it isnt optimal 
//  10 * 4 = 10 + 10 + 10 + 10
// There are a number of additions equal to the smaller number being multiplied 
// 
// Bit shifts are probably going to be the most efficent ops available 
// 10 * 4 = 10 << 2
//
// Therefore I think this should probably set up the mult as a distrubtion 
// that can utilize bit shifts to do much of the work 
// 
// 21 * 48 = 21 * (3 * 16) = 21 << 4 * 3 = 336 + 336 + 336 
//  Here the obvious solution would have req 21 addition, instead 3 addition 1 shift 
//
// Scan left for first set bit to find largset factor that is a power of 2 
// 48 = 0b110000, only including up to first set bit is 0b10000 = 16
//
// If both inputs contain a power of two, they can be added together to shift 
//  24 * 56 = (8 * 3) * (8 * 7) = 3 * 7 << 6 = (7 + 7 + 7) << 6
//  
// If neither inputs contain a power of two (both have lsb set) should distribute to make 
// an input a power of two 
//  5 * 11 = (4 + 1) * 11 = 4 * 11 + 1 * 11 = 11 << 2 + 11
// This takes us from 5 -> 2. It's more dramatic with larger numbers 
//  259 * 254 = (256 + 3) * 254 = 254 * 256 + 254 * 3 = 254 << 8 + 254 + 254 + 254 
//  The brute force method would be 254 operations here and we're down to 4 
//
// It may be worthwhile to apply that process to both sides, which will be clearer 
// with a larger delta from a prime 
//      383 * 97 
//      (256+127) * (128 - 31)
//      256 * 128 - 256 * 31 + 127 * 128 + 127 * -31
//      (1 << (8 + 7)) +
//          -31 << 7 +
//              127 << 7 +
//                  127 * -31 // Odd times odd again, recurse
//
// Another consideration is when to stop recursing. I think it's 3 
//  3 * x = x + x + x 
//  (3 - 1) * x = x << 1 - x 
// Same number of ops, so no need to break it up past x + x + x 
//
// Given two inputs 
//      If one is 3 or less 
//          Just do it with repeated addition 
//      If both are a power of two 
//          1 << (powA + powB)
//      Elif one is a power of two 
//          A << powB 
//      else 
//          Break up the inputs 
//          If both contain a power of 2 
//              (2PowA * RemainingA) * (2PowB * RemainingB)
//              RecursiveMultiply(RemainingA, RemainingB) << (PowA + PowB)
//          Else
//              Make non pow2 input pow2 via add/subtract 
//                  (2PowA * RemainingA) * (2PowB + DeltaB) 
//                  (RemainingA * (2PowB + DeltaB)) << PowA
//                  (RemainingA << 2PowB + RecursiveMultiply(RemainingA, DeltaB)) << PowA
//              Not too different for both having no pow2 
//                  (2PowA + DeltaA) * (2PowB + DeltaB)
//                  1 << (PowA + PowB) + DeltaA << PowB + DeltaB << PowA + ...
//                  ... RecursiveMultiply(DeltaA, DeltaB)
// 
// After implementing, I underestimated the amount of extra operations it would take to 
// determine things like nearest power of 2, Log2, etc. 
// This still ends up unquestionably better than repeated addition for large numbers 
// but there's probably a range of numbers greater than 3 where repeated addition is 
// actually the best solution in terms of number of relevant ops when you account for 
// the overhead ops to gather information about the numbers 
// Num of relevant ops for overhead...
//  IsPow2                  - 1 minus 
//  IntLog2Pow2             - 4 minus, 4 shifts (better than potentially checking all 32 bits though)
//  FactorInput             - BSF/BSR unsure re impl. 1 shit 1 minus 
//  WorstCase Factorization - 3 shifts, 3 adds (plus child calls) 
// So something like worst case 15 overhead ops per recursive call 
// By repeatedly going to pow2, can probably expect about Log2(N) levels 
// Only one potential recursive call, can't expand to N:1. 
// So if for a * b, min(a, b) = x
//  15Log2(x) <= x
//  https://www.symbolab.com/solver/inequalities-calculator/15%5Clog_%7B2%7D%5Cleft(X%5Cright)%20%3CX
//  Based on these estimations, repeated addition is better up to min = 100
//      15Log2(99) = 99.44, 99 is cheaper 
//      15Log2(100) = 99.65, 100 is more expensive
//  This value would be higher if there is a cost of bit scans that should be included  
//

struct RecursiveMultiplyInput
{
    uint32_t a;
    uint32_t b;
};

DEF_TESTDATA(RecursiveMultiplyData, RecursiveMultiplyInput, uint32_t);

//
// From stanford bit hacks 
// https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
//
uint32_t IntLog2Pow2(uint32_t x)
{
    const uint32_t b[] = 
        { 0xAAAAAAAA, 0xCCCCCCCC, 0xF0F0F0F0, 0xFF00FF00, 0xFFFF0000 };

    uint32_t result = (x & b[0]) != 0;
    for(int i = 4; i > 0; --i)
    {
        result |= ((x & b[i]) != 0) << i;
    }

    return result;
}

uint32_t RepeatedAddition(uint32_t a, uint32_t n)
{
    // Probably better to roll this into addition loop but the problem specifically 
    // calls for minimizing the number of additions/subtractions/shifts
    if(n == 0)
    {
        return 0;
    }
    uint32_t sum = a;

    for(uint32_t i = 0; i < n - 1; ++i)
    {
        sum += a;
    }

    return sum;
}

static void FactorInput(unsigned long n, unsigned long& pow2, unsigned long& other, bool& containsPow2)
{
    assert(n > 3);

    unsigned long lsb;
    _BitScanForward(&lsb, n);
    // Contains a power of 2 
    if (lsb > 0)
    {
        containsPow2 = true;
        pow2 = lsb;
        other = n >> pow2;
    }
    else
    {
        containsPow2 = false;
        // Find next lowest pow2 
        _BitScanReverse(&pow2, n);
        other = n - (1 << pow2);
    }
}

uint32_t RecursiveMultiply(uint32_t a, uint32_t b)
{
    // First base case, either value less than 3
    if(a <= 3 || b <= 3)
    {
        if(a < b)
        {
            return RepeatedAddition(b, a);
        }
        else 
        {
            return RepeatedAddition(a, b);
        }
    }

    bool aIsPow2 = !(a & (a-1));
    bool bIsPow2 = !(b & (b-1));
    if(aIsPow2)
    {
        return b << IntLog2Pow2(a);
    }
    else if(bIsPow2)
    {
        return a << IntLog2Pow2(b);
    }
    else 
    {
        bool containsPow2A;
        unsigned long powA;
        unsigned long otherA;
        FactorInput(a, powA, otherA, containsPow2A);

        bool containsPow2B;
        unsigned long powB;
        unsigned long otherB;
        FactorInput(b, powB, otherB, containsPow2B);

        if(containsPow2A && containsPow2B)
        {
            // (pow2A * otherA) * (pow2B * otherB)
            return RecursiveMultiply(otherA, otherB) << (powA + powB);
        }
        else if(containsPow2A)
        {
            // (pow2A * otherA) * (pow2B + otherB)      
            // (pow2B + otherB) * (pow2A * otherA)  
            // [pow2B * (pow2A * otherA)] + [otherB * (pow2A * otherA)] // Grouping not needed, organizational
            // [otherA << (powA + powB)]  + [(otherA * otherB) << powA]
            return (otherA << (powA + powB)) + (RecursiveMultiply(otherA, otherB) << powA);
        }
        else if(containsPow2B)
        {
            // (pow2A + otherA) * (pow2B * otherB)      
            // [pow2A * (pow2B * otherB)] + [otherA * (pow2B * otherB)]
            // [otherB << (powA + powB)]  + [(otherA * otherB) << powB]
            return (otherB << (powA + powB)) + (RecursiveMultiply(otherA, otherB) << powB);

        }
        else 
        {
            // (pow2A + otherA) * (pow2B + otherB)
            // (pow2A * pow2B) + (pow2a * otherB) + (otherA * pow2B) + (otherA * otherB)
            // [1 << (powA + powB)] + (otherB << powA) + (otherA << powB) + RecursiveMultiply(otherA, otherB)
            return (1 << (powA + powB)) + (otherB << powA) + (otherA << powB) + 
                RecursiveMultiply(otherA, otherB);
        }
    }

    // Should not get here
    assert(false);
    return -1;
}

static uint32_t SolveRecursiveMultiply(RecursiveMultiplyInput& params)
{
    return RecursiveMultiply(params.a, params.b);
}

int Cci::Run_8_5()
{
    const uint32_t kNumTestCases = 15;
    RecursiveMultiplyData testCases[kNumTestCases] = {
        {{1, 1},            1},        
        {{1, 2},            2},
        {{2, 3},            6},
        {{4, 5},            20},
        {{5, 12},           60},
        {{5, 6},            30},
        {{262144, 31},      8126464},   // one is pow2
        {{31, 262144},      8126464},   //
        {{262142, 48},      12582816},  // both contain pow 2 
        {{48, 262142},      12582816},  // 
        {{262142, 47},      12320674},  // One contains pow 2 
        {{47, 262142},      12320674},  // 
        {{262143, 47},      12320721},  // neither contain pow 2 
        {{47, 262143},      12320721},  // 
        {{54781, 26213},    1435974353} // stress
    };                      
   
    return TestRunner::RunTestCases<RecursiveMultiplyInput, uint32_t, kNumTestCases>(testCases, &SolveRecursiveMultiply);
}
