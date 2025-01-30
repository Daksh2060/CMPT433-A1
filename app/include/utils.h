/*
 * This module contains utility functions used in the applications of assignments.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <time.h>

/**
 * Pauses the program for a number of milliseconds, obtained from course LED Guide.
 * 
 * @param delayInMs The delay duration in milliseconds.
 */
void sleepForMs(long long delayInMs);

/**
 * Checks if the joystick has been idle for a certain amount of time. Used to exit input reading.
 * 
 * @param start_time The start time from where the timeout is measured.
 * @param timeout_seconds The timeout duration limit in seconds.
 * @return True if the timeout limit has passed, otherwise false.
 */
bool has_timeout_passed(time_t start_time, int timeout_seconds);

#endif