# Set build output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/example")

# Generate executable
add_executable(publisher publisher.c)
add_executable(subscriber subscriber.c)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Link library
target_link_libraries(publisher iceoryx_clib)
target_link_libraries(subscriber iceoryx_clib)