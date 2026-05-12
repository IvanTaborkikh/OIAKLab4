#ifndef DATA_GEN_H
#define DATA_GEN_H

#include <stddef.h>

void fill_int_array(int *arr, size_t n, unsigned int seed);
void fill_float_array(float *arr, size_t n, unsigned int seed);
void cast_int_to_float(const int *src, float *dst, size_t n);

#endif
