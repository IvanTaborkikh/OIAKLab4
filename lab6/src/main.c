#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "data_gen.h"
#include "poly.h"

#define REPEATS 100
#ifndef OPT_LABEL
#define OPT_LABEL "unknown"
#endif

// сталі коефіцієнти
#define COEF_A  2.0f
#define COEF_B -3.0f
#define COEF_C  1.5f
#define COEF_D  0.5f

static const size_t SIZES[] = {100000000};
static const size_t NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);

static double bench(int use_xmm, const float *x, float *result, size_t n) {
    struct timespec t0, t1;
    double total = 0.0, sum = 0.0;

    for (int r = 0; r < REPEATS; r++) {
        timer_now(&t0);
        if (use_xmm)
            sum += poly_xmm(x, COEF_A, COEF_B, COEF_C, COEF_D, result, n);
        else
            sum += poly_fpu(x, COEF_A, COEF_B, COEF_C, COEF_D, result, n);
        timer_now(&t1);
        total += timespec_diff_sec(&t0, &t1);
    }
    if (sum == 0.0) printf("sum=0\n");
    return total / REPEATS;
}

int main(void) {
    printf("opt,impl,N,avg_ms\n");

    for (size_t s = 0; s < NUM_SIZES; s++) {
        size_t N = SIZES[s];
        float *x = malloc(N * sizeof(float));
        float *r = malloc(N * sizeof(float));
        if (!x || !r) { printf("blad alokacji\n"); return 1; }

        fill_float_array(x, N, 42u);

        printf("%s,FPU,%zu,%.6f\n", OPT_LABEL, N,
               bench(0, x, r, N) * 1000.0);
        printf("%s,XMM,%zu,%.6f\n", OPT_LABEL, N,
               bench(1, x, r, N) * 1000.0);

        free(x); free(r);
    }
    return 0;
}