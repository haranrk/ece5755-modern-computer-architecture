#include "data_utils.h"

float *init_1d_array(int size)
{
    float *array = malloc(size * sizeof(float));
    for (int i = 0; i < size; i++)
    {
        array[i] = 0;
    }
    return array;
}
float **init_2d_array(int rows, int cols)
{
    // malloc a 2d array
    float **array = malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++)
    {
        array[i] = malloc(cols * sizeof(float));
        for (int j = 0; j < cols; j++)
        {
            array[i][j] = (i+j)*((i+j)%2);
            printf("%f ",  array[i][j]);
        }
        printf("\n");
    }
    return array;
}
float **init_2d_id_array(int rows, int cols)
{
    // malloc a 2d identity array
    float **array = malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++)
    {
        array[i] = malloc(cols * sizeof(float));
        for (int j = 0; j < cols; j++)
        {
            array[i][j] = 0;
        }
        array[i][i]= 1;
    }
    return array;
}
float ***init_image(int channelSize, int inputSize)
{
    float ***image = malloc(channelSize * sizeof(*image));
    for (int c = 0; c < channelSize; c++)
    {
        image[c] = malloc(inputSize * sizeof(**image));
        for (int i = 0; i < inputSize; i++)
        {
            image[c][i] = malloc(inputSize * sizeof(***image));
            for (int j = 0; j < inputSize; j++)
            {
                image[c][i][j] = c + i + j;
            }
        }
    }
    return image;
}

float ****init_kernel(int numFilters, int channelSize, int kernelSize)
{
    float ****kernel = malloc(numFilters * sizeof(*kernel));
    for (int i = 0; i < numFilters; i++)
    {
        kernel[i] = malloc(channelSize * sizeof(*kernel[i]));
        for (int j = 0; j < channelSize; j++)
        {
            kernel[i][j] = malloc(kernelSize * sizeof(*kernel[i][j]));
            for (int k = 0; k < kernelSize; k++)
            {
                kernel[i][j][k] = malloc(kernelSize * sizeof(*kernel[i][j][k]));
                for (int m = 0; m < kernelSize; m++)
                {
                    kernel[i][j][k][m] = 0;
                }
            }
        }
    }
    return kernel;
}

// loadImages returns a 4D array where each element of the array is a 28x28 image loaded from
// the training dataset.
float ****loadImages(const char *filename, int numImages, int numChannels)
{
    // Image pre-processing (let's just use 1000 for now)
    float ****images = malloc(numImages * sizeof(*images)); // Dimensions: numImages x numChannels x 28 x 28
    for (int i = 0; i < numImages; i++)
    {
        images[i] = malloc(numChannels * sizeof(*images[i]));
        for (int c = 0; c < numChannels; c++)
        {
            images[i][c] = malloc(28 * sizeof(**images[i]));
            for (int j = 0; j < 28; j++)
            {
                images[i][c][j] = malloc(28 * sizeof(***images[i]));
            }
        }
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", filename);
        exit(1);
    }

    // Skip the magic number and the size headers
    fseek(file, 16, SEEK_SET);
    for (int i = 0; i < numImages; i++)
    {
        for (int c = 0; c < numChannels; c++)
        {
            for (int j = 0; j < 28; j++)
            {
                for (int k = 0; k < 28; k++)
                {
                    unsigned char pixel;
                    fread(&pixel, 1, 1, file);
                    images[i][c][j][k] = pixel / 255.0;
                }
            }
        }
    }

    fclose(file);

    return images;
}

void destroyImages(float ****images, int numImages, int numChannels)
{
    for (int i = 0; i < numImages; i++)
    {
        for (int c = 0; c < numChannels; c++)
        {
            for (int j = 0; j < 28; j++)
            {
                free(images[i][c][j]);
            }
            free(images[i][c]);
        }
        free(images[i]);
    }
    free(images);
}

int *loadLabels(const char *filename, int numLabels)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }

    // Skip the magic number and the size header
    fseek(file, 8, SEEK_SET);

    int *labels = malloc(numLabels * sizeof(*labels));
    for (int i = 0; i < numLabels; i++)
    {
        unsigned char label;
        fread(&label, 1, 1, file);
        labels[i] = (int)label;
    }

    fclose(file);
    return labels;
}


void cleanup_float_1d(float *data)
{
    free(data);
}

void cleanup_float_2d(float **data, int dim1)
{
    free(data[0]);
    free(data);
}

void cleanup_float_4d(float ****data, int dim1, int dim2, int dim3)
{
    // First, free temp_data
    free(data[0][0][0]);

    for (int i = 0; i < dim1; i++)
    {
        for (int j = 0; j < dim2; j++)
        {
            for (int k = 0; k < dim3; k++)
            {
                // You don't need to free data[i][j][k] here, because it points to an address in temp_data
                // free(data[i][j][k]);
            }
            // Free the third dimension
            free(data[i][j]);
        }
        // Free the second dimension
        free(data[i]);
    }
    // Free the first dimension
    free(data);
}
