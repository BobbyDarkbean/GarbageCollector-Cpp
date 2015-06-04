#include <iostream>
#include <thread>
#include "memorymanagement.h"

using namespace MemoryManagement;

void create_and_destroy(double d)
{
    double *x = new_object<double>(d);
    destroy(x);
}

int main()
{
    int *x = new_object<int>(4);
    int *y = new_object<int>(5);
    (void)x;

    std::cout << _GC.acquisitions() << std::endl;

    std::thread th1(create_and_destroy, 2.32);
    std::thread th2(create_and_destroy, 4.17);
    std::thread th3(create_and_destroy, 0.92);

    th1.join();
    th2.join();
    th3.join();

    destroy(y);

    std::cout << _GC.acquisitions() << std::endl;

    return 0;
}
