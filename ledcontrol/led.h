#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define LED_TRIGGER_FILE "/sys/class/leds/ACT/trigger"
#define LED_DELAY_ON_FILE "/sys/class/leds/ACT/delay_on"
#define LED_DELAY_OFF_FILE "/sys/class/leds/ACT/delay_off"
#define LED_BRIGHTNESS "/sys/class/leds/ACT/brightness"

/**
 * Sets the LED trigger mode.
 * @param trigger_mode The desired trigger mode ("none", "timer", "heartbeat").
 */
void setTrigger(const char *trigger_mode);


/** 
 * Sets the LED on or off.
 * @param value The state of the light, 1 for on, 0 for off.
 */
void setBrightness(int value);


/** 
 * Sets the LED delay for the "on" state.
 * @param delay_on_ms The delay (in milliseconds) for the LED to stay on.
 */
void setDelayOn(int delay_on_ms);


/** 
 * Sets the LED delay for the "off" state.
 * @param delay_off_ms The delay (in milliseconds) for the LED to stay off.
 */
void setDelayOff(int delay_off_ms);

#endif

