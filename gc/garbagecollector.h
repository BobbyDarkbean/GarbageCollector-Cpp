#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H


#include <map>
#include <cstdlib>
#include "minfo.h"


namespace MemoryManagement {


template <typename T>
inline size_t _object_unique_id(T *ptr)
{ return reinterpret_cast<size_t>(ptr); }


class GarbageCollector
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

    std::map<size_t, _MBlockInfo *> _mem_map;
};


template <typename T>
void GarbageCollector::acquire(T *ptr, bool array)
{
    _MBlockInfo *mInfo = create_mInfo(ptr, array);
    std::pair<std::map<size_t, _MBlockInfo *>::iterator, bool> insertion =
            _mem_map.insert(std::make_pair(_object_unique_id(ptr), mInfo));

    if (!insertion.second) {
        delete *insertion.first;
        *insertion.first = mInfo;
    }
}


template <typename T>
void GarbageCollector::release(T *ptr)
{
    std::map<size_t, _MBlockInfo *>::iterator itr =
            _mem_map.find(_object_unique_id(ptr));

    if (itr == _mem_map.end())
        return;

    delete itr->second;
    _mem_map.erase(itr);
}


} // namespace MemoryManagement


#endif // GARBAGECOLLECTOR_H
