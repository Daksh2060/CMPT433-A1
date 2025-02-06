/*
 * This file implements the functions used in the reaction timer game.
 */

#include "reaction_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variable to track the best reaction time.
static long long best_time_ms = 0;

void flash_led(ColorDirection colour, int flash_duration_ms, int repetitions) 
{   
    Led led;
    if (colour == GREEN_UP) {
        led_init(&led, LED_GREEN_NAME);
    } else {
        led_init(&led, LED_RED_NAME);
    }

    for(int i = 0; i < repetitions; i++) {
        led_turn_on(&led);
        sleep_for_ms(flash_duration_ms);
        led_turn_off(&led);
        sleep_for_ms(flash_duration_ms);
    }
    led_cleanup(&led);
}

bool handle_response(int joystick_y, ColorDirection correct_direction, long long reaction_time_ms, Led *led) 
{
    if (abs(joystick_y) > JOYSTICK_THRESHOLD) {
        led_turn_off(led);
        led_cleanup(led);

        bool is_up_correct = ((joystick_y < -JOYSTICK_THRESHOLD) && (correct_direction == GREEN_UP));
        bool is_down_correct = ((joystick_y > JOYSTICK_THRESHOLD) && (correct_direction == RED_DOWN));

        if (is_up_correct || is_down_correct) {
            printf("Correct!\n");
            flash_led(GREEN_UP, 200, 5);
            
            if ((best_time_ms == 0) || (reaction_time_ms < best_time_ms)) {
                best_time_ms = reaction_time_ms;
                printf("New best time!\n");
                sleep_for_ms(250);
            }
            printf("Your reaction time was %lld ms; ", reaction_time_ms);
            printf("best so far in game is %lld ms.\n", best_time_ms);
        } else {
            printf("Incorrect!\n");
            flash_led(RED_DOWN, 200, 5);
        }
        return true;
    }
    return false;
}

void cleanup_and_exit(Joystick *joystick, Led *led, bool is_lateral_movement) 
{
    if (led) {
        led_turn_off(led);
        led_cleanup(led);
    }
    joystick_cleanup(joystick);

    if (is_lateral_movement) {
        printf("Joystick pushed left or right; exiting game.\n");
    } else {
        printf("No input within 5000ms; quitting!\n");
    }
    exit(0);
}

