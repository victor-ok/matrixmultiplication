#include "common_defs.h"
#include "matrix_utils.h"
#include "matrix_multi_algs.h"
#include "timer.h"
#include <time.h>

int main(int argc, char *argv[])
{
    int matrix_size = N;
    int tile_size = TILE_SIZE;

    if (argc > 1)
    {
        matrix_size = atoi(argv[1]);
            if (matrix_size <= 0)
            {
                fprintf(stderr, "Error: Matrix size must be a positive integer.\n");
                return EXIT_FAILURE;
            }
    }
    if (argc > 2)
    {
        tile_size = atoi(argv[2]);
        if (tile_size <= 0 || tile_size > matrix_size)
        {
            fprintf(stderr, "Error: Tile size must be a positive integer and less than or equal to matrix size.\n");
            return EXIT_FAILURE;
        }
        if (tile_size % 4 != 0)
        {
            fprintf(stderr, "Warning: For optimal AVX performance, consider a tile size that is a multiple of 4 (e.g., 32, 64).\n");
        }
    } else {
        if (tile_size % 4 != 0)
        {
            fprintf(stderr, "Warning: Default TILE_SIZE (%d) is not a multiple of 4. Consider adjusting for AVX.\n", TILE_SIZE);
        }
    }
    
    printf("Matrix Size: %d x %d\n", matrix_size, matrix_size);
    printf("Tile Size for Tiled Multiplications: %d\n", tile_size);

    srand(time(NULL));

    double** A = create_matrix(matrix_size);
    double** B = create_matrix(matrix_size);
    double** C_naive = create_matrix(matrix_size);
    double** C_tiled = create_matrix(matrix_size);
    double** C_avx_tiled = create_matrix(matrix_size);

    Timer timer;

    printf("\nPerforming Naive Matrix Multiplication...\n");
    start_timer(&timer);
    multiply_naive(A, B, C_naive, matrix_size);
    stop_timer(&timer);
    printf("Naive Multiplication Time: %.6f seconds\n", get_elapsed_time(&timer));

    printf("\nPerforming Loop Tiling Matrix Multiplication (Compiler Auto-Vectorization Potential)...\n");
    start_timer(&timer);
    multiply_tiled(A, B, C_tiled, matrix_size, tile_size);
    stop_timer(&timer);
    printf("Loop Tiling Multiplication Time: %.6f seconds\n", get_elapsed_time(&timer));

    printf("\nPerforming Loop Tiling Matrix Multiplication with Explicit AVX Intrinsics...\n");
    start_timer(&timer);
    multiply_avx_tiled(A, B, C_avx_tiled, matrix_size, tile_size);
    stop_timer(&timer);
    printf("Explicit AVX Tiled Multiplication Time: %.6f seconds\n", get_elapsed_time(&timer));

    free_matrix(A, matrix_size);
    free_matrix(B, matrix_size);
    free_matrix(C_naive, matrix_size);
    free_matrix(C_tiled, matrix_size);
    free_matrix(C_avx_tiled, matrix_size);

    return 0;
}
