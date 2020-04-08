# Set build output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Generate executable
add_executable(ice_clib_pub publisher.c)
add_executable(ice_clib_sub subscriber.c)
add_executable(ice_clib_sub_callback subscriber_callback.c)

# Add include directories
target_include_directories(ice_clib_pub PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ice_clib_sub PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ice_clib_sub_callback PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link library
target_link_libraries(ice_clib_pub PRIVATE iceoryx_clib)
target_link_libraries(ice_clib_sub PRIVATE iceoryx_clib)
target_link_libraries(ice_clib_sub_callback PRIVATE iceoryx_clib)

# Install
install(TARGETS ice_clib_pub DESTINATION bin)
install(TARGETS ice_clib_sub DESTINATION bin)
install(TARGETS ice_clib_sub_callback DESTINATION bin)