#include "hal/led.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// Ensures only one LED is initialized at a time
static bool is_initialized = false;

void led_init(Led *led, const char *name) {
    assert(led != NULL);
    assert(name != NULL);
    assert(!is_initialized);

    // Set flags to true so another LED cannot be initialized.
    printf("LED initialized: %s\n", name);
    is_initialized = true;
    led->is_initialized = true;

    // Set the filepath for the brightness file of the LED
    snprintf(led->brightness_file, sizeof(led->brightness_file), "/sys/class/leds/%s/brightness", name);
}

void led_turn_on(Led *led) {
    assert(led != NULL);
    assert(is_initialized);

    FILE *brightness = fopen(led->brightness_file, "w");
    if (brightness == NULL) {
        printf("Error opening brightness file\n");
        return;
    }

    int chars_written = fprintf(brightness, "%d\n", 1);
    if (chars_written <= 0) {
        perror("Error writing to LED brightness file");
        exit(EXIT_FAILURE);
    }

    printf("LED turned on\n");
    fclose(brightness);
}

void led_turn_off(Led *led) {
    assert(led != NULL);
    assert(is_initialized);

    FILE *brightness = fopen(led->brightness_file, "w");
    if (brightness == NULL) {
        printf("Error opening brightness file\n");
        return;
    }
 
    int chars_written = fprintf(brightness, "%d\n", 0);
    if (chars_written <= 0) {
        perror("Error writing to LED brightness file");
        exit(EXIT_FAILURE);
    }

    printf("LED turned off\n");
    fclose(brightness);
}

void led_cleanup(Led *led) {
    assert(led != NULL);
    assert(is_initialized);

    //Sets module and LED struct to uninitialized so new LED can be initialized
    printf("LED cleaned up\n");
    is_initialized = false;
    led->is_initialized = false;
}







//For trigger control
// void setTrigger(const char *trigger_mode) 
// {
//     FILE *trigger_file = fopen(LED_TRIGGER_FILE, "w");
//     if (trigger_file == NULL) {
//         perror("Error opening LED trigger file");
//         exit(EXIT_FAILURE);
//     }

//     int chars_written = fprintf(trigger_file, "%s\n", trigger_mode);
//     if (chars_written <= 0) {
//         perror("Error writing to LED trigger file");
//         exit(EXIT_FAILURE);
//     }

//     fclose(trigger_file);
// }

//// snprintf(led->trigger_file, sizeof(led->trigger_file), "/sys/class/leds/%s/trigger", name); under init