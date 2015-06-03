#ifndef GC_SHARED_H
#define GC_SHARED_H


#ifdef WIN32
#   ifdef MEMMNGT_GC_LIB
#       define GC_SHARED __declspec(dllexport)
#   else
#       define GC_SHARED __declspec(dllimport)
#   endif // MEMMNGT_GC_LIB
#else
#   define GC_SHARED
#endif // WIN32


#endif // GC_SHARED_H
