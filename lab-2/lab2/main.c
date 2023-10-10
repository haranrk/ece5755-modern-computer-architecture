#include "kernel/kernel.h"
#include "utils/data_utils.h"
#include <string.h>

enum Impl {
  NAIVE,
  TILED,
  UNKNOWN
};

void run_matmul(enum Impl impl, int dims, int block_size, int iterations) {
    float **A = init_2d_array(dims, dims);
    float **B = init_2d_id_array(dims, dims);
    printf("Params: dims: %d, block_size: %d, iterations: %d\n", dims, block_size, iterations);

    switch(impl){
        case NAIVE:
            printf("Naive\n");
            for (int i = 1; i<iterations; i++){
                float **C = matmul(A, B, dims, dims, dims, dims);
            }
            break;
        case TILED:
            printf("Tiling\n");
            for (int i = 1; i<iterations; i++){
                float **C = matmul_blocking(A, B, dims, dims, dims, dims, block_size);
            }
            break;
        case UNKNOWN:
          printf("Unknown matmul implementation\n");
    }

    free(A);
    free(B);
}

enum Impl stringToEnum(const char *str) {
    if (strcmp(str, "NAIVE") == 0) {
        return NAIVE;
    } else if (strcmp(str, "TILED") == 0) {
        return TILED;
    } else {
        return UNKNOWN;
    }
}

int main(int argc, char *argv[]){
  if (argc < 4){
    printf("Usage: ./main <impl> <dims> <block_size> <iterations>\n");
    return 0;
  }
  char *input = argv[1];
  enum Impl impl = stringToEnum(argv[1]);
  int dims = atoi(argv[2]);
  int block_size = atoi(argv[3]);
  int iterations = atoi(argv[4]);
  run_matmul( impl, dims, block_size, iterations);
  return 0;
}
