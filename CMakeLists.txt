cmake_minimum_required(VERSION 3.1)

project(CommandCenter)

# Specify output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Include custom macros to find SC2Api.
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SC2Api REQUIRED)

# Build with c++14 support, required by sc2api.
set(CMAKE_CXX_STANDARD 14)

add_subdirectory("src")
