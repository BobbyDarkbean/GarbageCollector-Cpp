cmake_minimum_required(VERSION 2.8)

set(LIB memmngt-gc)
project(${LIB})

set(GC_MAJOR_VERSION 2.3.0)
set(GC_MINOR_VERSION 2.3)

set(GC_SOURCE minfo.cpp
              garbagecollector.cpp)
set(GC_HEADER gc_global.h
              gc_shared.h
              minfo.h
              memorymanagement.h
              garbagecollector_m.h
              garbagecollector.h)

if(WIN32)
set(MEMMNGT_GC_LIB)
endif(WIN32)

set(CMAKE_CXX_FLAGS "-Wall -O3 -pedantic -s -std=c++0x")

add_library(${LIB} SHARED ${GC_SOURCE})
set_target_properties(${LIB} PROPERTIES
                             VERSION ${GC_MAJOR_VERSION}
                             SOVERSION ${GC_MINOR_VERSION})
