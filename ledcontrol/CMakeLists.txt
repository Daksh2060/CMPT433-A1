# CMake configuration for the ledcontrol module
add_library(ledcontrol STATIC led.c)

# Include the header file for the ledcontrol module
target_include_directories(ledcontrol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
