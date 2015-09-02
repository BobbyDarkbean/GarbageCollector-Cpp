#ifdef GC_ECHO
#include <iostream>
#include <typeinfo>
#endif // GC_ECHO
#include "garbagecollector_m.h"
#include "garbagecollector.h"


namespace MemoryManagement {
namespace Mapping {


#ifdef GC_MTHREAD
std::mutex GarbageCollectorImplementation::mx;
#endif // GC_MTHREAD


GarbageCollectorImplementation::GarbageCollectorImplementation()
    : mem_map() { }


GarbageCollectorImplementation::~GarbageCollectorImplementation()
{
    std::unordered_map<const void *, _MBlockInfo *>::iterator _end = mem_map.end();
    for (std::unordered_map<const void *, _MBlockInfo *>::iterator itr = mem_map.begin();
         itr != _end; ++itr) {
#ifdef GC_ECHO
    std::cout << "GC:\t" << itr->second->address()
              << "\tauto destruction" << std::endl;
#endif // GC_ECHO
        delete itr->second;
    }
}


GarbageCollector::GarbageCollector()
    : m(new GarbageCollectorImplementation) { }


GarbageCollector::~GarbageCollector()
{
    delete m;
}


size_t GarbageCollector::acquisitions() const
{
    return m->mem_map.size();
}


GarbageCollector &GarbageCollector::instance()
{
#ifdef GC_MTHREAD
    std::lock_guard<std::mutex> lock(GarbageCollectorImplementation::mx);
#endif // GC_MTHREAD

    static GarbageCollector gc;
    return gc;
}


void GarbageCollector::acquire_helper(const void *key, _MBlockInfo *mInfo)
{
#ifdef GC_MTHREAD
    std::lock_guard<std::mutex> lock(GarbageCollectorImplementation::mx);
#endif // GC_MTHREAD

    std::pair<std::unordered_map<const void *, _MBlockInfo *>::iterator, bool> insertion =
            m->mem_map.insert(std::make_pair(key, mInfo));

    if (!insertion.second) {
        delete insertion.first->second;
        insertion.first->second = mInfo;
    }
#ifdef GC_ECHO
    std::cout << "GC:\t" << insertion.first->second->address()
              << "\tpointer acquired" << std::endl;
#endif // GC_ECHO
}


void GarbageCollector::release_helper(const void *key)
{
#ifdef GC_MTHREAD
    std::lock_guard<std::mutex> lock(GarbageCollectorImplementation::mx);
#endif // GC_MTHREAD

    std::unordered_map<const void *, _MBlockInfo *>::iterator itr =
            m->mem_map.find(key);

    if (itr == m->mem_map.end())
        return;

#ifdef GC_ECHO
    std::cout << "GC:\t" << itr->second->address()
              << "\tuser-activated destruction" << std::endl;
#endif // GC_ECHO
    delete itr->second;
    m->mem_map.erase(itr);
}


} // namespace Mapping
} // namespace MemoryManagement
