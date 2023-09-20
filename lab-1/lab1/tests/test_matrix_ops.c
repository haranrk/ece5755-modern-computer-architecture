#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"

/**** HELPER FUNCTIONS ****/
/**** YOUR CODE HERE ****/

void test_matmul_square_matrices(void)
{
    float A[3][3] = {{1, 2, 3}, {4, 5, 6}};
    float B[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    float **C = matmul(A, B, 3, 3, 3, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("C[%d][%d]: %f\n", i, j, A[i][j]);
        }
    }
}

void test_matmul_incompatible_dimensions(void)
{
    // Setup
    float **A = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        A[i] = (float *)malloc(3 * sizeof(float));
    }

    float **B = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        B[i] = (float *)malloc(2 * sizeof(float));
    }

    // Run function under test
    float **C = matmul(A, B, 2, 3, 2, 2);

    // Check expectations
    UNITY_TEST_ASSERT_NULL(C, __LINE__, "Expected NULL!");

    // Cleanup
    for (int i = 0; i < 2; i++)
    {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
}