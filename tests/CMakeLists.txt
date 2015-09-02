cmake_minimum_required(VERSION 2.8)

set(APP gc2b_test)
project(${APP})

message("Project: ${PROJECT_NAME}")

set(GC_TEST_SOURCE main.cpp)
set(LIB_REQ memmngt-gc)

include_directories(../gc)

set(CMAKE_CXX_FLAGS "-Wall -O3 -pedantic -s -std=c++0x")
if(${GC_BUILD_OPT_THREAD})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif(${GC_BUILD_OPT_THREAD})

add_executable(${APP} ${GC_TEST_SOURCE})
target_link_libraries(${APP} ${LIB_REQ})
