#include <iostream>
class MemoryAllocator {
public:

    MemoryAllocator() : iterator(memoryPool), current(0){}
    ~MemoryAllocator() {}

    void* Allocate(const size_t size) {
        for (size_t i = 0; i < size; ++i) {
            memoryPool[current] = 'A';
            ++current;
            iterator = &memoryPool[current];
        }
        return (void*) iterator;
    }
    void Free(const void* address) {
        auto p = reinterpret_cast<char*>(const_cast<void*>(address));
        *p = 0;
    }
    char* iterator;
private:
    static const int MemoryPoolSize = 512 * 1024 * 1024;
    char memoryPool[MemoryPoolSize];
    
    size_t current;
};

int main() {
    MemoryAllocator *m = new MemoryAllocator();
    m->Allocate(4);
    m->Free((m->iterator - 1));
    std::cin.get();
    return 0;
}