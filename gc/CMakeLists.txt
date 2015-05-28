cmake_minimum_required(VERSION 2.8)

set(LIB memmngt-gc)
project(${LIB})

set(GC_MAJOR_VERSION 2.3.0)
set(GC_MINOR_VERSION 2.3)

set(GC_SOURCE minfo.cpp
              garbagecollector.cpp)
set(GC_HEADER gc_global.h
              minfo.h
              garbagecollector.h)

add_library(${LIB} SHARED ${GC_SOURCE})
set_target_properties(${LIB} PROPERTIES
                             VERSION ${GC_MAJOR_VERSION}
                             SOVERSION ${GC_MINOR_VERSION})
