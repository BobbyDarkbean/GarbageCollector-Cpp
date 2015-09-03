#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H


#include <cstdlib>
#ifdef GC_MTHREAD
#include <mutex>
#endif // GC_MTHREAD
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

    void acquire_helper(const void *, _MBlockInfo *);
    void release_helper(const void *);

#ifdef GC_MTHREAD
    template <typename T>
    _MBlockInfo *create_mInfo_helper(T *ptr, bool array);
    
    static std::mutex mx;
#endif // GC_MTHREAD

    GarbageCollectorImplementation *m;
};


template <typename T>
inline T *GarbageCollector::acquire(T *ptr, bool array)
{
#if defined(GC_MTHREAD) && defined(GC_ECHO)
    _MBlockInfo *mInfo = create_mInfo_helper(ptr, array);
#else
    _MBlockInfo *mInfo = create_mInfo(ptr, array);
#endif // defined(GC_MTHREAD) && defined(GC_ECHO)
    acquire_helper(_object_unique_id(ptr), mInfo);
    return ptr;
}


template <typename T>
inline void GarbageCollector::release(T *ptr)
{ release_helper(_object_unique_id(ptr)); }


#if defined(GC_MTHREAD) && defined(GC_ECHO)
template <typename T>
inline _MBlockInfo *GarbageCollector::create_mInfo_helper(T *ptr, bool array)
{
    std::lock_guard<std::mutex> lock(GarbageCollector::mx);
    return create_mInfo(ptr, array);
}
#endif // defined(GC_MTHREAD) && defined(GC_ECHO)


} // namespace Mapping
} // namespace MemoryManagement


#define _GC (::MemoryManagement::Mapping::GarbageCollector::instance())


#endif // GARBAGECOLLECTOR_H
