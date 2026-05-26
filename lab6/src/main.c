#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "data_gen.h"
#include "energy.h"

#define REPEATS 100
#define G 9.81f

#ifndef OPT_LABEL
#define OPT_LABEL "unknown"
#endif

static const size_t SIZES[] = {100000000};
static const size_t NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);

static double bench(int use_xmm, const float *m, const float *h,
                    float *result, size_t n) {
    struct timespec t0, t1;
    double total = 0.0;
    double sum = 0.0;

    for (int r = 0; r < REPEATS; r++) {
        timer_now(&t0);
        if (use_xmm)
            sum += energy_xmm(m, h, G, result, n);
        else
            sum += energy_fpu(m, h, G, result, n);
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
        float *m = malloc(N * sizeof(float));
        float *h = malloc(N * sizeof(float));
        float *r = malloc(N * sizeof(float));

        if (!m || !h || !r) { printf("blad alokacji\n"); return 1; }

        fill_float_array(m, N, 42u);
        fill_float_array(h, N, 7u);

        printf("%s,FPU,%zu,%.6f\n", OPT_LABEL, N,
               bench(0, m, h, r, N) * 1000.0);
        printf("%s,XMM,%zu,%.6f\n", OPT_LABEL, N,
               bench(1, m, h, r, N) * 1000.0);

        free(m); free(h); free(r);
    }
    return 0;
}