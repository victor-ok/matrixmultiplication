#include "matrix_utils.h"
#include <time.h>

/**
 * create_matrix - function to allocate and initialize a matrix.
 * 
 * @size: size of the matrix.
 * 
 * Return: matrix.
 */

double** create_matrix(int size) {
    double** matrix = (double**)malloc(size * sizeof(double*));
    if (matrix == NULL) {
        perror("Failed to allocate memory for matrix rows");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)_mm_malloc(size * sizeof(double), 32);
        if (matrix[i] == NULL) {
            perror("Failed to allocate aligned memory for matrix columns");
            for (int k = 0; k < i; k++) {
                _mm_free(matrix[k]);
            }
            free(matrix);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX * 10.0; 
        }
    }
    return matrix;
}

/**
 * free_matrix - function to free matrix
 * 
 * @matrix: pointer to the head of the matrix
 * @size: size of the matrix
 */

void free_matrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        _mm_free(matrix[i]); 
    }
    free(matrix);
}

/**
 * print_matrix - function to print a matrix
 * 
 * @matrix: pointer to the head of the matrix
 * @size: size of the matrix
 */

void print_matrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}
