#ifndef ARITH_XMM_H
#define ARITH_XMM_H

#include <stddef.h>

double add_float_xmm(const float *a, const float *b, float *result, size_t n);
double sub_float_xmm(const float *a, const float *b, float *result, size_t n);
double mul_float_xmm(const float *a, const float *b, float *result, size_t n);
double div_float_xmm(const float *a, const float *b, float *result, size_t n);

#endif
