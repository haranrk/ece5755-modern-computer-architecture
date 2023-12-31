#include "conv.h"

// Basic convolution operation
float ***convolution(float ***image, int numChannels, float ****kernel, float *biasData, int numFilters, int inputSize, int kernelSize)
{
    int outputSize = inputSize - kernelSize + 1;

    // Allocate memory for the convolution output
    float ***convOutput = malloc(numFilters * sizeof(*convOutput));
    for (int i = 0; i < numFilters; i++)
    {
        convOutput[i] = malloc(outputSize * sizeof(*convOutput[i]));
        for (int j = 0; j < outputSize; j++)
        {
            convOutput[i][j] = malloc(outputSize * sizeof(*convOutput[i][j]));
        }
    }

    for (int f = 0; f < numFilters; f++)
    {
        for (int si = 0; si < outputSize; si++)
        {
            for (int sj = 0; sj < outputSize; sj++)
            {
                convOutput[f][si][sj] = biasData[f];
                for (int c = 0; c < numChannels; c++)
                {
                    for (int i = 0; i < kernelSize; i++)
                    {
                        for (int j = 0; j < kernelSize; j++)
                        {
                            convOutput[f][si][sj] += image[c][si + i][sj + j] * kernel[f][c][i][j];
                        }
                    }
                }
            }
        }
    }

    return convOutput;
}
