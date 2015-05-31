#include "garbagecollector.h"


namespace MemoryManagement {


GarbageCollector::GarbageCollector() { }


GarbageCollector::~GarbageCollector()
{
    std::map<size_t, _MBlockInfo *>::iterator _end = _mem_map.end();
    for (std::map<size_t, _MBlockInfo *>::iterator itr = _mem_map.begin();
         itr != _end; ++itr) {
        delete itr->second;
    }
}


GarbageCollector _GC;


} // namespace MemoryManagement
