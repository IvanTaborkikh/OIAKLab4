#ifndef POLY_H
#define POLY_H
#include <stddef.h>

double poly_fpu(const float *x, float a, float b, float c, float d,
                float *result, size_t n);

double poly_xmm(const float *x, float a, float b, float c, float d,
                float *result, size_t n);

#endif