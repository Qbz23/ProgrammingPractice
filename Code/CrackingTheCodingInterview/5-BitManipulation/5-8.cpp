// 5.8 Draw Line p116
//
// Imagine a screen is represented as an array of bytes 
// each bit represents a single pixel and the width 
// is divisible by 8.
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <vector> 
#include <cassert>

// X is in pixel frequency, y is at element frequency
struct LineInputData 
{
    LineInputData(uint32_t _x1, uint32_t _x2, uint32_t _y) : 
        x1(_x1), x2(_x2), y(_y) {}
    uint32_t x1;
    uint32_t x2;
    uint32_t y;
};

struct DrawLineInput 
{
    DrawLineInput(uint32_t w, uint32_t x1, uint32_t x2, uint32_t y) :
        width(w), line(x1, x2, y) {}
    uint32_t width; // How many pixels wide the screen is 
                    // Vector has (width >> 3)^2 elements 
                    // this repressents a "Width x (Width >> 3)" 
                    // pixel grid
    LineInputData line;
};

DEF_TESTDATA(DrawLineData, DrawLineInput, std::vector<uint8_t>);

std::vector<uint8_t> DrawLine(DrawLineInput& in)
{
    const uint32_t bitWidth = 8;
    // Validate Assumptions
    assert(
        in.line.x1 <= in.line.x2    && 
        in.line.x2 < in.width       &&
        in.line.y * bitWidth < in.width );

    // Setup initial screen to all zeroes 
    uint32_t widthElements = in.width / bitWidth;
    assert(in.width % bitWidth == 0);
    std::vector<uint8_t> output(widthElements * widthElements, 0);

    // Convert X pixel coordinates to element indices 
    uint32_t elementOffsetY = in.line.y * widthElements;
    uint32_t startElementIndex = elementOffsetY + (in.line.x1 / bitWidth);
    uint32_t endElementIndex = elementOffsetY + (in.line.x2 / bitWidth);

    const uint8_t allOnes = ~0;
    // Iterate over each element, setting its bits as appropriate 
    for(uint32_t i = startElementIndex; i <= endElementIndex; ++i)
    {
        // Edge elements can be partial 
        // Beginning of line
        if(i == startElementIndex)
        {
            uint32_t startBit = in.line.x1 % bitWidth;
            // Special case where all contained within bit
            if(i == endElementIndex)
            {
                uint32_t endBit = in.line.x2 % bitWidth; 
                uint32_t endShift = bitWidth - endBit - 1;
                uint8_t startBits = allOnes >> startBit;
                uint8_t endBits = allOnes << endShift;
                output[i] = startBits & endBits;
            }
            // Typical case where line continues into subsequent bits
            else 
            {
                output[i] = (allOnes >> startBit);
            }
        }
        // End of line
        else if(i == endElementIndex)
        {
            uint32_t endBit = in.line.x2 % bitWidth;
            uint32_t endShift = bitWidth - endBit - 1;
            output[i] = allOnes << endShift;
        }
        // Middle elements get fully set
        else 
        {
            output[i] = allOnes;
        }
    }

    return output;
}

int Cci::Run_5_8()
{
    const unsigned int kNumTestCases = 6;
    // The screens being used are Wx(W>>3), see above comments 
    // This could be more robust, but it'd be pretty annoying to test 
    // Might be worth to do a more robust version of this as a toy project 
    // at some point but I don't think that's necssary here 
    DrawLineData testCases[kNumTestCases] = {
        {{24, 9, 18, 1},                    {   0,              0,          0,
                                                0,              0b01111111, 0b11100000,
                                                0,              0,          0}},
        {{24, 1, 22, 0},                    {   0b01111111,     0b11111111, 0b11111110,
                                                0,              0,          0,
                                                0,              0,          0}},
        {{16, 0, 8, 0},                     {   0b11111111,     0b10000000, 
                                                0,              0}},    
        {{16, 7, 15, 1},                    {   0,              0,
                                                0b00000001,     0b11111111}},
        {{8,  1, 2, 0},                     {   0b01100000}},
        {{8,  1, 1, 0},                     {   0b01000000}}
                      
    };

    return TestRunner::RunTestCases<DrawLineInput, std::vector<uint8_t>, kNumTestCases>(testCases, &DrawLine);
}

