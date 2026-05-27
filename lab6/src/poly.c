#include "poly.h"

// === ВЕРСІЯ 1: FPU (схема Горнера) ===
// y = ((a*x + b)*x + c)*x + d
double poly_fpu(const float *x, float a, float b, float c, float d,
                float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
        float res;
        __asm__ volatile (
            "flds  %1\n\t"   // ST0 = a
            "fmuls %5\n\t"   // ST0 = a*x
            "fadds %2\n\t"   // ST0 = a*x + b
            "fmuls %5\n\t"   // ST0 = (a*x+b)*x
            "fadds %3\n\t"   // ST0 = (a*x+b)*x + c
            "fmuls %5\n\t"   // ST0 = ((a*x+b)*x+c)*x
            "fadds %4\n\t"   // ST0 = ((a*x+b)*x+c)*x + d
            "fstps %0\n\t"
            : "=m" (res)
            : "m" (a), "m" (b), "m" (c), "m" (d), "m" (x[i])
            : "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}

// === ВЕРСІЯ 2: XMM (схема Горнера, 4 float одночасно) ===
double poly_xmm(const float *x, float a, float b, float c, float d,
                float *result, size_t n) {
    double sum = 0.0;
    size_t i;

    // broadcast констант: xmm4={a,a,a,a}, xmm5={b,...}, xmm6={c,...}, xmm7={d,...}
    __asm__ volatile (
        "movss %0, %%xmm4\n\t"
        "shufps $0, %%xmm4, %%xmm4\n\t"
        "movss %1, %%xmm5\n\t"
        "shufps $0, %%xmm5, %%xmm5\n\t"
        "movss %2, %%xmm6\n\t"
        "shufps $0, %%xmm6, %%xmm6\n\t"
        "movss %3, %%xmm7\n\t"
        "shufps $0, %%xmm7, %%xmm7\n\t"
        :
        : "m" (a), "m" (b), "m" (c), "m" (d)
        : "xmm4", "xmm5", "xmm6", "xmm7"
    );

    for (i = 0; i + 4 <= n; i += 4) {
        __asm__ volatile (
            "movups (%1), %%xmm0\n\t"    // xmm0 = x[i..i+3]
            // Горнер: xmm0 = a
            "movaps %%xmm4, %%xmm1\n\t"  // xmm1 = {a,a,a,a}
            "mulps  %%xmm0, %%xmm1\n\t"  // xmm1 = a*x
            "addps  %%xmm5, %%xmm1\n\t"  // xmm1 = a*x + b
            "mulps  %%xmm0, %%xmm1\n\t"  // xmm1 = (a*x+b)*x
            "addps  %%xmm6, %%xmm1\n\t"  // xmm1 = (a*x+b)*x + c
            "mulps  %%xmm0, %%xmm1\n\t"  // xmm1 = ((a*x+b)*x+c)*x
            "addps  %%xmm7, %%xmm1\n\t"  // xmm1 = ((a*x+b)*x+c)*x + d
            "movups %%xmm1, (%0)\n\t"
            :
            : "r"(result + i), "r"(x + i)
            : "xmm0", "xmm1", "memory"
        );
        sum += result[i] + result[i+1] + result[i+2] + result[i+3];
    }
    // хвіст
    for (; i < n; i++) {
        float xi = x[i];
        result[i] = ((a * xi + b) * xi + c) * xi + d;
        sum += result[i];
    }
    return sum;
}