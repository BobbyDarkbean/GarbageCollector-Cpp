#include <iostream>
#ifdef GC_MTHREAD
#include <thread>
#endif // GC_MTHREAD
#include "memorymanagement.h"

using namespace MemoryManagement;

struct GcDrivenObject
{
private:
    GC_DRIVEN(GcDrivenObject)
};

GcDrivenObject::~GcDrivenObject() { }

void create_and_destroy(double d)
{
    double *x = new_object<double>(d);
    destroy(x);
}

inline void print_object_count()
{
    std::cout << "Objects managed: " << _GC.acquisitions() << std::endl;
}

int main()
{
    int *x = new_object<int>(4);
    int *y = new_object<int>(5);
    (void)x;

    print_object_count();

#ifdef GC_MTHREAD
    std::thread th1(create_and_destroy, 2.32);
    std::thread th2(create_and_destroy, 4.17);
    std::thread th3(create_and_destroy, 0.92);

    th1.join();
    th2.join();
    th3.join();
#endif // GC_MTHREAD

    GcDrivenObject *gcd = new_object<GcDrivenObject>();
    (void)gcd;

    char *c = new_array<char>(5);
    int *a = new_array<int>(12);
    (void)a;

    print_object_count();

    destroy(c);
    destroy(y);

    print_object_count();

    return 0;
}
