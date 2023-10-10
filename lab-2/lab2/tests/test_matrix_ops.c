#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_matrix_ops.h"

/**** HELPER FUNCTIONS ****/
/**** YOUR CODE HERE ****/

void test_matmul_square_matrices(void)
{
    const int DIMS = 5;
    float **A_m = init_2d_array(DIMS, DIMS);
    float **B_m = init_2d_id_array(DIMS, DIMS);

    // for (int i = 0; i < 1000; i++)
    // {
    //     float **C = matmul_blocking(A_m, B_m, 3, 3, 3, 3);
    // }

    float **C = matmul_blocking(A_m, B_m, DIMS, DIMS, DIMS, DIMS);

    for (int i = 0; i < DIMS; i++)
    {
        for (int j = 0; j < DIMS; j++)
        {
            TEST_ASSERT_FLOAT_WITHIN(1e-6, C[i][j], A_m[i][j]);
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
    float **C = matmul_blocking(A, B, 2, 3, 2, 2);

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

void test_matmul_square_matrices1(void)
{
    int size = 100;
    float **A_m = init_2d_array(size, size);
    float **B_m = init_2d_array(size, size);

    for (int i = 0; i < 100; i++)
    {
        float **C = matmul_blocking(A_m, B_m, size, size, size, size);
    }
}

void test_matmul_square_matrices2(void)
{
    int size = 1000;
    float **A_m = init_2d_array(size, size);
    float **B_m = init_2d_array(size, size);

    for (int i = 0; i < 1; i++)
    {
        float **C = matmul_blocking(A_m, B_m, size, size, size, size);
    }
}