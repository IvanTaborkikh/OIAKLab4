#ifndef ARITH_ASM_H
#define ARITH_ASM_H

#include <stddef.h>

long long add_int_asm(const int *a, const int *b, int *result, size_t n);
long long sub_int_asm(const int *a, const int *b, int *result, size_t n);
long long mul_int_asm(const int *a, const int *b, int *result, size_t n);
long long div_int_asm(const int *a, const int *b, int *result, size_t n);

double add_float_asm(const float *a, const float *b, float *result, size_t n);
double sub_float_asm(const float *a, const float *b, float *result, size_t n);
double mul_float_asm(const float *a, const float *b, float *result, size_t n);
double div_float_asm(const float *a, const float *b, float *result, size_t n);

#endif
