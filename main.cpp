#include "lib.hpp"
#include "custom_list.hpp"
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

template <typename Container>
void print_container(Container & cont)
{
    for (const auto & val : cont) {
        std::cout << val << std::endl;
    }
}

template <typename Container>
void populate_container(Container & cont, int startKey, int numKeys)
{
    int stopKey = startKey + numKeys;
    for (int i = startKey; i < stopKey; ++i)
        cont.push_back(i);
}


int main() {

    {
        std::map<int, int> map;
        populate_map(map, 0, 10, otus::fact);
    }

    {
        std::map<int, int, std::less<int>, otus::ReservingAllocator<int>> map_custom_alloc(otus::ReservingAllocator<int>(10));
        populate_map(map_custom_alloc, 0, 10, otus::fact);
        print_map(map_custom_alloc);
    }

    {
        otus::CustomList<int> list;
        populate_container(list, 0, 10);
    }

    {
        otus::CustomList<int, otus::ReservingAllocator<int>> list_custom_alloc(otus::ReservingAllocator<int>(10));
        populate_container(list_custom_alloc, 0, 10);
        print_container(list_custom_alloc);
    }

    return 0;
}
