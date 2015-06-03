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


void GarbageCollector::acquire(size_t key, _MBlockInfo *mInfo)
{
    std::pair<std::map<size_t, _MBlockInfo *>::iterator, bool> insertion =
            _mem_map.insert(std::make_pair(key, mInfo));

    if (!insertion.second) {
        delete insertion.first->second;
        insertion.first->second = mInfo;
    }
}


void GarbageCollector::release(size_t key)
{
    std::map<size_t, _MBlockInfo *>::iterator itr =
            _mem_map.find(key);

    if (itr == _mem_map.end())
        return;

    delete itr->second;
    _mem_map.erase(itr);
}


GarbageCollector _GC;


} // namespace MemoryManagement
