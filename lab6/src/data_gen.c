#define _POSIX_C_SOURCE 200809L
#include "data_gen.h"
#include <stdlib.h>

void fill_int_array(int *arr, size_t n, unsigned int seed) {
    unsigned int state = seed;
    for (size_t i = 0; i < n; ++i) {
        int v = (int)(rand_r(&state) % 1000) + 1;   
        if (rand_r(&state) & 1) v = -v;          
        arr[i] = v;
    }
}

void fill_float_array(float *arr, size_t n, unsigned int seed) {
    unsigned int state = seed;
    for (size_t i = 0; i < n; ++i) {
        float frac = (float)rand_r(&state) / (float)RAND_MAX;
        float v = 1.0f + frac * 1000.0f;           
        if (rand_r(&state) & 1) v = -v;
        arr[i] = v;
    }
}

void cast_int_to_float(const int *src, float *dst, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        dst[i] = (float)src[i];
    }
}
