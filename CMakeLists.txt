# minimum cmake version
cmake_minimum_required(VERSION 3.10)

# project name
project(iceoryx_clib)

# Dependency
find_package(iceoryx_posh QUIET)
if(NOT iceoryx_posh_FOUND)
  message(WARNING "iceoryx NOT FOUND: skip '${PROJECT_NAME}'")
  return()
endif()

# Process src, example
add_subdirectory(src)
add_subdirectory(example)