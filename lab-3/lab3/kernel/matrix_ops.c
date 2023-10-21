#include "matrix_ops.h"
#include <math.h>
#include <stdbool.h>

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

float *init_array(int size)
{
    float *array = malloc(size * sizeof(float));
    for (int i = 0; i < size; i++)
    {
        array[i] = 0;
    }
    return array;
}

float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols)
{
    if (A_cols != B_rows)
    {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    int AnValues = 0;
    float *ARowIndexArray = init_array(A_rows + 1);

    int valuesInThisRow = 0;
    for (int i = 0; i < A_rows; i++)
    {
        for (int j = 0; j < A_cols; j++)
        {
            if (A[i][j] != 0)
            {
                AnValues++;
                valuesInThisRow++;
            }
        }
        ARowIndexArray[i + 1] = valuesInThisRow;
    }

    float *AValues = init_array(AnValues);
    float *AColIndexArray = init_array(AnValues);

    int colPointer = 0;
    for (int i = 0; i < A_rows; i++)
    {
        for (int j = 0; j < A_cols; j++)
        {
            if (A[i][j] != 0)
            {
                AValues[colPointer] = A[i][j];
                AColIndexArray[colPointer] = j;
                colPointer++;
            }
        }
    }

    int BnValues = 0;
    float *BColIndexArray = init_array(B_cols + 1);

    int valuesInThisCol = 0;
    for (int i = 0; i < B_cols; i++)
    {
        for (int j = 0; j < B_rows; j++)
        {
            if (B[i][j] != 0)
            {
                BnValues++;
                valuesInThisCol++;
            }
        }
        BColIndexArray[i + 1] = valuesInThisCol;
    }

    float *BValues = init_array(BnValues);
    float *BRowIndexArray = init_array(BnValues);

    int rowPointer = 0;
    for (int i = 0; i < B_cols; i++)
    {
        for (int j = 0; j < B_rows; j++)
        {
            if (B[i][j] != 0)
            {
                BValues[rowPointer] = B[i][j];
                BRowIndexArray[rowPointer] = j;
                rowPointer++;
            }
        }
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

    for (int iterations; iterations < 20; iterations++) {
        for (int a_row = 0; a_row < A_rows + 1; a_row++)
        {
            int a_col_idx = ARowIndexArray[a_row];
            int a_col_end_idx = ARowIndexArray[a_row + 1];
            for (int b_col = 0; b_col < B_rows + 1; b_col++)
            {
                int b_row_idx = BColIndexArray[b_col];
                int b_row_end_idx = BColIndexArray[b_col + 1];

                C[a_row][b_col] = 0;
                while (a_col_idx < a_col_end_idx && b_row_idx < b_row_end_idx)
                {
                    int a_col = AColIndexArray[a_col_idx];
                    int b_row = BRowIndexArray[b_row_idx];

                    if (a_col == b_row)
                    {
                        C[a_row][b_col] += A[a_row][a_col] * B[b_row][b_col];
                        a_col_idx++;
                        b_row_idx++;
                    }
                    else if (a_col < b_row)
                    {
                        a_col_idx++;
                    }
                    else
                    {
                        b_row_idx++;
                    }
                }
            }
        }
    }
    return C;
}