#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H
#include "common_defs.h"

double** create_matrix(int size);
void free_matrix(double** matrix, int size);
void print_matrix(double** matrix, int size);
int verify_matrices(double** C1, double** C2, int size, double epsilon);

#endif