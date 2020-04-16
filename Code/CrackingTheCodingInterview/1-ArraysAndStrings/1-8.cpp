// 1.8 Zero Matrix  - pg91

// Write an algorithm such that if an element in an MxN matrix is 0, 
// its entire row and col are 0'd

// [ 1,  2,  3, 4]
// [ 5,  6,  7, 8]
// [ 9, 10, 11, 12]
// 
// matrix[0] = [1, 2, 3 4]
// therefore i = row and j = col 
#include "../../Shared/Testing/TestRunner.hpp"
#include <vector>

typedef std::vector<std::vector<int>> Matrix;
DEF_TESTDATA(ZeroMatrixData, Matrix, Matrix);

Matrix zeroMatrix(Matrix& matrix)    
{
    // Init out matrix 
    std::vector<std::vector<int>> out(matrix.size());
    for(unsigned int i = 0; i < matrix.size(); ++i)
    {
        out[i].resize(matrix[0].size());
    }
  
    // if a col has already been hit, note in this bitfield 
    // Set      ->      zeroedColumns |= 1 << j 
    // Check    ->      (zeroedColumns & 1 << j) != 0
    unsigned int zeroedColumns = 0; 
    for(unsigned int i = 0; i < matrix.size(); ++i)
    {
        bool rowZeroed = false; 
        for(unsigned int j = 0; j < matrix[i].size(); ++j)
        {
            // Check if this col was already zero'd 
            bool colZeroed = ((1 << j) & zeroedColumns) != 0;
            
            int val = matrix[i][j]; 
            if(val == 0)
            {
                // Zero Row 
                for(int k = 0; k < matrix[0].size(); ++k)
                {
                    out[i][k] = 0; 
                }
                // Zero Col 
                for(int k = 0; k < matrix.size(); ++k)
                {
                    out[k][j] = 0;
                }
                // Note that this col is covered 
                zeroedColumns |= (1 << j);
                // Cant continue to the next, this row might still knock out a column 
                // But still note that youre zero'd 
                rowZeroed = true; 
            }
            // Only write your value if your col/row isnt zeroed 
            else if (!colZeroed && !rowZeroed)
            {
                out[i][j] = val;
            }
        }
    }
    
    return out; 
}

int main()
{
    const unsigned int kNumTestCases = 6;
    ZeroMatrixData testCases[kNumTestCases] = { 
        // Basic 
        {{{1, 2, 3},
          {4, 5, 6},
          {7, 0, 9}},           {{1, 0, 3},
                                 {4, 0, 6},
                                 {0, 0, 0}}},
        // Basic 2
        {{{1, 2, 3},
          {4, 5, 6},
          {7, 8, 0}},           {{1, 2, 0},
                                 {4, 5, 0},
                                 {0, 0, 0}}},
        // Technically valid input
        {{{1}},                 {{1}}},
        // No zeros 
        {{{1, 2, 3, 2, 1},
          {4, 5, 6, 5, 4},
          {7, 8, 9, 8, 7}},     {{1, 2, 3, 2, 1},
                                 {4, 5, 6, 5, 4},
                                 {7, 8, 9, 8, 7}}},
        // Still need to care about zero'd row 
        {{{0, 2, 3, 0, 1},
          {4, 5, 6, 5, 4},
          {7, 8, 0, 8, 7}},     {{0, 0, 0, 0, 0},
                                 {0, 5, 0, 0, 4},
                                 {0, 0, 0, 0, 0}}},
        // Still need to care about zero'd col 
        {{{0, 2, 3, 2, 1},
          {0, 5, 6, 5, 4},
          {7, 8, 9, 8, 7}},     {{0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0},
                                 {0, 8, 9, 8, 7}}}                          
    };
    
    TestRunner::RunTestCases<Matrix, Matrix, kNumTestCases>(testCases, &::zeroMatrix);
}

