#include <gtest/gtest.h>
#include "lib.hpp"

TEST(DefaultTests, FactTest) {
    ASSERT_EQ(otus::fact(0), 1);
    ASSERT_EQ(otus::fact(1), 1);
    ASSERT_EQ(otus::fact(2), 2);
    ASSERT_EQ(otus::fact(3), 6);
    ASSERT_EQ(otus::fact(5), 120);
    ASSERT_EQ(otus::fact(10), 3628800);
}
