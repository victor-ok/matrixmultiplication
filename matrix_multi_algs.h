#ifndef MATRIX_MULT_ALGS_H
#define MATRIX_MULT_ALGS_H

#include "common_defs.h"

/* Naive matrix multiplication A * B = C */
void multiply_naive(double** A, double** B, double** C, int size);

/* Loop tiling matrix multiplication A * B = C */
void multiply_tiled(double** A, double** B, double** C, int size, int tile_size);

/* Loop tiling matrix multiplication with explicit AVX intrinsics */
void multiply_avx_tiled(double** A, double** B, double** C, int size, int tile_size);

#endif
