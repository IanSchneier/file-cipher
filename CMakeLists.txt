cmake_minimum_required(VERSION 3.28)
project(std_module_example CXX)

# Turning off extensions avoids an issue with the clang 16 compiler
# clang 17 and greater can avoid this setting
# set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
# Set the version of C++ for the project
set(CMAKE_CXX_STANDARD 20)
# Create a library
add_library(byte_census)
# Add the module file to the library
target_sources(byte_census
  PUBLIC
    FILE_SET CXX_MODULES FILES
      byte_census.cxx
)
# Create an executable
add_executable(file-cipher main.cxx)
# Link to the library byte_census
target_link_libraries(file-cipher byte_census)