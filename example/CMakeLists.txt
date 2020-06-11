# minimum cmake version
cmake_minimum_required(VERSION 3.10)

# project name
project(iceoryx_clib_example VERSION 1.0.0)

# Find library
find_package(iceoryx_clib REQUIRED)
#target_link_libraries(ddsc PRIVATE iceoryx_clib::iceoryx_clib)

# Generate executable
add_executable(ice_clib_pub publisher.c)
add_executable(ice_clib_sub subscriber.c)
add_executable(ice_clib_sub_callback subscriber_callback.c)
add_executable(ice_clib_throughput_pub throughput_pub.c)
add_executable(ice_clib_throughput_sub throughput_sub.c)

# Link library
target_link_libraries(ice_clib_pub PRIVATE iceoryx_clib::iceoryx_clib)
target_link_libraries(ice_clib_sub PRIVATE iceoryx_clib::iceoryx_clib)
target_link_libraries(ice_clib_sub_callback PRIVATE iceoryx_clib::iceoryx_clib)
target_link_libraries(ice_clib_throughput_pub PRIVATE iceoryx_clib::iceoryx_clib)
target_link_libraries(ice_clib_throughput_sub PRIVATE iceoryx_clib::iceoryx_clib)
