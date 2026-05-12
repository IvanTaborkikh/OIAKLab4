#include "arith_xmm.h"

/*
 * Wektorowe operacje SIMD (SSE) na liczbach float.
 *
 * Każda iteracja pętli przetwarza 4 floaty naraz (4 x 32 bity = 128 bitów).
 * Krok pętli: i += 4
 * Używamy movups (Unaligned) – nie wymaga wyrównania do 16 bajtów.
 * Ogon tablicy (elementy, gdy n % 4 != 0) obsługiwany skalarnie.
 *
 * Zwracana wartość (sum) – żeby kompilator nie wyoptymalizował pętli.
 */

double add_float_xmm(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    size_t i;

    for (i = 0; i + 4 <= n; i += 4) {
        __asm__ volatile (
            "movups (%1), %%xmm0\n\t"    /* xmm0 = a[i..i+3]          */
            "movups (%2), %%xmm1\n\t"    /* xmm1 = b[i..i+3]          */
            "addps  %%xmm1, %%xmm0\n\t"  /* xmm0 = xmm0 + xmm1        */
            "movups %%xmm0, (%0)\n\t"    /* result[i..i+3] = xmm0     */
            :
            : "r"(result + i), "r"(a + i), "r"(b + i)
            : "xmm0", "xmm1", "memory"
        );
        sum += result[i] + result[i+1] + result[i+2] + result[i+3];
    }
    /* ogon */
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
