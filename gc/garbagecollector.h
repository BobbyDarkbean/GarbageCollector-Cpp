#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H


#include <cstdlib>
#include "minfo.h"


namespace MemoryManagement {
namespace Mapping {


template <typename T>
inline const void *_object_unique_id(T *ptr)
{ return reinterpret_cast<const void *>(ptr); }


struct GarbageCollectorImplementation;
class GarbageCollector
{
    GarbageCollector();

public:
    ~GarbageCollector();

    template <typename T>
    T *acquire(T *ptr, bool array);

    template <typename T>
    void release(T *ptr);

    size_t acquisitions() const;

    static GarbageCollector &instance();

private:
    DISABLE_COPY(GarbageCollector)
    DISABLE_MOVE(GarbageCollector)

    void acquire_helper(const void *, _MBlockInfo *);
    void release_helper(const void *);

    GarbageCollectorImplementation *m;
};


template <typename T>
inline T *GarbageCollector::acquire(T *ptr, bool array)
{
    acquire_helper(_object_unique_id(ptr), create_mInfo(ptr, array));
    return ptr;
}


template <typename T>
inline void GarbageCollector::release(T *ptr)
{ release_helper(_object_unique_id(ptr)); }


} // namespace Mapping
} // namespace MemoryManagement


#define _GC (::MemoryManagement::Mapping::GarbageCollector::instance())


#endif // GARBAGECOLLECTOR_H
