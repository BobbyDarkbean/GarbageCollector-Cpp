#include "minfo.h"
#include "garbagecollector_m.h"

#include "garbagecollector.h"


namespace MemoryManagement {


GarbageCollectorImplementation::GarbageCollectorImplementation()
    : mem_map() { }


GarbageCollectorImplementation::~GarbageCollectorImplementation()
{
    std::map<size_t, _MBlockInfo *>::iterator _end = mem_map.end();
    for (std::map<size_t, _MBlockInfo *>::iterator itr = mem_map.begin();
         itr != _end; ++itr) {
        delete itr->second;
    }
}


GarbageCollector::GarbageCollector()
    : m(new GarbageCollectorImplementation) { }


GarbageCollector::~GarbageCollector()
{
    delete m;
}


void GarbageCollector::acquire(size_t key, _MBlockInfo *mInfo)
{
    std::pair<std::map<size_t, _MBlockInfo *>::iterator, bool> insertion =
            m->mem_map.insert(std::make_pair(key, mInfo));

    if (!insertion.second) {
        delete insertion.first->second;
        insertion.first->second = mInfo;
    }
}


void GarbageCollector::release(size_t key)
{
    std::map<size_t, _MBlockInfo *>::iterator itr =
            m->mem_map.find(key);

    if (itr == m->mem_map.end())
        return;

    delete itr->second;
    m->mem_map.erase(itr);
}


GarbageCollector _GC;


} // namespace MemoryManagement
