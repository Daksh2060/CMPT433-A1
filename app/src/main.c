/**
 * CMPT433 Assignment 1 - Reaction Timer Game
 * Daksh Patel 301430433
 * 
 * A game that tests user reaction time by having them respond to directional prompts
 * using a joystick. Players push the joystick up or down when the corresponding
 * LED lights up. The game tracks and displays the best reaction time achieved. The game
 * can be exited by pressing left or right.
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "hal/joystick.h"
#include "hal/led.h"
#include "hal/button.h"
#include "utils.h"

// Constants for joystick and led usage
static const char* const LED_GREEN_NAME = "ACT";
static const char* const LED_RED_NAME = "PWR";
static const int JOYSTICK_THRESHOLD = 25;    
static const int REACTION_TIMEOUT_MS = 5000;

// ENUM for the up/green and down/red pairings, used interchangeably.
typedef enum {
    RED_DOWN = 0,
    GREEN_UP = 1
} ColorDirecton;

static long long best_time_ms = 0;

// Used to cleanup structs, print corresponding exit message, then exit the program.
static void cleanup_and_exit(Joystick *joystick, Led *led, int exit_code, bool is_lateral_movement); 

// Checks the input of the joystick for main gameplay loop, determines if it is correct or not.
static bool handle_response(int joystick_y, ColorDirecton correct_direction, long long reaction_time_ms, Led *led); 

// Used to flash the green/red LED, duration denotes the flash on and off time.
static void flash_led(ColorDirecton colour, int flash_duration_ms, int repetitions);


int main() 
{
    srand(time(NULL));
    Joystick joystick;
    joystick_init(&joystick);

    printf("Hello, Welcome to Assignment 1:\n\n");
    printf("When the LEDs light up, press the joystick in printed direction!\n");
    printf("(Press left or right to exit)\n");
    sleep_for_ms(1000);

    while (1) {
        printf("Get ready...\n");
        for(int i = 0; i < 4; i++) {
            flash_led(GREEN_UP, 250, 1);
            flash_led(RED_DOWN, 250, 1);
        }

        // Checks if the user is pressing the joystick before the random timer starts.
        bool warning_printed = false;
        while (1) {
            int joystick_y = joystick_read_input(&joystick, JOYSTICK_Y);
            int joystick_x = joystick_read_input(&joystick, JOYSTICK_X);

            // If the user is pushing left/right more than up/down, it is considered a left/right push
            if ((abs(joystick_x) > abs(joystick_y)) && (abs(joystick_x) > JOYSTICK_THRESHOLD)) {
                cleanup_and_exit(&joystick, NULL, 0, true);
            }

            if (abs(joystick_y) > JOYSTICK_THRESHOLD) {
                if (!warning_printed) {
                    printf("Please let go of the joystick.\n\n");
                    warning_printed = true;
                }
            } else {
                break;
            }
            
            sleep_for_ms(1000);
        }

        // Selects a random number between 0.5 and 3
        float random_delay = 0.5 + (float)rand() / RAND_MAX * (3.0 - 0.5);
        sleep_for_ms(random_delay * 1000);  

        ColorDirecton required_direction = rand() % 2;
        Led led;

        int joystick_y = joystick_read_input(&joystick, JOYSTICK_Y);
        int joystick_x = joystick_read_input(&joystick, JOYSTICK_X);

        // Checks if user pressed the joystick before the LED turns on
        if ((abs(joystick_x) > abs(joystick_y)) && (abs(joystick_x) > JOYSTICK_THRESHOLD)) {
            cleanup_and_exit(&joystick, NULL, 0, true);
        }

        if (abs(joystick_y) > JOYSTICK_THRESHOLD) {
            printf("Too soon!\n");
            sleep_for_ms(1000);
            continue;
        }

        long long start_time_ms = get_time_in_ms();

        if (required_direction == GREEN_UP) {
            printf("Press UP now!\n");
            led_init(&led, LED_GREEN_NAME);
            led_turn_on(&led);
        } else {
            printf("Press DOWN now!\n");
            led_init(&led, LED_RED_NAME);
            led_turn_on(&led);
        }

        // Waits for user input after LED turns on, checks for exit, then for correct input.
        bool input_received = false;
        while (!input_received) {
            joystick_y = joystick_read_input(&joystick, JOYSTICK_Y);
            joystick_x = joystick_read_input(&joystick, JOYSTICK_X);

            if ((abs(joystick_x) > abs(joystick_y)) && (abs(joystick_x) > JOYSTICK_THRESHOLD)) {
                cleanup_and_exit(&joystick, &led, 0, true);
            }

            long long reaction_time_ms = get_time_in_ms() - start_time_ms;

            if (reaction_time_ms > REACTION_TIMEOUT_MS) {
                cleanup_and_exit(&joystick, &led, 0, false);
            }

            input_received = handle_response(joystick_y, required_direction, reaction_time_ms, &led);
            sleep_for_ms(10);
        }
        sleep_for_ms(1000);
    }
    return 0;
}

static void flash_led(ColorDirecton colour, int flash_duration_ms, int repetitions) 
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

static bool handle_response(int joystick_y, ColorDirecton correct_direction, long long reaction_time_ms, Led *led) 
{
    if (abs(joystick_y) > JOYSTICK_THRESHOLD) {
        led_turn_off(led);
        led_cleanup(led);

        bool is_up_correct = ((joystick_y > JOYSTICK_THRESHOLD) && (correct_direction == GREEN_UP));
        bool is_down_correct = ((joystick_y < -JOYSTICK_THRESHOLD) && (correct_direction == RED_DOWN));

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

static void cleanup_and_exit(Joystick *joystick, Led *led, int exit_code, bool is_lateral_movement) 
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
    exit(exit_code);
}