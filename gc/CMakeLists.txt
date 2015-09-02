cmake_minimum_required(VERSION 2.8)

set(LIB memmngt-gc)
project(${LIB})

message("Project: ${PROJECT_NAME}")

set(GC_MAJOR_VERSION 2.3.0)
set(GC_MINOR_VERSION 2.3)

set(GC_SOURCE minfo.cpp
              garbagecollector.cpp)
set(GC_HEADER gc_global.h
              minfo.h
              memorymanagement.h
              garbagecollector_m.h
              garbagecollector.h)

set(CMAKE_CXX_FLAGS "-Wall -O3 -pedantic -s -std=c++0x")
if(${GC_BUILD_OPT_THREAD})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif(${GC_BUILD_OPT_THREAD})

add_library(${LIB} SHARED ${GC_SOURCE})
set_target_properties(${LIB} PROPERTIES
                             VERSION ${GC_MAJOR_VERSION}
                             SOVERSION ${GC_MINOR_VERSION})
