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
    friend void ::MemoryManagement::Mapping::_destruct_call<Class>(Class *); \
    friend void ::MemoryManagement::Mapping::_destruct_array_call<Class>(Class *);


#endif // GC_GLOBAL_H
