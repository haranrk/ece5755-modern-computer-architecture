#ifndef DATA_UTILS_H
#define DATA_UTILS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "hdf5.h"

#define PARAMS_FILENAME "./model/model.h5"

// Load images and labels
float *init_1d_array(int size);
float **init_2d_array(int rows, int cols);
float **init_2d_id_array(int rows, int cols);
float ***init_image(int channelSize, int inputSize);
float ****init_kernel(int numFilters, int channelSize, int kernelSize);
float ****loadImages(const char *filename, int numImages, int numChannels);
void destroyImages(float ****images, int numImages, int numChannels);
int *loadLabels(const char *filename, int numLabels);

// Read parameters from HDF5 file, and cleanup
void read_float_1d_params(hid_t file_id, const char *datasetname, float **data, int *size);
void read_float_2d_params(hid_t file_id, const char *datasetname, float ***data, int *dim1, int *dim2);
void read_float_4d_params(hid_t file_id, const char *datasetname, float *****data, int *dim1, int *dim2, int *dim3, int *dim4);
void cleanup_float_1d(float *data);
void cleanup_float_2d(float **data, int dim1);
void cleanup_float_4d(float ****data, int dim1, int dim2, int dim3);

#endif // DATA_UTILS_H