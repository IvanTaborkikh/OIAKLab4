#include "arith_xmm.h"

double add_float_xmm(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    size_t i;

    for (i = 0; i + 4 <= n; i += 4) {
        __asm__ volatile (
            "movups (%1), %%xmm0\n\t"    
            "movups (%2), %%xmm1\n\t"    
            "addps  %%xmm1, %%xmm0\n\t"  
            "movups %%xmm0, (%0)\n\t"    
            :
            : "r"(result + i), "r"(a + i), "r"(b + i)
            : "xmm0", "xmm1", "memory"
        );
        sum += result[i] + result[i+1] + result[i+2] + result[i+3];
    }
    for (; i < n; i++) {
        result[i] = a[i] + b[i];
        sum += result[i];
    }
    return sum;
}

double sub_float_xmm(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    size_t i;

    for (i = 0; i + 4 <= n; i += 4) {
        __asm__ volatile (
            "movups (%1), %%xmm0\n\t"
            "movups (%2), %%xmm1\n\t"
            "subps  %%xmm1, %%xmm0\n\t"
            "movups %%xmm0, (%0)\n\t"
            :
            : "r"(result + i), "r"(a + i), "r"(b + i)
            : "xmm0", "xmm1", "memory"
        );
        sum += result[i] + result[i+1] + result[i+2] + result[i+3];
    }
    for (; i < n; i++) {
        result[i] = a[i] - b[i];
        sum += result[i];
    }
    return sum;
}

double mul_float_xmm(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    size_t i;

    for (i = 0; i + 4 <= n; i += 4) {
        __asm__ volatile (
            "movups (%1), %%xmm0\n\t"
            "movups (%2), %%xmm1\n\t"
            "mulps  %%xmm1, %%xmm0\n\t"
            "movups %%xmm0, (%0)\n\t"
            :
            : "r"(result + i), "r"(a + i), "r"(b + i)
            : "xmm0", "xmm1", "memory"
        );
        sum += result[i] + result[i+1] + result[i+2] + result[i+3];
    }
    for (; i < n; i++) {
        result[i] = a[i] * b[i];
        sum += result[i];
    }
    return sum;
}

double div_float_xmm(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    size_t i;

    for (i = 0; i + 4 <= n; i += 4) {
        __asm__ volatile (
            "movups (%1), %%xmm0\n\t"
            "movups (%2), %%xmm1\n\t"
            "divps  %%xmm1, %%xmm0\n\t"
            "movups %%xmm0, (%0)\n\t"
            :
            : "r"(result + i), "r"(a + i), "r"(b + i)
            : "xmm0", "xmm1", "memory"
        );
        sum += result[i] + result[i+1] + result[i+2] + result[i+3];
    }
    for (; i < n; i++) {
        result[i] = a[i] / b[i];
        sum += result[i];
    }
    return sum;
}
