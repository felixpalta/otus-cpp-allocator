#include "lib.hpp"
#include <iostream>
#include <vector>
#include <map>

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

    //template <class U> struct rebind {typedef ReservingAllocator<U> other;};

    //ReservingAllocator() noexcept {}  // not required, unless used
    //template <class U> ReservingAllocator(ReservingAllocator<U> const&) noexcept {}
    
    pointer allocate(std::size_t n) {
        std::cout << "allocate " << n << " bytes" << std::endl;
        return  static_cast<pointer>(::operator new(n*sizeof (value_type)));
    }

    void deallocate(pointer p, std::size_t n) noexcept {
        std::cout << "deallocate " << n << " bytes" << std::endl;
        ::operator delete(p);
    }
};

//template <typename T, typename U>
//bool operator==(ReservingAllocator<T> const &, ReservingAllocator<U> const &) noexcept
//{
//    return false;
//}

//template <typename T, typename U>
//bool operator!=(ReservingAllocator<T> const & x, ReservingAllocator<U> const & y) noexcept
//{
//    return !(x == y);
//}

int main() {

    std::map<int, int, std::less<int>, ReservingAllocator<std::pair<const int, int>>> m1;

    m1[99] = 12;
    m1[100] = 14;
    PopulateMap(m1, 0, 10, [](int key){return otus::fact(key);});
    PrintMap(m1);

    return 0;
}
