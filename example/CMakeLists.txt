# Set build output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Generate executable
add_executable(publisher publisher.c)
add_executable(subscriber subscriber.c)

# Add include directories
target_include_directories(publisher PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(subscriber PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link library
target_link_libraries(publisher iceoryx_clib)
target_link_libraries(subscriber iceoryx_clib)

# Install
install(TARGETS publisher DESTINATION bin)
install(TARGETS subscriber DESTINATION bin)