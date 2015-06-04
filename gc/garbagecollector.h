#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H


#include <cstdlib>
#include "minfo.h"
#include "gc_shared.h"


namespace MemoryManagement {
namespace Mapping {


template <typename T>
inline size_t _object_unique_id(T *ptr)
{ return reinterpret_cast<size_t>(ptr); }


struct GarbageCollectorImplementation;
class GC_SHARED GarbageCollector
{
    GarbageCollector();

public:
    ~GarbageCollector();

    template <typename T>
    T *acquire(T *ptr, bool array);

    template <typename T>
    void release(T *ptr);

    static GarbageCollector &instance();

private:
    DISABLE_COPY(GarbageCollector)
    DISABLE_MOVE(GarbageCollector)

    void acquire(size_t, _MBlockInfo *);
    void release(size_t);

    GarbageCollectorImplementation *m;
};


template <typename T>
inline T *GarbageCollector::acquire(T *ptr, bool array)
{
    acquire(_object_unique_id(ptr), create_mInfo(ptr, array));
    return ptr;
}


template <typename T>
inline void GarbageCollector::release(T *ptr)
{ release(_object_unique_id(ptr)); }


} // namespace Mapping
} // namespace MemoryManagement


#define _GC (::MemoryManagement::Mapping::GarbageCollector::instance())


#endif // GARBAGECOLLECTOR_H
