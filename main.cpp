#include "lib.hpp"
#include <iostream>
#include <map>

template <typename MapType, typename ValueFunc>
void populate_map(MapType & map, int startKey, int numKeys, ValueFunc func)
{
    int stopKey = startKey + numKeys;
    for (int i = startKey; i < stopKey; ++i) {
        map[i] = func(i);
    }
}

template <typename MapType>
void print_map(const MapType & map) {
    for (auto & p: map)
        std::cout << p.first << " " << p.second << std::endl;
}

int main() {

    {
        std::map<int, int> map_standard_alloc;
        populate_map(map_standard_alloc, 0, 10, otus::fact);
    }

    {
        std::map<int, int, std::less<int>, otus::ReservingAllocator<int>> map_custom_alloc(otus::ReservingAllocator<int>(10));
        populate_map(map_custom_alloc, 0, 10, otus::fact);
        print_map(map_custom_alloc);
    }

    return 0;
}
