cmake_minimum_required(VERSION 2.8)

message("OS: ${CMAKE_SYSTEM}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
add_subdirectory(gc)
add_subdirectory(tests)
