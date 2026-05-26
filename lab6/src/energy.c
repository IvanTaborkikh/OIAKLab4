#include "energy.h"

// === ВЕРСІЯ 1: FPU (скалярна) ===
double energy_fpu(const float *m, const float *h, float g,
                  float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
        float res;
        __asm__ volatile (
            "flds  %1\n\t"   // ST0 = m[i]
            "fmuls %2\n\t"   // ST0 = m[i] * g
            "fmuls %3\n\t"   // ST0 = m[i] * g * h[i]
            "fstps %0\n\t"   // result[i] = ST0; pop
            : "=m" (res)
            : "m" (m[i]), "m" (g), "m" (h[i])
            : "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}

// === ВЕРСІЯ 2: XMM (векторна, 4 float за ітерацію) ===
double energy_xmm(const float *m, const float *h, float g,
                  float *result, size_t n) {
    double sum = 0.0;
    size_t i;

    // broadcast g -> {g, g, g, g} в xmm2
    __asm__ volatile (
        "movss  %0, %%xmm2\n\t"
        "shufps $0, %%xmm2, %%xmm2\n\t"
        :
        : "m" (g)
        : "xmm2"
    );

    for (i = 0; i + 4 <= n; i += 4) {
        __asm__ volatile (
            "movups (%1), %%xmm0\n\t"   // xmm0 = m[i..i+3]
            "movups (%2), %%xmm1\n\t"   // xmm1 = h[i..i+3]
            "mulps  %%xmm2, %%xmm0\n\t" // xmm0 = m * g
            "mulps  %%xmm1, %%xmm0\n\t" // xmm0 = m * g * h
            "movups %%xmm0, (%0)\n\t"   // result[i..i+3] = xmm0
            :
            : "r"(result + i), "r"(m + i), "r"(h + i)
            : "xmm0", "xmm1", "memory"
        );
        sum += result[i] + result[i+1] + result[i+2] + result[i+3];
    }
    // хвіст
    for (; i < n; i++) {
        result[i] = m[i] * g * h[i];
        sum += result[i];
    }
    return sum;
}