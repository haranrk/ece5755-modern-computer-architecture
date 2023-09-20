#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_conv.h"

/**** HELPER FUNCTIONS ****/
/**** YOUR CODE HERE ****/

void test_conv(void)
{
    const int numChannels = 2;
    const int numFilters = 1;
    const int inputSize = 4;
    const int kernelSize = 2;
    float image[2][4][4] = {
        {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}},
        {{1, 1, 3, 3}, {5, 5, 7, 7}, {9, 9, 11, 11}, {13, 113, 15, 15}}};

    float bias[1] = {1};
    float kernel[1][2][2][2] = {
        {{{1, 1}, {1, 1}},
         {{1, 1}, {1, 1}}},
        {{{2, 2}, {2, 2}},
         {{2, 2}, {2, 2}}}};
    printf("Kernel: %f\n", kernel[0][0][0][0]);

    float actual_output[1][3][3] = {
        {{36, 48, 60}, {84, 96, 108}, {132, 144, 156}}};

    // float ***output = convolution(image, numChannels, kernel, bias, numFilters, inputSize, kernelSize);
    // const int outputSize = inputSize - kernelSize + 1;
    // for (int f = 0; f < numFilters; f++)
    // {
    //     for (int i = 0; i < inputSize; i++)
    //     {
    //         for (int j = 0; j < outputSize; j++)
    //         {
    //             TEST_ASSERT_FLOAT_WITHIN(1e-6, actual_output[f][i][j], output[f][i][j]);
    //         }
    //     }
    // }
}
