// // Main program to build the application
// // Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "hal/joystick.h"
#include "hal/led.h"
#include "hal/button.h"
#include "utils.h"

int main() 
{
    Joystick joystick;
    joystick_init(&joystick);

    int prev_x = 0, prev_y = 0;
    int x, y;

    int threshold = 2;  
    int idle_time_threshold = 5; 
    
    time_t start_time = time(NULL);  

    printf("Reading joystick input...\n");

    while (1) {
        
        x = joystick_read_input(&joystick, JOYSTICK_X);
        y = joystick_read_input(&joystick, JOYSTICK_Y);

        printf("X: %d, Y: %d\n", x, y);

        
        if (abs(x - prev_x) <= threshold && abs(y - prev_y) <= threshold) {
            if (has_timeout_passed(start_time, idle_time_threshold)) { 
                printf("Joystick has not changed significantly for 5 seconds. Exiting...\n");
                break;  
            }
        } else {
            
            start_time = time(NULL);
        }

        prev_x = x;
        prev_y = y;

        sleepForMs(10);  
    }

    joystick_cleanup(&joystick);  
    return 0;
}



