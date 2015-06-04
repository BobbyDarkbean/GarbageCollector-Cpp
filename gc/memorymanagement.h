#ifndef MEMORYMANAGEMENT_H
#define MEMORYMANAGEMENT_H


#include "garbagecollector.h"


namespace MemoryManagement {


template <typename T>
inline T *new_object()
{ return _GC.acquire(new T, false); }


template <typename T,
          typename T1>
inline T *new_object(T1 arg)
{ return _GC.acquire(new T(arg), false); }


template <typename T,
          typename T1, typename T2>
inline T *new_object(T1 arg1, T2 arg2)
{ return _GC.acquire(new T(arg1, arg2), false); }


template <typename T,
          typename T1, typename T2, typename T3>
inline T *new_object(T1 arg1, T2 arg2, T3 arg3)
{ return _GC.acquire(new T(arg1, arg2, arg3), false); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4>
inline T *new_object(T1 arg1, T2 arg2, T3 arg3, T4 arg4)
{ return _GC.acquire(new T(arg1, arg2, arg3, arg4), false); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4,
          typename T5>
inline T *new_object(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
{ return _GC.acquire(new T(arg1, arg2, arg3, arg4, arg5), false); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6>
inline T *new_object(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6)
{ return _GC.acquire(new T(arg1, arg2, arg3, arg4, arg5, arg6), false); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7>
inline T *new_object(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6,
                     T7 arg7)
{ return _GC.acquire(new T(arg1, arg2, arg3, arg4, arg5, arg6, arg7), false); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8>
inline T *new_object(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6,
                     T7 arg7, T8 arg8)
{
    return _GC.acquire(
            new T(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8), false);
}


template <typename T>
inline T *new_array()
{ return _GC.acquire(new T, true); }


template <typename T,
          typename T1>
inline T *new_array(T1 arg)
{ return _GC.acquire(new T(arg), true); }


template <typename T,
          typename T1, typename T2>
inline T *new_array(T1 arg1, T2 arg2)
{ return _GC.acquire(new T(arg1, arg2), true); }


template <typename T,
          typename T1, typename T2, typename T3>
inline T *new_array(T1 arg1, T2 arg2, T3 arg3)
{ return _GC.acquire(new T(arg1, arg2, arg3), true); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4>
inline T *new_array(T1 arg1, T2 arg2, T3 arg3, T4 arg4)
{ return _GC.acquire(new T(arg1, arg2, arg3, arg4), true); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4,
          typename T5>
inline T *new_array(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
{ return _GC.acquire(new T(arg1, arg2, arg3, arg4, arg5), true); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6>
inline T *new_array(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6)
{ return _GC.acquire(new T(arg1, arg2, arg3, arg4, arg5, arg6), true); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7>
inline T *new_array(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6,
                    T7 arg7)
{ return _GC.acquire(new T(arg1, arg2, arg3, arg4, arg5, arg6, arg7), true); }


template <typename T,
          typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8>
inline T *new_array(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6,
                    T7 arg7, T8 arg8)
{
    return _GC.acquire(
            new T(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8), true);
}


template <typename T>
inline void destroy(T *object)
{ _GC.release(object); }


} // namespace MemoryManagement


#endif // MEMORYMANAGEMENT_H
