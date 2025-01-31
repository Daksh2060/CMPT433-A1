#include "utils.h"
#include <time.h>
#include <unistd.h>

void sleep_for_ms(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

bool has_timeout_passed(time_t start_time, int timeout_seconds) 
{
    time_t current_time = time(NULL);
    //Checks if time difference has hit the limit to trigger timeout and exit joystick reading.
    return difftime(current_time, start_time) >= timeout_seconds;
}
