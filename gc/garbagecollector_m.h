#ifndef GARBAGECOLLECTOR_M_H
#define GARBAGECOLLECTOR_M_H


#include <cstdlib>
#include <map>
#include <mutex>
#include "gc_global.h"


namespace MemoryManagement {
namespace Mapping {


class _MBlockInfo;


struct GarbageCollectorImplementation
{
    GarbageCollectorImplementation();
    ~GarbageCollectorImplementation();

    std::map<size_t, _MBlockInfo *> mem_map;

    static std::mutex mx;

private:
    DISABLE_COPY(GarbageCollectorImplementation)
    DISABLE_MOVE(GarbageCollectorImplementation)
};


std::mutex GarbageCollectorImplementation::mx;


} // namespace Mapping
} // namespace MemoryManagement


#endif // GARBAGECOLLECTOR_M_H
