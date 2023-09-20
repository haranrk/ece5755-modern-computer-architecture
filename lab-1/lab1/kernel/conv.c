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

    printf("hi");
    printf("numFilters: %d, outputSize: %d\n", numFilters, outputSize);
    for (int f = 0; f < numFilters; f++)
    {
        for (int si = 0; si < outputSize; si++)
        {
            for (int sj = 0; sj < outputSize; sj++)
            {
                printf("convOutput[%d][%d][%d]: %f\n", f, si, sj, convOutput[f][si][sj]);
                convOutput[f][si][sj] = biasData[f];
                for (int c = 0; c < numChannels; c++)
                {
                    for (int i = 0; i < kernelSize; i++)
                    {
                        for (int j = 0; j < kernelSize; j++)
                        {
                            printf("Hekk\n");
                            printf("kernel[%d][%d][%d][%f]: \n", f, c, i, biasData[f]);
                            printf("Hekk\n");
                            printf("kernel[%d][%d][%d][%d]: %f\n", f, c, i, j, kernel[0][0][0][0]);
                            convOutput[f][si][sj] += image[c][si + i][sj + j] * kernel[f][c][si][sj];
                        }
                    }
                }
            }
        }
    }

    return convOutput;
}
