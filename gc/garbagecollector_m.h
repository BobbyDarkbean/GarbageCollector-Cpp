#ifndef GARBAGECOLLECTOR_M_H
#define GARBAGECOLLECTOR_M_H


#include <unordered_map>
#include "gc_global.h"


namespace MemoryManagement {
namespace Mapping {


class _MBlockInfo;


struct GarbageCollectorImplementation
{
    GarbageCollectorImplementation();
    ~GarbageCollectorImplementation();

    std::unordered_map<const void *, _MBlockInfo *> mem_map;

private:
    DISABLE_COPY(GarbageCollectorImplementation)
};

} // namespace Mapping
} // namespace MemoryManagement


#endif // GARBAGECOLLECTOR_M_H
