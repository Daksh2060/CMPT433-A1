/*
 * This file implements the utility module, holding functions reusable for multiple assignments.
 */

#include "utils.h"
#include <time.h>
#include <unistd.h>

void sleep_for_ms(long long delay_in_ms)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delay_ns = delay_in_ms * NS_PER_MS;
    int seconds = delay_ns / NS_PER_SECOND;
    int nanoseconds = delay_ns % NS_PER_SECOND;
    struct timespec req_delay = {seconds, nanoseconds};
    nanosleep(&req_delay, (struct timespec *) NULL);
}

bool has_timeout_passed(time_t start_time, int timeout_seconds) 
{
    time_t current_time = time(NULL);
    return difftime(current_time, start_time) >= timeout_seconds;
}

long long get_time_in_ms(void) 
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nano_seconds = spec.tv_nsec;
    long long milli_seconds = seconds * 1000 + nano_seconds / 1000000;
    return milli_seconds;
}
