#include "arith_c.h"

long long add_int_c(const int *a, const int *b, int *result, size_t n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] + b[i];
        sum += result[i];
    }
    return sum;
}

long long sub_int_c(const int *a, const int *b, int *result, size_t n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] - b[i];
        sum += result[i];
    }
    return sum;
}

long long mul_int_c(const int *a, const int *b, int *result, size_t n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] * b[i];
        sum += result[i];
    }
    return sum;
}

long long div_int_c(const int *a, const int *b, int *result, size_t n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] / b[i];
        sum += result[i];
    }
    return sum;
}

double add_float_c(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] + b[i];
        sum += result[i];
    }
    return sum;
}

double sub_float_c(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] - b[i];
        sum += result[i];
    }
    return sum;
}

double mul_float_c(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] * b[i];
        sum += result[i];
    }
    return sum;
}

double div_float_c(const float *a, const float *b, float *result, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] / b[i];
        sum += result[i];
    }
    return sum;
}
