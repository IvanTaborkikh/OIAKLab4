#ifndef ENERGY_H
#define ENERGY_H
#include <stddef.h>

// Версія 1: FPU скалярна
double energy_fpu(const float *m, const float *h, float g, float *result, size_t n);

// Версія 2: XMM векторна
double energy_xmm(const float *m, const float *h, float g, float *result, size_t n);

#endif