/*
 * This module handles the reaction timer game for assignment 1. It manages the response
 * to directional prompts using the joystick and flashing LEDs for up/down instructions.
 * The module tracks and displays the best reaction time achieved.
 */

#ifndef REACTION_TIMER_H
#define REACTION_TIMER_H

#include "joystick.h"
#include "led.h"
#include "utils.h"
#include <stdbool.h>

// Constants for joystick and LED usage
extern const char* const LED_GREEN_NAME;   // Name of the green LED ("ACT").
extern const char* const LED_RED_NAME;     // Name of the red LED ("PWR").
extern const int JOYSTICK_THRESHOLD;       // Threshold for joystick movement detection.
extern const int REACTION_TIMEOUT_MS;      // Timeout duration for reaction (in milliseconds).

// Enum for the up/green and down/red pairings, used interchangeably.
typedef enum {
    RED_DOWN = 0,   // Red LED corresponding to Down.
    GREEN_UP = 1    // Green LED corresponding to Up.
} ColorDirection;

/**
 * Cleans up and exits the game, printing an appropriate exit message.
 * 
 * @param joystick Pointer to the Joystick struct to clean up.
 * @param led Pointer to the Led struct to clean up (if needed).
 * @param is_lateral_movement Flag indicating if the user exited with lateral movement.
 */
void cleanup_and_exit(Joystick *joystick, Led *led, bool is_lateral_movement);

/**
 * Handles the player's response to the LED prompt, checking the direction 
 * and updating the best reaction time if applicable.
 * 
 * @param joystick_y The joystick Y-axis value.
 * @param correct_direction The correct direction for the player to respond to.
 * @param reaction_time_ms The reaction time in milliseconds.
 * @param led Pointer to the Led struct to control LED response.
 * @return True if a valid response is detected, otherwise false.
 */
bool handle_response(int joystick_y, ColorDirection correct_direction, long long reaction_time_ms, Led *led);

/**
 * Flashes the LED in the specified color for a given duration and number of repetitions.
 * 
 * @param colour The color of the LED to flash.
 * @param flash_duration_ms Duration in milliseconds for each flash (before and after).
 * @param repetitions Number of flashes.
 */
void flash_led(ColorDirection colour, int flash_duration_ms, int repetitions);

#endif
