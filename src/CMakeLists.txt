# Assign all the source code in current directory to LIB_SOURCES
aux_source_directory(. LIB_SOURCES)

# Set build output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Generate library
add_library(iceoryx_clib SHARED ${LIB_SOURCES})

# Add include directory
target_include_directories(iceoryx_clib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # headers for building
    $<INSTALL_INTERFACE:include>                   # headers for install
  )

# Add link library
target_link_libraries(iceoryx_clib PRIVATE iceoryx_posh::iceoryx_posh)

# For find_package
include(CMakePackageConfigHelpers)
# Create <Package>Config.cmake from PackageConfig.cmake.in
configure_package_config_file(
    "cmake/PackageConfig.cmake.in"
    "${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION lib/${PROJECT_NAME}/cmake
  )
# Create <Package>Version.cmake
write_basic_package_version_file(
    "${PROJECT_NAME}Version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
  )

# Install
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION .)
# <Package>Config.cmake and <Package>Version.cmake should be also installed
install(FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Version.cmake"
    DESTINATION lib/${PROJECT_NAME}/cmake
  )
install(TARGETS iceoryx_clib EXPORT iceoryx_clib DESTINATION lib)
install(EXPORT iceoryx_clib
    NAMESPACE ${PROJECT_NAME}::
    FILE "${PROJECT_NAME}Targets.cmake"
    DESTINATION lib/${PROJECT_NAME}/cmake
  )