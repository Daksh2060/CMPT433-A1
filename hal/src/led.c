#include "hal/led.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

static bool is_initialized = false;

void led_init(Led *led, const char *name) {
    assert(led != NULL);
    assert(name != NULL);
    assert(!is_initialized);

    printf("LED initialized: %s\n", name);
    is_initialized = true;
    led->is_initialized = true;

    // snprintf(led->trigger_file, sizeof(led->trigger_file), "/sys/class/leds/%s/trigger", name);
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

    printf("LED cleaned up\n");
    is_initialized = false;
    led->is_initialized = false;
}