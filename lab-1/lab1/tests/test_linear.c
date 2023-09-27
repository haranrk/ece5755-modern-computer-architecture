#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_linear.h"

void test_linear(void)
{

  // sample arrays for a linear layer
  float input[] = {1.0, 2.0, 3.0};
  float weightsArray[][3] = {
      {0.1, 0.2, 0.3},
      {0.4, 0.5, 0.6},
      {0.7, 0.8, 0.9}};

  float **weights = init_2d_array(3, 3);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      weights[i][j] = weightsArray[i][j];
    }
  }

  float biases[] = {0.1, 0.2, 0.3};
  float actualOutput[] = {1.5, 3.4, 5.3};

  int inputSize = 3;
  int outputSize = 3;

  for (int i = 0; i < 1000; i++)
  {
    float *output = linear(input, weights, biases, inputSize, outputSize);
  }
  float *output = linear(input, weights, biases, inputSize, outputSize);

  for (int i = 0; i < outputSize; i++)
  {
    TEST_ASSERT_FLOAT_WITHIN(1e-6, actualOutput[i], output[i]);
  }
}

// Add more test cases as needed