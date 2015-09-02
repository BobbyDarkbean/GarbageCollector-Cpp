cmake_minimum_required(VERSION 2.8)

message("OS: ${CMAKE_SYSTEM}")

# Build options
set(GC_BUILD_OPT_ECHO 1)        # console logging
set(GC_BUILD_OPT_THREAD 1)      # multi-threading

if(${GC_BUILD_OPT_ECHO})
add_definitions(-DGC_ECHO)
endif(${GC_BUILD_OPT_ECHO})

if(${GC_BUILD_OPT_THREAD})
add_definitions(-DGC_MTHREAD)
endif(${GC_BUILD_OPT_THREAD})

message("Build options:")
message("Echo ${GC_BUILD_OPT_ECHO}")
message("Multi-threading ${GC_BUILD_OPT_THREAD}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
add_subdirectory(gc)
add_subdirectory(tests)
