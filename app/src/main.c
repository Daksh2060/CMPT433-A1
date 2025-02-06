// /**
//  * CMPT433 Assignment 1 - Reaction Timer Game
//  * Daksh Patel 301430433
//  * 
//  * A game that tests user reaction time by having them respond to directional prompts
//  * using a joystick. Players push the joystick up or down when the corresponding
//  * LED lights up. The game tracks and displays the best reaction time achieved. The game
//  * can be exited by pressing left or right.
//  */

#include "reaction_timer.h"

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
                cleanup_and_exit(&joystick, NULL, true);
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

        ColorDirection required_direction = rand() % 2;
        Led led;

        int joystick_y = joystick_read_input(&joystick, JOYSTICK_Y);
        int joystick_x = joystick_read_input(&joystick, JOYSTICK_X);

        // Checks if user pressed the joystick before the LED turns on
        if ((abs(joystick_x) > abs(joystick_y)) && (abs(joystick_x) > JOYSTICK_THRESHOLD)) {
            cleanup_and_exit(&joystick, NULL, true);
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
                cleanup_and_exit(&joystick, &led, true);
            }

            long long reaction_time_ms = get_time_in_ms() - start_time_ms;

            if (reaction_time_ms > REACTION_TIMEOUT_MS) {
                cleanup_and_exit(&joystick, &led, false);
            }

            input_received = handle_response(joystick_y, required_direction, reaction_time_ms, &led);
            sleep_for_ms(10);
        }
        sleep_for_ms(1000);
    }
    return 0;
}