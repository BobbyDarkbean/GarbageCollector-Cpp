#ifdef GC_ECHO
#include <iostream>
#include <typeinfo>
#endif // GC_ECHO
#include "garbagecollector_m.h"
#include "garbagecollector.h"


namespace MemoryManagement {
namespace Mapping {


GarbageCollectorImplementation::GarbageCollectorImplementation()
    : mem_map() { }


GarbageCollectorImplementation::~GarbageCollectorImplementation()
{
    std::map<size_t, _MBlockInfo *>::iterator _end = mem_map.end();
    for (std::map<size_t, _MBlockInfo *>::iterator itr = mem_map.begin();
         itr != _end; ++itr) {
#ifdef GC_ECHO
    std::cout << "GC: auto destruction at "
              << itr->second->address() << std::endl;
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


GarbageCollector &GarbageCollector::instance()
{
    static GarbageCollector gc;
    return gc;
}


void GarbageCollector::acquire(size_t key, _MBlockInfo *mInfo)
{
    std::pair<std::map<size_t, _MBlockInfo *>::iterator, bool> insertion =
            m->mem_map.insert(std::make_pair(key, mInfo));

    if (!insertion.second) {
        delete insertion.first->second;
        insertion.first->second = mInfo;
    }
#ifdef GC_ECHO
    std::cout << "GC: pointer acquired at "
              << insertion.first->second->address() << std::endl;
#endif // GC_ECHO
}


void GarbageCollector::release(size_t key)
{
    std::map<size_t, _MBlockInfo *>::iterator itr =
            m->mem_map.find(key);

    if (itr == m->mem_map.end())
        return;

#ifdef GC_ECHO
    std::cout << "GC: user-activated destruction at "
              << itr->second->address() << std::endl;
#endif // GC_ECHO
    delete itr->second;
    m->mem_map.erase(itr);
}


} // namespace Mapping
} // namespace MemoryManagement
