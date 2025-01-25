# Add executable target
add_executable(my_program
    main.c
)

# Link the ledcontrol library
target_link_libraries(my_program PRIVATE ledcontrol)
