#ifndef GARBAGECOLLECTOR_M_H
#define GARBAGECOLLECTOR_M_H


#include <cstdlib>
#include <map>
#include "minfo.h"
#include "gc_global.h"


namespace MemoryManagement {


struct GarbageCollectorImplementation
{
    GarbageCollectorImplementation();
    ~GarbageCollectorImplementation();

    std::map<size_t, _MBlockInfo *> mem_map;

private:
    DISABLE_COPY(GarbageCollectorImplementation)
    DISABLE_MOVE(GarbageCollectorImplementation)
};


}


#endif // GARBAGECOLLECTOR_M_H
