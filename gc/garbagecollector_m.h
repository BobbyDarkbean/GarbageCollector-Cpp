#ifndef GARBAGECOLLECTOR_M_H
#define GARBAGECOLLECTOR_M_H


#include <unordered_map>
#ifdef GC_MTHREAD
#include <mutex>
#endif // GC_MTHREAD
#include "gc_global.h"


namespace MemoryManagement {
namespace Mapping {


class _MBlockInfo;


struct GarbageCollectorImplementation
{
    GarbageCollectorImplementation();
    ~GarbageCollectorImplementation();

    std::unordered_map<const void *, _MBlockInfo *> mem_map;

#ifdef GC_MTHREAD
    static std::mutex mx;
#endif // GC_MTHREAD

private:
    DISABLE_COPY(GarbageCollectorImplementation)
    DISABLE_MOVE(GarbageCollectorImplementation)
};

} // namespace Mapping
} // namespace MemoryManagement


#endif // GARBAGECOLLECTOR_M_H
