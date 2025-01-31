#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "hal/joystick.h"
#include "hal/led.h"
#include "hal/button.h"
#include "utils.h"

typedef enum {
    RED = 0,
    GREEN = 1
} LedColor;

// Static global variable for best reaction time
static long long best_time = 0;

void flash_led(LedColor colour, int flash_duration_ms, int repetitions) {   
    Led led;

    if(colour == GREEN) {
        led_init(&led, "ACT");
    } else {
        led_init(&led, "PWR");
    }

    for(int i = 0; i < repetitions; i++) {
        led_turn_on(&led);
        sleep_for_ms(flash_duration_ms);
        led_turn_off(&led);
        sleep_for_ms(flash_duration_ms);
    }

    led_cleanup(&led);
}

int handle_response(int y, int correct_input, long long reaction_time, Led *led) {
    if (y > 20 || y < -20) {
        led_turn_off(led);
        led_cleanup(led);
        if ((y > 20 && correct_input == 1) || (y < -20 && correct_input == 0)) {
            printf("Correct!\n");
            flash_led(GREEN, 200, 5);
            if (best_time == 0 || reaction_time < best_time) {
                best_time = reaction_time;
                printf("New best time!\n");
            }
            printf("Your reaction time was %lld ms; ", reaction_time);
            printf("best so far in game is %lld ms.\n", best_time);
        } else {
            printf("Incorrect!\n");
            flash_led(RED, 200, 5);
        }
        return 1;
    }
    return 0;
}

static long long get_time_in_ms(void) {
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoSeconds = spec.tv_nsec;
    long long milliSeconds = seconds * 1000 + nanoSeconds / 1000000;
    return milliSeconds;
}

int main() {
    srand(time(NULL));
    Joystick joystick;
    joystick_init(&joystick);

    printf("Hello, idk what else to say\n\n");
    printf("When the LEDs light up, press the joystick in that direction!\n");
    printf("(Press left or right to exit)\n");
    sleep_for_ms(1000);

    while (1) {

        printf("Get ready...\n");

        for(int i = 0; i < 4; i++) {
            flash_led(GREEN, 200, 1);
            flash_led(RED, 200, 1);
        }

        bool warning_printed = false;
        while (1) {
            int y = joystick_read_input(&joystick, JOYSTICK_Y);

            if (y > 10 || y < -10) {
                if (!warning_printed) {
                    printf("Please let go of the joystick.\n\n");
                    warning_printed = true;
                }
            } else {
                break;
            }

            sleep_for_ms(1000);
        }

        float random_float = 0.5 + (float)rand() / RAND_MAX * (3 - 0.5);
        sleep_for_ms(random_float * 1000);  

        int direction = rand() % 2;
        Led led;
        long long start_time = get_time_in_ms();

        if (direction == 1) {
            printf("Press UP now!\n");
            led_init(&led, "ACT");
            led_turn_on(&led);
              
        } else {
            printf("Press DOWN now!\n");
            led_init(&led, "PWR");
            led_turn_on(&led);
        }

        int correct_input = direction;
        int input_received = 0;

        while (!input_received) {
            int y = joystick_read_input(&joystick, JOYSTICK_Y);

            long long current_time = get_time_in_ms();
            long long reaction_time = current_time - start_time;

            if (reaction_time > 5000) {
                printf("No input within 5000ms; quitting!\n");
                joystick_cleanup(&joystick);
                exit(0);
            }

            input_received = handle_response(y, correct_input, reaction_time, &led);
            sleep_for_ms(10);
        }
        sleep_for_ms(1000);
    }

    return 0;
}