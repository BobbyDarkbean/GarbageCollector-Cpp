#ifndef GC_GLOBAL_H
#define GC_GLOBAL_H


#define DISABLE_COPY(Class) \
    Class(const Class &); \
    Class &operator =(const Class &);


#define DISABLE_MOVE(Class) \
    Class(Class &&); \
    Class &operator =(Class &&);


#define GC_DRIVEN(Class) \
    virtual ~Class(); \
    template <typename T> \
    friend void _destruct_call<T>(T *); \
    template <typename T> \
    friend void _destruct_array_call<T>(T *);


#endif // GC_GLOBAL_H
