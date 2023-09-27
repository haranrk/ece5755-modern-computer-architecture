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
    const int kernelSize = 4;
    float ***image = init_image(inputSize, numChannels);
    float ****kernel = init_kernel(numFilters, numChannels, kernelSize);
    return;

    float imageVal[2][4][4] = {
        {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}},
        {{1, 1, 3, 3}, {5, 5, 7, 7}, {9, 9, 11, 11}, {13, 113, 15, 15}}};

    for (int i = 0; i < numChannels; i++)
    {
        for (int j = 0; j < inputSize; j++)
        {
            for (int k = 0; k < inputSize; k++)
            {
                image[i][j][k] = imageVal[i][j][k];
            }
        }
    }

    float bias[1] = {1};
    float kernelVal[1][2][2][2] = {
        {{{1, 1}, {1, 1}},
         {{1, 1}, {1, 1}}},
        {{{2, 2}, {2, 2}},
         {{2, 2}, {2, 2}}}};

    // assign kernelVal to kernel variable
    for (int f = 0; f < numFilters; f++)
    {
        for (int i = 0; i < kernelSize; i++)
        {
            for (int j = 0; j < kernelSize; j++)
            {
                for (int k = 0; k < kernelSize; k++)
                {
                    kernel[f][i][j][k] = kernelVal[f][i][j][k];
                }
            }
        }
    }

    float actualOutput[1][3][3] = {
        {{36, 48, 60}, {84, 96, 108}, {132, 144, 156}}};

    for (int i = 0; i < 1000; i++)
    {
        float ***output = convolution(image, numChannels, kernel, bias, numFilters, inputSize, kernelSize);
    }
    float ***output = convolution(image, numChannels, kernel, bias, numFilters, inputSize, kernelSize);
    const int outputSize = inputSize - kernelSize + 1;
    for (int f = 0; f < numFilters; f++)
    {
        for (int i = 0; i < outputSize; i++)
        {
            for (int j = 0; j < outputSize; j++)
            {
                TEST_ASSERT_FLOAT_WITHIN(1e-6, actualOutput[f][i][j], output[f][i][j]);
            }
        }
    }
}
