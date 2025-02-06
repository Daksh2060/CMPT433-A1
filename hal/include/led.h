/*
 * This module is used to control the LED on the BeagleBone. The LED can be turned on or off
 * and only one LED can be controlled at a time. 
 */

#ifndef _LED_CONTROL_H
#define _LED_CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct of a LED device
typedef struct {
    char name[64];             // Name of the LED, e.g., "ACT" or "PWR"
    char brightness_file[128]; // Path to the file controlling the LED brightness, e.g., "/sys/class/leds/ACT/brightness"
    bool is_initialized;       // Flag to track if the LED has been initialized
} Led;


/**
 * Initializes the LED with the specified name.
 * 
 * @param led A pointer to the Led struct, created in main.
 * @param name The name of the LED, corresponding to the file in /sys/class/leds/
 */
void led_init(Led *led, const char *name);


/**
 * Turn on the LED by setting brightness to 1.
 * 
 * @param led A pointer to the Led struct to be turned on.
 */
void led_turn_on(Led *led);


/**
 * Turns off the LED by setting its brightness to 0.
 * 
 * @param led A pointer to the Led struct to be turned off.
 */
void led_turn_off(Led *led);


/**
 * Clean up LED by closing file handles and resetting the is_initialized flag.
 * 
 * @param led A pointer to the Led struct to be cleaned up.
 */
void led_cleanup(Led *led);

#endif