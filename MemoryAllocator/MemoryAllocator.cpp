#include "MemoryAllocator.h"

MemoryAllocator::MemoryAllocator()
{
    //memset(memoryPool, 'NUL', MemoryPoolSize);
    memoryPool[MemoryPoolSize] = {0};
    std::cout << "test\n";
}

MemoryAllocator::~MemoryAllocator() {}

void* MemoryAllocator::Allocate(const size_t size) {
    return nullptr;
}

void MemoryAllocator::Free(const void* address) {

}
