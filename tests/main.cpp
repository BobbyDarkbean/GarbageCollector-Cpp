#include <iostream>
#include "memorymanagement.h"

using namespace MemoryManagement;

int main()
{
    int *x = new_object<int>(4);
    int *y = new_object<int>(5);
    std::cout << *x << std::endl;
    destroy(y);

    return 0;
}
