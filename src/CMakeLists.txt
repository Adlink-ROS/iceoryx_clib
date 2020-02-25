# Assign all the source code in current directory to LIB_SOURCES
aux_source_directory(. LIB_SOURCES)

# Set build output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Generate library
add_library(iceoryx_clib SHARED ${LIB_SOURCES})

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)