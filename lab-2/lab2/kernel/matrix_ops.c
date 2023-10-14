#include "matrix_ops.h"
#include <math.h>

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols)
{
    if (A_cols != B_rows)
    {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++)
    {
        C[i] = (float *)malloc(B_cols * sizeof(float));
        for (int j = 0; j < B_cols; j++)
        {
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < A_rows; i++)
    {
        for (int j = 0; j < B_cols; j++)
        {
            for (int k = 0; k < A_cols; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}
float **matmul_blocking(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols, int BLOCK_SIZE)
{
    if (A_cols != B_rows)
    {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++)
    {
        C[i] = (float *)malloc(B_cols * sizeof(float));
        for (int j = 0; j < B_cols; j++)
        {
            C[i][j] = 0;
        }
    }

    for (int i_outer = 0; i_outer < A_rows; i_outer += BLOCK_SIZE)
    {
        for (int j_outer = 0; j_outer < B_cols; j_outer += BLOCK_SIZE)
        {
            for (int k_outer = 0; k_outer < A_cols; k_outer += BLOCK_SIZE)
            {
                for (int i = i_outer; i < fmin(i_outer + BLOCK_SIZE, A_rows); i++)
                {
                    for (int j = j_outer; j < fmin(j_outer + BLOCK_SIZE, B_cols); j++)
                    {
                        for (int k = k_outer; k < fmin(k_outer + BLOCK_SIZE, A_cols); k++)
                        {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    return C;
}