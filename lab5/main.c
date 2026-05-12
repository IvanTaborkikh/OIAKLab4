#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "data_gen.h"
#include "arith_xmm.h"

/*
 * Laboratorium 5 – Wektoryzacja obliczeń SIMD (XMM/SSE)
 *
 * Kompilacja BEZ optymalizacji (wymóg laboratorium):
 *   gcc -std=c11 -O0 main.c arith_xmm.c data_gen.c timer.c -o lab5 -lm
 *
 * Wynik: CSV z samymi wynikami XMM
 * Wyniki C i FPU bierzemy z lab4 i łączymy ręcznie w Excelu.
 */

#define REPEATS 5
#define N_TARGET 10000000

static double bench(int op, const float *a, const float *b,
                    float *result, size_t n)
{
    struct timespec t0, t1;
    double total = 0.0;
    double sink  = 0.0;

    for (int r = 0; r < REPEATS; ++r) {
        timer_now(&t0);
        switch (op) {
        case '+': sink += add_float_xmm(a, b, result, n); break;
        case '-': sink += sub_float_xmm(a, b, result, n); break;
        case '*': sink += mul_float_xmm(a, b, result, n); break;
        case '/': sink += div_float_xmm(a, b, result, n); break;
        }
        timer_now(&t1);
        total += timespec_diff_sec(&t0, &t1);
    }

    if (sink == 0.0) printf("# sink=0\n");
    return total / REPEATS;
}

int main(void)
{
    size_t N = N_TARGET;

    float *fa = malloc(N * sizeof(float));
    float *fb = malloc(N * sizeof(float));
    float *fr = malloc(N * sizeof(float));

    if (!fa || !fb || !fr) {
        fprintf(stderr, "Blad alokacji pamieci!\n");
        return 1;
    }

    fill_float_array(fa, N, 42u);
    fill_float_array(fb, N, 7u);

    printf("op,impl,N,avg_ms\n");

    int        ops[] = {'+', '-', '*', '/'};
    const char *opn[] = {"+",  "-",  "*",  "/"};

    for (int i = 0; i < 4; i++) {
        double ms = bench(ops[i], fa, fb, fr, N) * 1000.0;
        printf("%s,XMM,%zu,%.4f\n", opn[i], N, ms);
        fflush(stdout);
    }

    free(fa); free(fb); free(fr);
    return 0;
}
