#ifndef MINFO_H
#define MINFO_H


#include "gc_global.h"


namespace MemoryManagement {


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
    : _MBlockInfo(), obj(object) { }


template <typename T>
_MAllocInfo<T>::~_MAllocInfo() { _destruct_call(obj); }


template <typename T>
void *_MAllocInfo<T>::address() const
{ return reinterpret_cast<void *>(obj); }


template <typename T>
_AAllocInfo<T>::_AAllocInfo(T *array)
    : _MBlockInfo(), arr(array) { }


template <typename T>
_AAllocInfo<T>::~_AAllocInfo() { _destruct_array_call(arr); }


template <typename T>
void *_AAllocInfo<T>::address() const
{ return reinterpret_cast<void *>(arr); }


template <typename T>
inline _MBlockInfo *create_mInfo(T *ptr, bool array)
{ return array ? new _AAllocInfo<T>(ptr) : new _MAllocInfo<T>(ptr); }


} // namespace MemoryManagement


#endif // MINFO_H
