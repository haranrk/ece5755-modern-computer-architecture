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



float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols ) {
    if (A_cols != B_rows)
    {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    int AnValues = 0;
    int ArowIndexArrayLen = 0;

    for (int i = 0; i < A_rows; i++)
    {
        bool valuesInThisRow = false;
        for (int j = 0; j < A_cols; j++)
        {
            if(A[i][j] != 0){
                AnValues++;
                valuesInThisRow = true;
            }
        }
        if (valuesInThisRow){
            ArowIndexArrayLen++;
        }
    }

    float *AValues = init_array(AnValues);
    float *ARowIndexArray = init_array(ArowIndexArrayLen);
    float *AColIndexArray = init_array(AnValues);

    int rowPointer = 0;
    int colPointer = 0;
    for (int i = 0; i < A_rows; i++)
    {
        bool valuesInThisRow = false;
        for (int j = 0; j < A_cols; j++)
        {
            if(A[i][j] != 0){
                AValues[colPointer] = A[i][j];
                AColIndexArray[colPointer] = j;
                colPointer++;
                valuesInThisRow = true;
            }
        }
        if (valuesInThisRow){
            ARowIndexArray[rowPointer] = i;
            rowPointer++;
        }
    }

    int BnValues = 0;
    int BColIndexArrayLen = 0;

    for (int i = 0; i < B_cols; i++)
    {
        bool valuesInThisCol = false;
        for (int j = 0; j < B_rows; j++)
        {
            if(B[i][j] != 0){
                BnValues++;
                valuesInThisCol = true;
            }
        }
        if (valuesInThisCol){
            BColIndexArrayLen++;
        }
    }

    float *BValues = init_array(BnValues);
    float *BRowIndexArray = init_array(BnValues);
    float *BColIndexArray = init_array(BColIndexArrayLen);
    // printf("nValues: %d, rowIndexArrayLen: %d \n", nValues, rowIndexArrayLen );

    rowPointer = 0;
    colPointer = 0;
    for (int i = 0; i < B_cols; i++)
    {
        bool valuesInThisCol = false;
        for (int j = 0; j < B_rows; j++)
        {
            if(B[i][j] != 0){
                BValues[rowPointer] = B[i][j];
                BRowIndexArray[rowPointer] = j;
                rowPointer++;
                valuesInThisCol = true;
            }
        }
        if (valuesInThisCol){
            BColIndexArray[colPointer] = i;
            colPointer++;
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


    for (int aRowPointer = 0; aRowPointer < ArowIndexArrayLen; aRowPointer++)
    {
        for (int j = 0; j < B_cols; j++)
        {
            for (int k = 0; k < A_cols; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return A;

}