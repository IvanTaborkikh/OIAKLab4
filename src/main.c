#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "data_gen.h"
#include "arith_c.h"
#include "arith_asm.h"

#define REPEATS 100

#ifndef OPT_LABEL
#define OPT_LABEL "unknown"
#endif

static const size_t SIZES[] = {100000, 1000000, 10000000};
static const size_t NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);

static double bench_int_op(int op, const int *a, const int *b,
                           int *result, size_t n, int use_asm) {
    struct timespec t0, t1;
    double total = 0.0;
    long long sum = 0;

    for (int r = 0; r < REPEATS; ++r) {
        timer_now(&t0);

        if (use_asm) {
            switch (op) {
                case '+': sum += add_int_asm(a, b, result, n); break;
                case '-': sum += sub_int_asm(a, b, result, n); break;
                case '*': sum += mul_int_asm(a, b, result, n); break;
                case '/': sum += div_int_asm(a, b, result, n); break;
            }
        } else {
            switch (op) {
                case '+': sum += add_int_c(a, b, result, n); break;
                case '-': sum += sub_int_c(a, b, result, n); break;
                case '*': sum += mul_int_c(a, b, result, n); break;
                case '/': sum += div_int_c(a, b, result, n); break;
            }
        }

        timer_now(&t1);
        total += timespec_diff_sec(&t0, &t1);
    }

    if (sum == 0) printf("sum=0\n");

    return total / REPEATS;
}

static double bench_flt_op(int op, const float *a, const float *b,
                           float *result, size_t n, int use_asm) {
    struct timespec t0, t1;
    double total = 0.0;
    double sum = 0.0;

    for (int r = 0; r < REPEATS; ++r) {
        timer_now(&t0);

        if (use_asm) {
            switch (op) {
                case '+': sum += add_float_asm(a, b, result, n); break;
                case '-': sum += sub_float_asm(a, b, result, n); break;
                case '*': sum += mul_float_asm(a, b, result, n); break;
                case '/': sum += div_float_asm(a, b, result, n); break;
            }
        } else {
            switch (op) {
                case '+': sum += add_float_c(a, b, result, n); break;
                case '-': sum += sub_float_c(a, b, result, n); break;
                case '*': sum += mul_float_c(a, b, result, n); break;
                case '/': sum += div_float_c(a, b, result, n); break;
            }
        }

        timer_now(&t1);
        total += timespec_diff_sec(&t0, &t1);
    }

    if (sum == 0.0) printf("sum=0\n");

    return total / REPEATS;
}

int main(void) {
    printf("opt,op,type,impl,N,avg_ms\n");

    for (size_t s = 0; s < NUM_SIZES; ++s) {
        size_t N = SIZES[s];
        printf("# N = %zu\n", N);

        int   *ia = malloc(N * sizeof(int));
        int   *ib = malloc(N * sizeof(int));
        int   *ir = malloc(N * sizeof(int));
        float *fa = malloc(N * sizeof(float));
        float *fb = malloc(N * sizeof(float));
        float *fr = malloc(N * sizeof(float));

        if (!ia || !ib || !ir || !fa || !fb || !fr) {
            printf("blad alokacji pamieci\n");
            return 1;
        }

        fill_int_array(ia, N, 42u);
        fill_int_array(ib, N, 7u);
        fill_float_array(fa, N, 42u);
        fill_float_array(fb, N, 7u);

        int ops[] = {'+', '-', '*', '/'};
        char op_names[][2] = {"+", "-", "*", "/"};

        for (int i = 0; i < 4; i++) {
            printf("%s,%s,int,C,%zu,%.6f\n",   OPT_LABEL, op_names[i], N,
                   bench_int_op(ops[i], ia, ib, ir, N, 0) * 1000.0);
            printf("%s,%s,int,ASM,%zu,%.6f\n", OPT_LABEL, op_names[i], N,
                   bench_int_op(ops[i], ia, ib, ir, N, 1) * 1000.0);
        }

        for (int i = 0; i < 4; i++) {
            printf("%s,%s,float,C,%zu,%.6f\n",   OPT_LABEL, op_names[i], N,
                   bench_flt_op(ops[i], fa, fb, fr, N, 0) * 1000.0);
            printf("%s,%s,float,ASM,%zu,%.6f\n", OPT_LABEL, op_names[i], N,
                   bench_flt_op(ops[i], fa, fb, fr, N, 1) * 1000.0);
        }

        float *fa_cast = malloc(N * sizeof(float));
        float *fb_cast = malloc(N * sizeof(float));
        if (!fa_cast || !fb_cast) {
            printf("blad alokacji pamieci\n");
            return 1;
        }
        cast_int_to_float(ia, fa_cast, N);
        cast_int_to_float(ib, fb_cast, N);

        for (int i = 0; i < 4; i++) {
            printf("%s,%s,i_to_f,C,%zu,%.6f\n",   OPT_LABEL, op_names[i], N,
                   bench_flt_op(ops[i], fa_cast, fb_cast, fr, N, 0) * 1000.0);
            printf("%s,%s,i_to_f,ASM,%zu,%.6f\n", OPT_LABEL, op_names[i], N,
                   bench_flt_op(ops[i], fa_cast, fb_cast, fr, N, 1) * 1000.0);
        }

        free(ia);
        free(ib);
        free(ir);
        free(fa);
        free(fb);
        free(fr);
        free(fa_cast);
        free(fb_cast);
    }

    return 0;
}
