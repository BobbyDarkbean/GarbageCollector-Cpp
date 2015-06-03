#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H


#include <map>
#include <cstdlib>
#include "minfo.h"
#include "gc_shared.h"


namespace MemoryManagement {


template <typename T>
inline size_t _object_unique_id(T *ptr)
{ return reinterpret_cast<size_t>(ptr); }


class GC_SHARED GarbageCollector
{
public:
    GarbageCollector();
    ~GarbageCollector();

    template <typename T>
    void acquire(T *ptr, bool array);

    template <typename T>
    void release(T *ptr);

private:
    DISABLE_COPY(GarbageCollector)

    void acquire(size_t, _MBlockInfo *);
    void release(size_t);

    std::map<size_t, _MBlockInfo *> _mem_map;
};


template <typename T>
void GarbageCollector::acquire(T *ptr, bool array)
{ acquire(_object_unique_id(ptr), create_mInfo(ptr, array)); }


template <typename T>
void GarbageCollector::release(T *ptr)
{ release(_object_unique_id(ptr)); }


extern GarbageCollector _GC;


} // namespace MemoryManagement


#endif // GARBAGECOLLECTOR_H
