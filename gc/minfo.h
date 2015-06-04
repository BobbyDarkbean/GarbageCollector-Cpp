#ifndef MINFO_H
#define MINFO_H


#include "gc_global.h"
#ifdef GC_ECHO
#include <iostream>
#include <typeinfo>
#include "garbagecollector_m.h"
#endif // GC_ECHO


namespace MemoryManagement {
namespace Mapping {


template <typename T>
void _destruct_call(T *ptr) { delete ptr; }


template <typename T>
void _destruct_array_call(T *ptr) { delete[] ptr; }


class _MBlockInfo
{
public:
    _MBlockInfo();
    virtual ~_MBlockInfo();
    virtual void *address() const = 0;

private:
    DISABLE_COPY(_MBlockInfo)
    DISABLE_MOVE(_MBlockInfo)
};


template <typename T>
class _MAllocInfo : public _MBlockInfo
{
public:
    explicit _MAllocInfo(T *object = 0);
    virtual ~_MAllocInfo();

    void *address() const;
    T *&operator *() { return obj; }

private:
    DISABLE_COPY(_MAllocInfo)
    DISABLE_MOVE(_MAllocInfo)

    T *obj;
};


template <typename T>
class _AAllocInfo : public _MBlockInfo
{
public:
    explicit _AAllocInfo(T *array = 0);
    virtual ~_AAllocInfo();

    void *address() const;
    T *&operator *() { return arr; }

private:
    DISABLE_COPY(_AAllocInfo)
    DISABLE_MOVE(_AAllocInfo)

    T *arr;
};


template <typename T>
_MAllocInfo<T>::_MAllocInfo(T *object)
    : _MBlockInfo(), obj(object)
{
#ifdef GC_ECHO
    std::cout << "MInfo: created for object of type "
              << typeid(T).name() << " at " << obj << std::endl;
#endif // GC_ECHO
}


template <typename T>
_MAllocInfo<T>::~_MAllocInfo()
{
    _destruct_call(obj);
#ifdef GC_ECHO
    std::cout << "MInfo: object of type " << typeid(T).name()
              << " destroyed at " << obj << std::endl;
#endif // GC_ECHO
}


template <typename T>
void *_MAllocInfo<T>::address() const
{ return reinterpret_cast<void *>(obj); }


template <typename T>
_AAllocInfo<T>::_AAllocInfo(T *array)
    : _MBlockInfo(), arr(array)
{
#ifdef GC_ECHO
    std::cout << "MInfo: created for array of type "
              << typeid(T).name() << " at " << arr << std::endl;
#endif // GC_ECHO
}


template <typename T>
_AAllocInfo<T>::~_AAllocInfo()
{
    _destruct_array_call(arr);
#ifdef GC_ECHO
    std::cout << "MInfo: array of type " << typeid(T).name()
              << " destroyed at " << arr << std::endl;
#endif // GC_ECHO
}


template <typename T>
void *_AAllocInfo<T>::address() const
{ return reinterpret_cast<void *>(arr); }


template <typename T>
_MBlockInfo *create_mInfo(T *ptr, bool array)
{
#ifdef GC_ECHO
    std::lock_guard<std::mutex> lock(GarbageCollectorImplementation::mx);
#endif // GC_ECHO
    if (array)  return new _AAllocInfo<T>(ptr);
    else        return new _MAllocInfo<T>(ptr);
}


} // namespace Mapping
} // namespace MemoryManagement


#endif // MINFO_H
