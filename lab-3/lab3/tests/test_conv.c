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
    float ***image = init_image(numChannels, inputSize);
    float ****kernel = init_kernel(numFilters, numChannels, kernelSize);

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
        for (int i = 0; i < numChannels; i++)
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
        {{23, 31, 39}, {55, 63, 71}, {187, 195, 103}}};

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

void test_conv1(void)
{
    const int numChannels = 3;
    const int numFilters = 1;
    const int inputSize = 100;
    const int kernelSize = 2;
    float ***image = init_image(numChannels, inputSize);
    float ****kernel = init_kernel(numFilters, numChannels, kernelSize);

    float bias[1] = {1};

    for (int i = 0; i < 100; i++)
    {
        float ***output = convolution(image, numChannels, kernel, bias, numFilters, inputSize, kernelSize);
    }
    float ***output = convolution(image, numChannels, kernel, bias, numFilters, inputSize, kernelSize);
}

void test_conv2(void)
{
    const int numChannels = 3;
    const int numFilters = 1;
    const int inputSize = 1000;
    const int kernelSize = 2;
    float ***image = init_image(numChannels, inputSize);
    float ****kernel = init_kernel(numFilters, numChannels, kernelSize);

    float bias[1] = {1};

    for (int i = 0; i < 100; i++)
    {
        float ***output = convolution(image, numChannels, kernel, bias, numFilters, inputSize, kernelSize);
    }
    float ***output = convolution(image, numChannels, kernel, bias, numFilters, inputSize, kernelSize);
}