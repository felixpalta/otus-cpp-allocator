#ifndef RESERVING_ALLOCATOR_HPP
#define RESERVING_ALLOCATOR_HPP

#include <vector>
#include <cstddef>

namespace otus {

template <typename T>
struct ReservingAllocator {
    using value_type = T;
    using pointer = value_type*;

    ReservingAllocator(size_t poolSize) noexcept
        : mPoolSize(poolSize)
    {
    }

    ReservingAllocator(const ReservingAllocator & other)
        : mPoolSize(other.mPoolSize)
    {
        if (other.mPool.capacity()) {
            mPool.reserve(other.mPool.capacity());
            for (const auto & a : other.mPool)
                mPool.emplace_back(a);
        }
    }

    size_t pool_size() const { return mPoolSize; }
    size_t current_size() const { return mPool.size(); }

    template <class U> ReservingAllocator(ReservingAllocator<U> const& other) noexcept
        : mPoolSize(other.pool_size())
    {
    }

    pointer allocate(std::size_t n) {
        size_t oldSize = mPool.size();
        size_t newSize = mPool.size() + n;
        if (newSize > mPoolSize)
            throw std::bad_alloc();
        init_pool();
        mPool.resize(newSize);
        return &mPool[oldSize];
    }

    void deallocate(pointer /*p*/, std::size_t /*n*/) noexcept {
        // Do nothing - per-element deallocation is not supported
    }

private:
    void init_pool() {
        if (!mPool.capacity()) {
            mPool.reserve(mPoolSize);
        }
    }
private:
    const size_t mPoolSize;
    std::vector<T> mPool;
};


template <typename T>
bool operator==(ReservingAllocator<T> const & a, ReservingAllocator<T> const & b) noexcept
{
    return &a == &b;
}

template <typename T, typename U>
bool operator==(ReservingAllocator<T> const &, ReservingAllocator<U> const &) noexcept
{
    return false;
}

template <typename T, typename U>
bool operator!=(ReservingAllocator<T> const & a, ReservingAllocator<U> const & b) noexcept
{
    return !(a == b);
}

} // otus

#endif // RESERVING_ALLOCATOR_HPP
