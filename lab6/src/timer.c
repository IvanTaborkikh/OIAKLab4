#define _POSIX_C_SOURCE 200809L
#include "timer.h"

double timespec_diff_sec(const struct timespec *start, const struct timespec *end) {
    double sec  = (double)(end->tv_sec  - start->tv_sec);
    double nsec = (double)(end->tv_nsec - start->tv_nsec);
    return sec + nsec * 1e-9;
}

void timer_now(struct timespec *ts) {
    clock_gettime(CLOCK_MONOTONIC, ts);
}
