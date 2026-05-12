#include "arith_asm.h"

long long add_int_asm(const int *a, const int *b, int *result, size_t n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        int res;
        __asm__ volatile (
            "movl %1, %%eax\n\t"
            "addl %2, %%eax\n\t"
            "movl %%eax, %0\n\t"
            : "=m" (res)
            : "m" (a[i]), "m" (b[i])
            : "eax", "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}

long long sub_int_asm(const int *a, const int *b, int *result, size_t n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        int res;
        __asm__ volatile (
            "movl %1, %%eax\n\t"
            "subl %2, %%eax\n\t"
            "movl %%eax, %0\n\t"
            : "=m" (res)
            : "m" (a[i]), "m" (b[i])
            : "eax", "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}

long long mul_int_asm(const int *a, const int *b, int *result, size_t n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        int res;
        __asm__ volatile (
            "movl %1, %%eax\n\t"
            "imull %2, %%eax\n\t"
            "movl %%eax, %0\n\t"
            : "=m" (res)
            : "m" (a[i]), "m" (b[i])
            : "eax", "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}

long long div_int_asm(const int *a, const int *b, int *result, size_t n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        int res;
        __asm__ volatile (
            "movl %1, %%eax\n\t"
            "cdq\n\t"
            "idivl %2\n\t"
            "movl %%eax, %0\n\t"
            : "=m" (res)
            : "m" (a[i]), "m" (b[i])
            : "eax", "edx", "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}

double add_float_asm(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        float res;
        __asm__ volatile (
            "flds %1\n\t"
            "fadds %2\n\t"
            "fstps %0\n\t"
            : "=m" (res)
            : "m" (a[i]), "m" (b[i])
            : "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}

double sub_float_asm(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        float res;
        __asm__ volatile (
            "flds %1\n\t"
            "fsubs %2\n\t"
            "fstps %0\n\t"
            : "=m" (res)
            : "m" (a[i]), "m" (b[i])
            : "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}

double mul_float_asm(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        float res;
        __asm__ volatile (
            "flds %1\n\t"
            "fmuls %2\n\t"
            "fstps %0\n\t"
            : "=m" (res)
            : "m" (a[i]), "m" (b[i])
            : "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}

double div_float_asm(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        float res;
        __asm__ volatile (
            "flds %1\n\t"
            "fdivs %2\n\t"
            "fstps %0\n\t"
            : "=m" (res)
            : "m" (a[i]), "m" (b[i])
            : "memory"
        );
        result[i] = res;
        sum += res;
    }
    return sum;
}
