#include "lib.hpp"
#include <iostream>
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

int main() {

    std::map<const int, int> m1;
    PopulateMap(m1, 0, 10, [](int key){return otus::fact(key);});
    PrintMap(m1);
    return 0;
}
