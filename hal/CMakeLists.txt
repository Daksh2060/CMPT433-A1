# CMakeList.txt for HAL
#   Build a library (`hal`) which exposes the header files as "hal/*.h"
#   Use header as: #include "hal/button.h"

include_directories(hal/include)
include_directories(common/include)  # Add common/include to use utils.h

# Collect all source files for HAL
file(GLOB MY_SOURCES "src/*.c")

# Add the HAL library, including utils.c from common
add_library(hal STATIC ${MY_SOURCES})

# Link with the common library
target_link_libraries(hal PRIVATE common)

# Expose include directories
target_include_directories(hal PUBLIC include)
