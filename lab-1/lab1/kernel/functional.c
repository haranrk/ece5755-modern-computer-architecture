#include "functional.h"

float relu(float x)
{
    if (x > 0)
    {
        return x;
    }
    else
    {
        return 0;
    }
}

void applyRelu(float *input, int inputSize)
{
    for (int i = 0; i < inputSize; i++)
    {
        input[i] = relu(input[i]);
    }
}

float *softmax(float *input, int inputSize)
{
    float *softmaxOutput = malloc(inputSize * sizeof(*softmaxOutput));
    printf("ssd: %f\n", input[0]);

    float sum = 0;
    for (int i = 0; i < inputSize; i++)
    {
        sum += exp(input[i]);
    }
    for (int i = 0; i < inputSize; i++)
    {
        softmaxOutput[i] = exp(input[i]) / sum;
    }

    return softmaxOutput;
}