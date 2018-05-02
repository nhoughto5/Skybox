#include <iostream>
#include <assert.h>

class MemoryAllocator {
public:

    MemoryAllocator() : iterator(memoryPool), current(0){}
    ~MemoryAllocator() {}
    char* iterator;

    void* Allocate(const size_t size) {
        try {
            for (size_t i = 0; i < size; ++i) {
                if (memoryPool[current] == 'A') throw std::runtime_error("Address Already Allocated\n");
                memoryPool[current] = 'A';
                current = (current + 1) % MemoryPoolSize;
                iterator = &memoryPool[current];
            }
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            exit(1);
        }

        return (void*) iterator;
    }

    void Free(const void* address) {
        if (address < memoryPool || (memoryPool + MemoryPoolSize) < address) {
            throw std::runtime_error("Can not deallocate memory outside of memory pool\n");
        }
        auto p = reinterpret_cast<char*>(const_cast<void*>(address));
        *p = 0;
    }

    char getAtIndices(size_t i) {
        return memoryPool[i];
    }
    
private:
    static const int MemoryPoolSize = 512 * 1024 * 1024;
    char memoryPool[MemoryPoolSize];
    size_t current;
};

void executeTests();

int main() {
    executeTests();
    return 0;
}

// ===== Tests ==== //

void basicAllocationTest() {
    MemoryAllocator *m = new MemoryAllocator();
    m->Allocate(4);
    assert(m->getAtIndices(0) == 'A');
    assert(m->getAtIndices(1) == 'A');
    assert(m->getAtIndices(2) == 'A');
    assert(m->getAtIndices(3) == 'A');
    std::cout << "Passed Basic Allocation Test\n";
    delete m;
}

void basicFreeTest() {
    MemoryAllocator *m = new MemoryAllocator();
    m->Allocate(4);
    m->Free(m->iterator - 2);
    assert(m->getAtIndices(0) == 'A');
    assert(m->getAtIndices(1) == 'A');
    assert(m->getAtIndices(2) != 'A');
    assert(m->getAtIndices(3) == 'A');
    std::cout << "Passed Basic Free Test\n";
    delete m;
}
void outOfScopeFreeTest() {
    MemoryAllocator *m = new MemoryAllocator();
    m->Allocate(1);
    try {
        m->Free(m->iterator - 2);
    } catch (const std::runtime_error& e) {
        std::cout << "Passed `Out Of Scope Free` Test\n";
        delete m;
        return;
    }
    std::cout << "Failed `Out Of Scope Free` Test\n";
    delete m;
}
void notAllocatedFreeTest() {
    MemoryAllocator *m = new MemoryAllocator();
    try {
        m->Free(m->iterator + 1);
    } catch (const std::runtime_error& e) {
        std::cout << "Failed `Not Allocated Free` Test\n";
    }
    std::cout << "Passed `Not Allocated Free` Test\n";
    delete m;
}

void executeTests() {
    basicAllocationTest();
    basicFreeTest();
    notAllocatedFreeTest();
    outOfScopeFreeTest();
}