// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include "badmath.h"
#include "hal/button.h"
#include "hal/led.h"
#include <unistd.h>
#include <time.h>

// void foo() {
//     int data[3];    
//     for (int i = 0; i < 3; i++) {
//         data[i] = 10;
//         printf("Value: %d\n", data[i]);
//     }
// }

// int main()
// {
//     printf("Hello world!\n");

//     // Initialize all modules; HAL modules first
//     button_init();
//     badmath_init();

//     // Main program logic:
//     for (int i = 0; i < 10; i++) {
//         printf("  -> Reading button time %d = %d\n", i, button_is_button_pressed());
//     }

//     for (int i = 0; i <= 35; i++) {
//         int ans = badmath_factorial(i);
//         printf("%4d! = %6d\n", i, ans);
//     }

//     // Cleanup all modules (HAL modules last)
//     badmath_cleanup();
//     button_cleanup();

//     printf("!!! DONE !!!\n"); 

//     // Some bad code to try out and see what shows up.
//     #if 0
//         // Test your linting setup
//         //   - You should see a warning underline in VS Code
//         //   - You should see compile-time errors when building (-Wall -Werror)
//         // (Linting using clang-tidy; see )
//         int x = 0;
//         if (x = 10) {
//         }
//     #endif
//     #if 1
//         // Demonstrate -fsanitize=address (enabled in the root CMakeFiles.txt)
//         // Compile and run this code. Should see warning at compile time; error at runtime.
//         foo();

//     #endif
// }

static void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}


int main(){
    printf("Hello there hehehe!\n");

    Led led;
    led_init(&led, "ACT");
    // led_init(&led, "PWR");
    sleepForMs(1000);
    led_turn_on(&led);
    sleepForMs(3000);
    led_turn_off(&led);
    led_cleanup(&led);

    return 0;
}