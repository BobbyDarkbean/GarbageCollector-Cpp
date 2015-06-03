#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H


#include <cstdlib>
#include "gc_global.h"
#include "gc_shared.h"


namespace MemoryManagement {


class _MBlockInfo;
template <typename T>
inline _MBlockInfo *create_mInfo(T *ptr, bool array);


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
    void acquire(T *ptr, bool array);

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
void GarbageCollector::acquire(T *ptr, bool array)
{ acquire(_object_unique_id(ptr), create_mInfo(ptr, array)); }


template <typename T>
void GarbageCollector::release(T *ptr)
{ release(_object_unique_id(ptr)); }


#define _GC ::MemoryManagement::GarbageCollector::instance()


} // namespace MemoryManagement


#endif // GARBAGECOLLECTOR_H
