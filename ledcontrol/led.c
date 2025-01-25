#include "led.h"

void setTrigger(const char *trigger_mode) 
{
    FILE *trigger_file = fopen(LED_TRIGGER_FILE, "w");
    if (trigger_file == NULL) {
        perror("Error opening LED trigger file");
        exit(EXIT_FAILURE);
    }

    int chars_written = fprintf(trigger_file, "%s\n", trigger_mode);
    if (chars_written <= 0) {
        perror("Error writing to LED trigger file");
        exit(EXIT_FAILURE);
    }

    fclose(trigger_file);
}


void setBrightness(int value) 
{
    FILE *brightness_file = fopen(LED_BRIGHTNESS, "w");
    if (brightness_file == NULL) {
        perror("Error opening LED brightness file");
        exit(EXIT_FAILURE);
    }

    int chars_written = fprintf(brightness_file, "%d\n", value);
    if (chars_written <= 0) {
        perror("Error writing to LED brightness file");
        exit(EXIT_FAILURE);
    }

    fclose(brightness_file);
}


void setDelayOn(int delay_on_ms) 
{
    FILE *delay_on_file = fopen(LED_DELAY_ON_FILE, "w");
    if (delay_on_file == NULL) {
        perror("Error opening LED delay_on file");
        exit(EXIT_FAILURE);
    }

    int chars_written = fprintf(delay_on_file, "%d\n", delay_on_ms);
    if (chars_written <= 0) {
        perror("Error writing to LED delay_on file");
        exit(EXIT_FAILURE);
    }

    fclose(delay_on_file);
}


void setDelayOff(int delay_off_ms) 
{
    FILE *delay_off_file = fopen(LED_DELAY_OFF_FILE, "w");
    if (delay_off_file == NULL) {
        perror("Error opening LED delay_off file");
        exit(EXIT_FAILURE);
    }

    int chars_written = fprintf(delay_off_file, "%d\n", delay_off_ms);
    if (chars_written <= 0) {
        perror("Error writing to LED delay_off file");
        exit(EXIT_FAILURE);
    }

    fclose(delay_off_file);
}