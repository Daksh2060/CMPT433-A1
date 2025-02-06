# Build the app, using the HAL

include_directories(include)
include_directories(common/include)  # Include common for utils.h

file(GLOB MY_SOURCES "src/*.c")
add_executable(a1 ${MY_SOURCES})

# Link with the HAL library
target_link_libraries(a1 LINK_PRIVATE hal)

# Link with the common library
target_link_libraries(a1 PRIVATE common)

# Copy executable to final location (change `a1` to project name as needed)
add_custom_command(TARGET a1 POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:a1>"
     "~/cmpt433/public/myApps/a1" 
  COMMENT "Copying ARM executable to public NFS directory")

