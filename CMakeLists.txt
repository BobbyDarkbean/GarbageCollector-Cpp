cmake_minimum_required(VERSION 2.8)

message("OS: ${CMAKE_SYSTEM}")

# Uncomment next line to enable console logging
add_definitions(-DGC_ECHO)
# Uncomment next line to enable multi-threading
add_definitions(-DGC_MTHREAD)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
add_subdirectory(gc)
add_subdirectory(tests)
