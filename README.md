# matrixmultiplication
Port &amp; Polish: Software Optimization for RISC-V  Coding Challenge

## Running Tests

To run tests, run the following command
* To Compile Without Compiler Auto-Vectorization (but still allowing explicit AVX intrinsics):
```bash
gcc -O0 -march=native -mavx main.c matrix_utils.c matrix_mult_algs.c timer.c -o matrix_mult_no_vec 
```
* To Compile With Auto-Vectorization (and explicit AVX):
```bash
gcc -O3 -march=native -mavx main.c matrix_utils.c matrix_mult_algs.c timer.c -o matrix_mult_vec
```
* To Compile With Explicit AVX Intrinsics Only (and explicitly disable auto-vectorization):
```bash
gcc -O2 -march=native -mavx -fno-tree-vectorize main.c matrix_utils.c matrix_mult_algs.c timer.c -o matrix_mult_explicit_avx_only
```
