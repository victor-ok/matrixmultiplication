#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
#include <stddef.h>

typedef struct
{
    struct timeval start;
    struct timeval end;
} Timer;


void start_timer(Timer* timer);
void stop_timer(Timer* timer);
double get_elapsed_time(Timer* timer);

#endif
