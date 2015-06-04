#include <iostream>
#include "memorymanagement.h"

using namespace MemoryManagement;

int main()
{
    int *i = new_object<int>(4);
    std::cout << *i << std::endl;

    return 0;
}
