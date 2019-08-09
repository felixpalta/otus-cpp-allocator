#include <gtest/gtest.h>
#include "lib.hpp"

using AllocatorInt = otus::ReservingAllocator<int>;
using AllocatorPair = otus::ReservingAllocator<std::pair<int, int>>;

TEST(DefaultTests, FactTest) {
    ASSERT_EQ(otus::fact(0), 1);
    ASSERT_EQ(otus::fact(1), 1);
    ASSERT_EQ(otus::fact(2), 2);
    ASSERT_EQ(otus::fact(3), 6);
    ASSERT_EQ(otus::fact(5), 120);
    ASSERT_EQ(otus::fact(10), 3628800);
}

TEST(DefaultTests, AllocTest) {

    AllocatorInt alloc(10);
    ASSERT_EQ(alloc.pool_size(), 10);
    ASSERT_EQ(alloc.current_size(), 0);
    AllocatorInt::pointer p1 = alloc.allocate(1);
    ASSERT_NE(p1, nullptr);
    ASSERT_EQ(alloc.current_size(), 1);

    ASSERT_EQ(alloc.allocate(1), p1+1);
    ASSERT_EQ(alloc.current_size(), 2);

    ASSERT_EQ(alloc.allocate(8), p1+2);
    ASSERT_EQ(alloc.current_size(), 10);

    ASSERT_THROW(alloc.allocate(1), std::bad_alloc);
    ASSERT_EQ(alloc.current_size(), 10);
}


TEST(DefaultTests, AllocCopyTest) {

    AllocatorInt alloc(10);
    AllocatorInt alloc2(alloc);
    ASSERT_NE(alloc, alloc2);
    ASSERT_EQ(alloc.pool_size(), alloc2.pool_size());
    alloc.allocate(1);
    alloc2.allocate(10);
    ASSERT_EQ(alloc.current_size(), 1);
    ASSERT_EQ(alloc2.current_size(), 10);

    AllocatorPair allocPair(alloc);
    ASSERT_NE(allocPair, alloc);
    ASSERT_EQ(allocPair.pool_size(), alloc.pool_size());
    ASSERT_EQ(allocPair.current_size(), 0);
}
