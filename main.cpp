#include "lib.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>

template <typename MapType, typename ValueFunc>
void PopulateMap(MapType & map, int startKey, int numKeys, ValueFunc func)
{
    int stopKey = startKey + numKeys;
    for (int i = startKey; i < stopKey; ++i) {
        map[i] = func(i);
    }
}

template <typename MapType>
void PrintMap(const MapType & map) {
    for (auto & p: map)
        std::cout << p.first << " " << p.second << std::endl;
}

template <typename T>
struct ReservingAllocator {
    using value_type = T;
    using pointer = value_type*;

    ReservingAllocator(size_t poolSize)
        : mTotalSize(poolSize)
        , mPool(new T[poolSize])
        , mCurrentSize(0)
    {

    }

    //template <class U> struct rebind {typedef ReservingAllocator<U> other;};

    //ReservingAllocator() noexcept {}  // not required, unless used
    //template <class U> ReservingAllocator(ReservingAllocator<U> const&) noexcept {}
    
    pointer allocate(std::size_t n) {
        //std::cout << "allocate " << n << " elements, total size: " << n*sizeof (value_type) << std::endl;
        if (mCurrentSize + n > mTotalSize)
            throw std::bad_alloc();
        pointer p = mPool + mCurrentSize;
        mCurrentSize += n;
        return p;
    }

    void deallocate(pointer p, std::size_t n) noexcept {
//        //std::cout << "deallocate " << n << " elements" << std::endl;
//        std::free(p);
    }

private:
    const size_t mTotalSize;
    std::unique_ptr<T[]> mPool;
    size_t mCurrentSize;

};

template <typename T, typename U>
bool operator==(ReservingAllocator<T> const & a, ReservingAllocator<U> const & b) noexcept
{
    return &a == &b;
}

int main() {

    std::map<int, int, std::less<int>, ReservingAllocator<int>> m1(ReservingAllocator<int>(10));

    PopulateMap(m1, 0, 10, [](int key){return otus::fact(key);});
    PrintMap(m1);

    return 0;
}
