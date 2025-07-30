#include "matrix_multi_algs.h"

/**
 * multipy_naive - Naive matrix multiplication.
 *
 * @A: matrix A.
 * @B: matrix B.
 * @C: Result of A & B.
 * @size: Size of matrix
 *
 */

void multiply_naive(double** A, double** B, double** C, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            C[i][j] = 0.0;
            for (int k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/**
 * multipy_tiled - Loop tiling matrix multiplication
 *
 * @A: matrix A.
 * @B: matrix B.
 * @C: Result of A & B.
 * @size: Size of matrix
 * @tile_size: size of tile
 *
 */

void multiply_tiled(double** A, double** B, double** C, int size, int tile_size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            C[i][j] = 0.0;
        }
    }

    for (int ii = 0; ii < size; ii += tile_size)
    {
        for (int jj = 0; jj < size; jj += tile_size)
        {
            for (int kk = 0; kk < size; kk += tile_size)
            {
                int i_limit = (ii + tile_size > size ? size : ii + tile_size);
                int j_limit = (jj + tile_size > size ? size : jj + tile_size);
                int k_limit = (kk + tile_size > size ? size : kk + tile_size);

                for (int i = ii; i < i_limit; ++i)
                {
                    for (int k = kk; k < k_limit; ++k)
                    {
                        for (int j = jj; j < j_limit; ++j)
                        {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

/**
 * multipy_avx_tiled - Loop tiling matrix multiplication with explicit AVX intrinsics
 * 
 * @A: matrix A.
 * @B: matrix B.
 * @C: Result of A & B.
 * @size: Size of matrix
 * @tile_size: size of tile
 * 
 */

void multiply_avx_tiled(double** A, double** B, double** C, int size, int tile_size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0.0;
        }
    }
    for (int ii = 0; ii < size; ii += tile_size) {
        for (int jj = 0; jj < size; jj += tile_size) {
            for (int kk = 0; kk < size; kk += tile_size) {
                int i_limit = (ii + tile_size > size ? size : ii + tile_size);
                int j_limit = (jj + tile_size > size ? size : jj + tile_size);
                int k_limit = (kk + tile_size > size ? size : kk + tile_size);

                for (int i = ii; i < i_limit; i++) {
                    for (int k = kk; k < k_limit; k++) {
                        for (int j = jj; j < j_limit; j += 4) {
                            if (j + 3 >= j_limit) {
                                for (int j_scalar = j; j_scalar < j_limit; j_scalar++) {
                                    C[i][j_scalar] += A[i][k] * B[k][j_scalar];
                                }
                                continue;
                            }
                            __m256d c_vec = _mm256_load_pd(&C[i][j]);
                            __m256d a_val = _mm256_set1_pd(A[i][k]);
                            __m256d b_vec = _mm256_load_pd(&B[k][j]);
                            __m256d prod = _mm256_mul_pd(a_val, b_vec);
                            c_vec = _mm256_add_pd(c_vec, prod);
                            _mm256_store_pd(&C[i][j], c_vec);
                        }
                    }
                }
            }
        }
    }
}
