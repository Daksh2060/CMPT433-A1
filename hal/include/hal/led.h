#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char name[64];
    // char trigger_file[128];
    char brightness_file[128];
    bool is_initialized;
} Led;

void led_init(Led *led, const char *name);

void led_turn_on(Led *led);

void led_turn_off(Led *led);

void led_cleanup(Led *led);

#endif



// //The desired trigger mode ("none", "timer", "heartbeat").
 
// void setTrigger(const char *trigger_mode);