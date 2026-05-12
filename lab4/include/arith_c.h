#ifndef ARITH_C_H
#define ARITH_C_H

#include <stddef.h>

long long add_int_c(const int *a, const int *b, int *result, size_t n);
long long sub_int_c(const int *a, const int *b, int *result, size_t n);
long long mul_int_c(const int *a, const int *b, int *result, size_t n);
long long div_int_c(const int *a, const int *b, int *result, size_t n);

double add_float_c(const float *a, const float *b, float *result, size_t n);
double sub_float_c(const float *a, const float *b, float *result, size_t n);
double mul_float_c(const float *a, const float *b, float *result, size_t n);
double div_float_c(const float *a, const float *b, float *result, size_t n);

#endif
