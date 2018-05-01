#pragma once
#include <string.h>
#include <iostream>

class MemoryAllocator {
public:
    MemoryAllocator();
    ~MemoryAllocator();
    void* Allocate(const size_t size);
    void Free(const void* address);

private:
    static const int MemoryPoolSize = 512 * 1024 * 1024;
    char* memoryPool;
    //void* iterator;
};

