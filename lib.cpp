#include "lib.hpp"

namespace otus {

int fact(int i)
{
    return i < 2 ? 1 : i * fact(i-1);
}

} // otus
