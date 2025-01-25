# CMake Build Configuration for Cross-Compilation
cmake_minimum_required(VERSION 3.18)
project(LEDControl VERSION 1.0 DESCRIPTION "LED Control Project" LANGUAGES C)

# Cross-Compilation Toolchain Setup
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(TOOLCHAIN_PREFIX aarch64-linux-gnu)

# Specify the cross compiler
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

# Compiler options
set(CMAKE_C_STANDARD 11)
add_compile_options(
    -Wall 
    -Werror 
    -Wpedantic 
    -Wextra
    -fdiagnostics-color
)

# Optional: Address Sanitizer (comment out for release)
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

# PThread library
add_compile_options(-pthread)
add_link_options(-pthread)

# Output directory
set(EXECUTABLE_OUTPUT_PATH "$ENV{HOME}/cmpt433/public")

# Subdirectories (adjust as per your project structure)
add_subdirectory(ledcontrol)
add_subdirectory(src)








