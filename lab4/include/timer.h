#ifndef TIMER_H
#define TIMER_H

#include <time.h>

double timespec_diff_sec(const struct timespec *start, const struct timespec *end);
void timer_now(struct timespec *ts);

#endif
