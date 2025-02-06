# CMakeLists.txt for Common

# Include directories for header files
include_directories(include)

# Add source files (here we add utils.c)
file(GLOB COMMON_SOURCES src/*.c)

# Create a static library for common code
add_library(common STATIC ${COMMON_SOURCES})

# Make the include directory public for other targets (app and hal) to use
target_include_directories(common PUBLIC include)